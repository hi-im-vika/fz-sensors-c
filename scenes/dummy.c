/**
 * @file dummy.c
 * @author vika
 * @brief retrieve data from any sensor
 * @version 0.1
 * @date 2024-08-18
 * 
 */

#include "../sensors.h"

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

bool sensors_scene_dummy_on_event(void* ctx, SceneManagerEvent evt) {
    UNUSED(ctx);
    UNUSED(evt);
    return false;
}

void sensors_scene_dummy_on_exit(void* ctx) {
    SensorsApp* s = ctx;
    variable_item_list_reset(s->sensor_config);
}
