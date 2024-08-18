#include "on_enter.h"

void mainmenu_on_enter(void* ctx) {
    SensorsApp* s = ctx;
    submenu_reset(s->menu);
    submenu_add_item(s->menu, "Sensor 1", 0, NULL, s);
    submenu_add_item(s->menu, "Sensor 2", 1, NULL, s);
    submenu_add_item(s->menu, "Sensor 3", 2, NULL, s);
    view_dispatcher_switch_to_view(s->vd, SensorsAppScene_MainMenu);
}

void sensors_data_on_enter(void* ctx) {
    UNUSED(ctx);
}
