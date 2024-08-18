#include "handlers.h"

void (*const scene_on_enter[])(void*) = {
    mainmenu_on_enter,
    sensors_data_on_enter,
};
void (*const scene_on_exit[])(void*) = {
    mainmenu_on_exit,
    sensors_data_on_exit,
};
bool (*const scene_on_event[])(void*, SceneManagerEvent) = {
    mainmenu_on_event,
    sensors_data_on_event,
};

const SceneManagerHandlers handlers = {
    .on_enter_handlers = scene_on_enter,
    .on_exit_handlers = scene_on_exit,
    .on_event_handlers = scene_on_event,
    .scene_num = SensorsAppScene_count,
};
