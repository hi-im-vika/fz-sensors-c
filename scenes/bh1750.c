/**
 * @file bh1750.c
 * @author vika
 * @brief retrieve data from the BH1750 sensor
 * @version 0.1
 * @date 2024-08-18
 * 
 */

#include "../sensors.h"

const char* bh1750_mode_strings[] = {
    "Oneshot",
    "Continuous",
};

const char* bh1750_res_strings[] = {
    "0.5 lx",
    "1 lx",
    "4 lx",
};

enum BH1750VarItemListIndex {
    BH1750VarItemListIndexMode,       ///< item with current sensor mode of operation
    BH1750VarItemListIndexResolution, ///< item with current sensor resolution
    BH1750VarItemListIndexSave,       ///< item to save settings to sensor
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
    case BH1750VarItemListIndexSave:
        break;
    }
    variable_item_set_current_value_index(i, index);
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
