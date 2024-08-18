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

/**
 * @brief 
 * @details
 * @param i i2c context
 */
void i2c_tx(I2CTRx* i) {
    // wipe rx data to prepare for rx
    memset(i->rx, 0, 256);
    furi_hal_i2c_acquire(I2C_HANDLE);
    i->i2c_ok = false;
    i->i2c_ok = furi_hal_i2c_trx(
        I2C_HANDLE, (i->address) << 1, i->tx, i->tx_bytes, i->rx, i->rx_bytes, I2C_TIMEOUT);
    furi_hal_i2c_release(I2C_HANDLE);
}

/**
 * @brief 
 * @details
 * @param i i2c context
 */
void i2c_rx(I2CTRx* i) {
    // wipe rx data to prepare for rx
    memset(i->rx, 0, 256);
    furi_hal_i2c_acquire(I2C_HANDLE);
    i->i2c_ok = furi_hal_i2c_rx(I2C_HANDLE, (i->address) << 1, i->rx, i->rx_bytes, I2C_TIMEOUT);
    furi_hal_i2c_release(I2C_HANDLE);
}
