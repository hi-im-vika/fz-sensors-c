#include "i2c_trx.h"

I2CTRx* i2c_init() {
    I2CTRx* i = malloc(sizeof(I2CTRx));
    i->address = 0x00;
    i->rx_bytes = 2;
    i->i2c_ok = false;

    return i;
}

void i2c_free(I2CTRx* i) {
    free(i);
}

void i2c_tx(I2CTRx* i) {
    // wipe rx data to prepare for rx
    memset(i->rx, 0, 256);
    // dynamically allocate array for expected bytes
    uint8_t* rx_buf = malloc(i->rx_bytes * sizeof(uint8_t));
    furi_hal_i2c_acquire(I2C_HANDLE);
    i->i2c_ok = false;
    i->i2c_ok = furi_hal_i2c_trx(
        I2C_HANDLE, i->address, i->tx, sizeof(i->tx), &rx_buf[0], i->rx_bytes, I2C_TIMEOUT);
    furi_hal_i2c_release(I2C_HANDLE);
}

void i2c_rx(I2CTRx* i) {
    // wipe rx data to prepare for rx
    memset(i->rx, 0, 256);
    // dynamically allocate array for expected bytes
    uint8_t* rx_buf = malloc(i->rx_bytes * sizeof(uint8_t));
    furi_hal_i2c_acquire(I2C_HANDLE);
    i->i2c_ok = furi_hal_i2c_rx(I2C_HANDLE, i->address, &rx_buf[0], i->rx_bytes, I2C_TIMEOUT);
    furi_hal_i2c_release(I2C_HANDLE);
}
