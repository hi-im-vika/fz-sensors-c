#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/empty_screen.h>
#include <gui/handlers.h>

/* generated by fbt from .png files in images folder */
#include <sensors_icons.h>

// keep track of app view
typedef enum {
    SensorsAppView_Menu,
    SensorsAppView_Sensor
} SensorsAppView;

// keep track of app context
typedef struct {
    SceneManager* sm;
    ViewDispatcher* vd;

    Submenu* menu;
    EmptyScreen* sensor_data;
} SensorsApp;
