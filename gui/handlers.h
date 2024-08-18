#pragma once

#include <gui/scene_manager.h>

#include "events/on_enter.h"
#include "events/on_event.h"
#include "events/on_exit.h"

extern void (*const scene_on_enter[])(void*);
extern void (*const scene_on_exit[])(void*);
extern bool (*const scene_on_event[])(void*, SceneManagerEvent);
extern const SceneManagerHandlers handlers;
