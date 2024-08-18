/**
 * @file bh1750.c
 * @author vika
 * @brief retrieve data from the BH1750 sensor
 * @version 0.1
 * @date 2024-08-18
 * 
 */

#include "../sensors_i.h"

#define BH1750_ADDRESS 0x23

const char* bh1750_mode_strings[] = {
    "Oneshot",
    "Continuous",
};

const uint8_t bh1750_mode_cmd[] = {
    0b00100000,
    0b00010000,
};

const char* bh1750_res_strings[] = {
    "0.5 lx",
    "1 lx",
    "4 lx",
};

const uint8_t bh1750_res_cmd[] = {
    0b00000001,
    0b00000000,
    0b00000011,
};

enum BH1750VarItemListIndex {
    BH1750VarItemListIndexMode,       ///< item with current sensor mode of operation
    BH1750VarItemListIndexResolution, ///< item with current sensor resolution
    BH1750VarItemListIndexSave,       ///< item to save settings to sensor
    BH1750VarItemListIndexRead,       ///< item to read from sensor
};

/**
 * @brief callback to handle change in item value in VariableItemList
 * 
 * @param i item in VariableItemList that changed
 */
static void bh1750_callback(VariableItem* i) {
    // get context
    SensorsApp* s = variable_item_get_context(i);
    // get index of current value in option list
    uint8_t index = variable_item_get_current_value_index(i);
    uint8_t var_item_list_index = variable_item_list_get_selected_item_index(s->sensor_config);
    switch(var_item_list_index) {
    case BH1750VarItemListIndexMode:
        variable_item_set_current_value_text(i, bh1750_mode_strings[index]);
        break;
    case BH1750VarItemListIndexResolution:
        variable_item_set_current_value_text(i, bh1750_res_strings[index]);
        break;
    default:
        break;
    }
    variable_item_set_current_value_index(i, index);
}

/**
 * @brief callback to handle when enter key pressed on item in VariableItemList
 * 
 * @param ctx 
 * @param index 
 */
static void bh1750_enter_callback(void* ctx, uint32_t index) {
    SensorsApp* s = ctx;
    I2CTRx* i = s->it;
    if(index == BH1750VarItemListIndexSave) {
        VariableItem* current_item = variable_item_list_get(s->sensor_config, index);
        variable_item_set_current_value_text(current_item, "Wait...");
        // get word representing mode by retrieving current value index of mode item in VariableItemList to lookup in bh1750_mode_cmd array
        uint8_t mode_word = bh1750_mode_cmd[variable_item_get_current_value_index(
            variable_item_list_get(s->sensor_config, BH1750VarItemListIndexMode))];
        // get word representing resolution by retrieving current value index of resolution item in VariableItemList to lookup in bh1750_res_cmd array
        uint8_t res_word = bh1750_res_cmd[variable_item_get_current_value_index(
            variable_item_list_get(s->sensor_config, BH1750VarItemListIndexResolution))];

        // once config words are set up, prep for i2c tx
        // reset tx buffer
        memset(i->tx, 0, 256);
        i->address = BH1750_ADDRESS;
        i->tx_bytes = 1;                 // only expect to send one byte
        i->tx[0] = mode_word | res_word; // AND upper and lower word to get resulting config byte
        i->rx_bytes = 1;                 // expecting no bytes but zero causes undefined behaviour
        i2c_tx(i);
        // update list item value text to reflect result of saving settings
        if(i->i2c_ok) {
            variable_item_set_current_value_text(current_item, "Saved!");
        } else {
            variable_item_set_current_value_text(current_item, "Error!");
        }
    } else if(index == BH1750VarItemListIndexRead) {
        VariableItem* current_item = variable_item_list_get(s->sensor_config, index);
        variable_item_set_current_value_text(current_item, "Wait...");
        // once config words are set up, prep for i2c tx
        // reset tx buffer
        memset(i->tx, 0, 256);
        i->address = BH1750_ADDRESS;
        i->rx_bytes = 2; // expecting no bytes but zero causes undefined behaviour
        i2c_rx(i);
        // update list item value text to reflect result of saving settings
        if(i->i2c_ok) {
            char val[10];
            uint16_t lux = i->rx[0] << 8;
            lux |= i->rx[1];
            snprintf(val, sizeof(val), "%d", lux);
            variable_item_set_current_value_text(current_item, val);
        } else {
            variable_item_set_current_value_text(current_item, "Error!");
        }
    }
}

/**
 * @brief runs when entering the BH1750 scene
 * 
 * @param ctx app context
 */
void sensors_scene_bh1750_on_enter(void* ctx) {
    // get context
    SensorsApp* s = ctx;

    // set up list display
    VariableItemList* l = s->sensor_config;
    VariableItem* i;
    variable_item_list_reset(l);

    // adjust measurement mode
    i = variable_item_list_add(l, "Mode", 2, bh1750_callback, s);
    variable_item_set_current_value_index(i, 0);
    variable_item_set_current_value_text(i, bh1750_mode_strings[0]);

    // adjust resolution
    i = variable_item_list_add(l, "Resolution", 3, bh1750_callback, s);
    variable_item_set_current_value_index(i, 0);
    variable_item_set_current_value_text(i, bh1750_res_strings[0]);

    // save config to sensor
    i = variable_item_list_add(l, "Save", 0, NULL, s);
    variable_item_list_set_enter_callback(
        l,
        bh1750_enter_callback, // callback function to invoke on OK press
        s);                    // context object to pass to the callback function

    // save config to sensor
    i = variable_item_list_add(l, "Read", 0, NULL, s);
    variable_item_list_set_enter_callback(
        l,
        bh1750_enter_callback, // callback function to invoke on OK press
        s);                    // context object to pass to the callback function

    // switch to view after setup
    view_dispatcher_switch_to_view(s->vd, SensorsAppView_SensorConfig);
}

/**
 * @brief runs when an event is detected in the BH1750 scene
 * 
 * @param ctx app context
 * @param evt detected event
 * @return true event was handled
 * @return false event was not handled
 */
bool sensors_scene_bh1750_on_event(void* ctx, SceneManagerEvent evt) {
    UNUSED(ctx);
    UNUSED(evt);
    return false;
}

/**
 * @brief runs when leaving the BH1750 scene
 * 
 * @param ctx app context
 */
void sensors_scene_bh1750_on_exit(void* ctx) {
    SensorsApp* s = ctx;
    variable_item_list_reset(s->sensor_config);
}
