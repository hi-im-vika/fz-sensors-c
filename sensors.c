#include "sensors.h"

bool navigation_event_handler(void* ctx) {
    SensorsApp* s = ctx;
    return scene_manager_handle_back_event(s->sm);
}

void sm_init(SensorsApp* s) {
    // init scene manager with list of all handlers
    s->sm = scene_manager_alloc(&handlers, s);
}

void vd_init(SensorsApp* s) {
    // init view dispatcher
    s->vd = view_dispatcher_alloc();
    view_dispatcher_enable_queue(s->vd);

    // allocate views
    s->menu = submenu_alloc();
    s->sensor_config = variable_item_list_alloc();

    // assign callback to pass events from views to scene manager
    view_dispatcher_set_event_callback_context(s->vd, s);
    // view_dispatcher_set_custom_event_callback(s->vd, ViewDispatcherCustomEventCallback callback)
    view_dispatcher_set_navigation_event_callback(s->vd, navigation_event_handler);

    // add views to dispatcher
    view_dispatcher_add_view(
        s->vd, SensorsAppView_SensorConfig, variable_item_list_get_view(s->sensor_config));
}

// app init stuff
SensorsApp* sensors_app_init() {
    SensorsApp* s = malloc(sizeof(SensorsApp));
    sm_init(s);
    vd_init(s);
    return s;
}

// free all memory related to app
void sensors_app_free(SensorsApp* s) {
    scene_manager_free(s->sm);
    view_dispatcher_remove_view(s->vd, SensorsAppView_Menu);
    view_dispatcher_remove_view(s->vd, SensorsAppView_SensorConfig);
    view_dispatcher_free(s->vd);
    submenu_free(s->menu);
    variable_item_list_free(s->sensor_config);
    free(s);
}

// entrypoint
int32_t sensors_app(void* p) {
    UNUSED(p);

    // begin main app init
    SensorsApp* s = sensors_app_init();

    // set first scene of app
    // create gui object
    Gui* gui = furi_record_open(RECORD_GUI);
    // attach dispatcher to gui
    view_dispatcher_attach_to_gui(s->vd, gui, ViewDispatcherTypeFullscreen);
    // set next scene and begin general logic
    scene_manager_next_scene(s->sm, SensorsAppScene_MainMenu);
    // start view dispatcher
    view_dispatcher_run(s->vd);

    // once at this point, begin cleanup
    furi_record_close(RECORD_GUI);
    sensors_app_free(s);

    return 0;
}
