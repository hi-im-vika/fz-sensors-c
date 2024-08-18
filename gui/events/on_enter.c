#include "on_enter.h"

void mainmenu_on_enter(void* ctx) {
    SensorsApp* s = ctx;
    menu_reset(s->menu);
    menu_add_item(s->menu, "Sensor 1", NULL, 0, NULL, s);
    menu_add_item(s->menu, "Sensor 2", NULL, 1, NULL, s);
    menu_add_item(s->menu, "Sensor 3", NULL, 2, NULL, s);
    view_dispatcher_switch_to_view(s->vd, SensorsAppScene_MainMenu);
}

void sensors_data_on_enter(void* ctx) {
    UNUSED(ctx);
}
