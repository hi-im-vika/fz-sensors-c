#include "sensors.h"


void sm_init(SensorsApp* s) {
    // init scene manager with list of all handlers
    s->sm = scene_manager_alloc(&handlers, s);
}

void vd_init(SensorsApp* s) {
    // init view dispatcher
    s->vd = view_dispatcher_alloc();
    view_dispatcher_enable_queue(s->vd);

    // allocate views
    s->menu = menu_alloc();
    s->sensor_data = empty_screen_alloc();

    // assign callback to pass events from views to scene manager
    view_dispatcher_set_event_callback_context(s->vd, s);
    // view_dispatcher_set_custom_event_callback(s->vd, ViewDispatcherCustomEventCallback callback)
    view_dispatcher_set_navigation_event_callback(s->vd, navigation_event_handler);

    // add views to dispatcher
    view_dispatcher_add_view(s->vd, SensorsAppView_Menu, menu_get_view(s->menu));
    view_dispatcher_add_view(s->vd, SensorsAppView_Sensor, empty_screen_get_view(s->sensor_data));
}

// free all memory related to app
void sensors_app_free(SensorsApp* s) {
    scene_manager_free(s->sm);
    view_dispatcher_remove_view(s->vd, SensorsAppView_Menu);
    view_dispatcher_remove_view(s->vd, SensorsAppView_Sensor);
    view_dispatcher_free(s->vd);
    menu_free(s->menu);
    empty_screen_free(s->sensor_data);
    free(s);
}

// main app logic
int32_t sensors_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm sensors!");

    return 0;
}
