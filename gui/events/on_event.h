#pragma once

#include <furi.h>
#include <gui/scene_manager.h>
#include "../../sensors.h"

bool mainmenu_on_event(void* ctx, SceneManagerEvent evt);
bool sensors_data_on_event(void* ctx, SceneManagerEvent evt);
