#include <furi.h>
#include <gui/gui.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>

/* generated by fbt from .png files in images folder */
#include <sensors_icons.h>

// // keep track of app scene
// typedef enum {
//     SensorsAppScene_MainMenu,
//     SensorsAppScene_Sensor,
//     SensorsAppScene_count
// } SensorsAppScene;

// keep track of app view
typedef enum {
    SensorsAppView_Menu,
    SensorsAppView_Sensor
} SensorsAppScene;

// keep track of app context
typedef struct {
    SceneManager* sm;
    ViewDispatcher* vd;
} SensorsApp;

// app init stuff
void sensors_app_init(SensorsApp* s) {
    // init scene manager with list of all handlers
    s->sm = scene_manager_alloc(handlers, s);

    // init view dispatcher
    s->vd = view_dispatcher_alloc();
    view_dispatcher_enable_queue(s->vd);

    // allocate views
    s->menu = menu_alloc();
    s->sensor_data = empty_screen_alloc();
}

// main app logic
int32_t sensors_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm sensors!");

    return 0;
}
