#include <furi.h>

/* generated by fbt from .png files in images folder */
#include <sensors_icons.h>

int32_t sensors_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm sensors!");

    return 0;
}
