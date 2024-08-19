/**
 * @file text_box.c
 * @author vika
 * @brief scene for showing peripheral response
 * @version 0.1
 * @date 2024-08-18
 * 
 */

#include "../sensors_i.h"

/**
 * @brief runs when entering the text box scene
 * 
 * @param ctx app context
 */
void sensors_scene_text_box_on_enter(void* ctx) {
    // get context

    SensorsApp* s = ctx;
    // allocate space for (4 characters + (4 characters and 1 space) * number of bytes received + null terminator) * sizeof(uint8_t)
    // char* text[(((4) + (5 * (s->it->rx_bytes - 1)) + 1) * sizeof(uint8_t))];

    if(s->it->i2c_ok) {
        // reset text store contents
        memset(s->text_store, 0, COUNT_OF(s->text_store));

        // put first byte into text store
        snprintf(s->text_store, 5, "0x%02X", s->it->rx[0]);

        // loop and put remaining bytes into text store
        for(int i = 1; i < s->it->rx_bytes; i++) {
            char human_byte[6];
            snprintf(human_byte, 6, " 0x%02X", s->it->rx[i]);
            strcat(s->text_store, human_byte);
        }
        text_box_set_text(s->text_box, s->text_store);
    } else {
        text_box_set_text(
            s->text_box,
            "Error communicating with peripheral. Check pullup resistors and address!");
    }

    view_dispatcher_switch_to_view(s->vd, SensorsAppView_TextBox);
}

/**
 * @brief runs when an event is detected in the text box scene
 * 
 * @param ctx app context
 * @param evt detected event
 * @return true event was handled
 * @return false event was not handled
 */
bool sensors_scene_text_box_on_event(void* ctx, SceneManagerEvent evt) {
    UNUSED(ctx);
    UNUSED(evt);
    return false;
}

/**
 * @brief runs when leaving the text box scene
 * 
 * @param ctx app context
 */
void sensors_scene_text_box_on_exit(void* ctx) {
    SensorsApp* s = ctx;
    text_box_reset(s->text_box);
}
