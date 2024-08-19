/**
 * @file byte_input.c
 * @author vika
 * @brief scene for data input
 * @version 0.1
 * @date 2024-08-18
 * 
 */

#include "../sensors_i.h"
#include "dummy_i.h"

/**
 * @brief callback to handle when save button is pressed
 * @details saves value to i2c struct and returns to previous scene
 * @param ctx 
 */
void byte_text_input_callback(void* ctx) {
    SensorsApp* s = ctx;
    scene_manager_previous_scene(s->sm);
}

/**
 * @brief runs when entering the byte input scene
 * 
 * @param ctx app context
 */
void sensors_scene_byte_input_on_enter(void* ctx) {
    // get context
    SensorsApp* s = ctx;
    if(scene_manager_has_previous_scene(s->sm, SensorsAppScene_DummySensor)) {
        switch(variable_item_list_get_selected_item_index(s->sensor_config)) {
            case(DummyVarItemListIndexAddress):
                byte_input_set_header_text(s->byte_input, "Enter Address");
                byte_input_set_result_callback(
                    s->byte_input, byte_text_input_callback, NULL, s, &(s->it->address), 1);
                break;
            case(DummyVarItemListIndexPayload):
                byte_input_set_header_text(s->byte_input, "Enter Payload");
                byte_input_set_result_callback(
                    s->byte_input, byte_text_input_callback, NULL, s, (s->it->tx), s->it->tx_bytes);
                break;
            default:
                break;
        }
    }

    view_dispatcher_switch_to_view(s->vd, SensorsAppView_ByteInput);
}

/**
 * @brief runs when an event is detected in the byte input scene
 * 
 * @param ctx app context
 * @param evt detected event
 * @return true event was handled
 * @return false event was not handled
 */
bool sensors_scene_byte_input_on_event(void* ctx, SceneManagerEvent evt) {
    SensorsApp* s = ctx;
    bool consumed = false;
    switch(evt.type) {
        case SceneManagerEventTypeCustom:
            switch(evt.event) {
                case SensorsAppEvent_EnterBytes:
                    scene_manager_next_scene(s->sm, SensorsAppScene_DummySensor);
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
 * @brief runs when leaving the byte input scene
 * 
 * @param ctx app context
 */
void sensors_scene_byte_input_on_exit(void* ctx) {
    UNUSED(ctx);
}
