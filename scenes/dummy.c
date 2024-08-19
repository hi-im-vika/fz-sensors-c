/**
 * @file dummy.c
 * @author vika
 * @brief retrieve data from any sensor
 * @version 0.1
 * @date 2024-08-18
 * 
 */

#include "../sensors_i.h"
#include "dummy_i.h"

/**
 * @brief runs when entering the dummy sensor scene
 * 
 * @param ctx app context
 */
void sensors_scene_dummy_on_enter(void* ctx) {
    // get context
    SensorsApp* s = ctx;

    // set up list display
    VariableItemList* l = s->sensor_config;
    VariableItem* i;
    variable_item_list_reset(l);

    // specify bytes to send to device
    i = variable_item_list_add(l, "Payload", 1, NULL, s);
    variable_item_set_current_value_index(i, 0);
    variable_item_set_current_value_text(i, "N/A");

    // specify bytes expected from device
    i = variable_item_list_add(l, "RX Bytes", 1, NULL, s);
    variable_item_set_current_value_index(i, 0);
    variable_item_set_current_value_text(i, "N/A");

    // send command
    i = variable_item_list_add(l, "Send", 0, NULL, s);

    // switch to view after setup
    view_dispatcher_switch_to_view(s->vd, SensorsAppView_SensorConfig);
}

/**
 * @brief runs when an event is detected in the dummy sensor scene
 * 
 * @param ctx app context
 * @param evt detected event
 * @return true event was handled
 * @return false event was not handled
 */
bool sensors_scene_dummy_on_event(void* ctx, SceneManagerEvent evt) {
    SensorsApp* s = ctx;
    bool consumed = false;
    switch(evt.type) {
        case SceneManagerEventTypeCustom:
            switch(evt.event) {
                case Dummy_ByteInputEvent_Address:
                    scene_manager_next_scene(s->sm, SensorsAppScene_ByteInput);
                    consumed = true;
                    break;
                case Dummy_ByteInputEvent_Payload:
                    scene_manager_next_scene(s->sm, SensorsAppScene_ByteInput);
                    consumed = true;
                    break;
                case Dummy_Send:
                    i2c_tx(s->it);
                    scene_manager_next_scene(s->sm, SensorsAppScene_TextBox);
                    consumed = true;
                    break;
                default:
                    consumed = false;
                    break;
            }
            break;
        default: // eg. SceneManagerEventTypeBack, SceneManagerEventTypeTick
            consumed = false;
            break;
    }
    return consumed;
}

/**
 * @brief runs when leaving the dummy sensor scene
 * 
 * @param ctx app context
 */
void sensors_scene_dummy_on_exit(void* ctx) {
    SensorsApp* s = ctx;
    variable_item_list_reset(s->sensor_config);
}
