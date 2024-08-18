#pragma once
#include <furi_hal_i2c.h>
#include <stdlib.h>
#include <string.h>

#define I2C_HANDLE  &furi_hal_i2c_handle_external
#define I2C_TIMEOUT 10

typedef struct {
    uint8_t address;
    uint8_t tx[256];
    uint8_t rx[256];

    bool i2c_ok;
    uint8_t rx_bytes;
} I2CTRx;

I2CTRx* i2c_init();
void i2c_free(I2CTRx* i);
void i2c_tx(I2CTRx* i);
void i2c_rx(I2CTRx* i);
