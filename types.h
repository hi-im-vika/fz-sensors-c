#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/variable_item_list.h>

#include "util/i2c_trx.h"

// keep track of app context
typedef struct {
    SceneManager* sm;
    ViewDispatcher* vd;
    I2CTRx* it;

    Submenu* main_menu;
    VariableItemList* sensor_config;
} SensorsApp;
