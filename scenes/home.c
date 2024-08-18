#include "../sensors.h"

static void home_callback(void* ctx, uint32_t index) {
    SensorsApp* s = ctx;
    switch(index) {
    case SensorsAppMenu_SelectDummySensor:
        scene_manager_handle_custom_event(s->sm, SensorsAppEvent_UseDummySensor);
        break;
    case SensorsAppMenu_SelectBH1750:
        scene_manager_handle_custom_event(s->sm, SensorsAppEvent_UseBH1750);
        break;
    default:
        break;
    }
}

void sensors_scene_home_on_enter(void* ctx) {
    SensorsApp* s = ctx;
    submenu_reset(s->main_menu);
    submenu_add_item(
        s->main_menu, "Dummy Sensor", SensorsAppMenu_SelectDummySensor, home_callback, s);
    submenu_add_item(s->main_menu, "BH1750", SensorsAppMenu_SelectBH1750, home_callback, s);
    view_dispatcher_switch_to_view(s->vd, SensorsAppView_Menu);
}

bool sensors_scene_home_on_event(void* ctx, SceneManagerEvent evt) {
    SensorsApp* s = ctx;
    bool consumed = false;
    switch(evt.type) {
    case SceneManagerEventTypeCustom:
        switch(evt.event) {
        case SensorsAppEvent_UseDummySensor:
            scene_manager_next_scene(s->sm, SensorsAppScene_DummySensor);
            consumed = true;
            break;
        case SensorsAppEvent_UseBH1750:
            scene_manager_next_scene(s->sm, SensorsAppScene_BH1750);
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

void sensors_scene_home_on_exit(void* ctx) {
    SensorsApp* s = ctx;
    submenu_reset(s->main_menu);
}
