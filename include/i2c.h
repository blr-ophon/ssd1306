#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>


typedef enum{
    MASTER_TRANSMITTER_MODE     = 1,
    MASTER_RECEIVER_MODE        = 2,
    SLAVE_RECEIVER_MODE         = 3,
} E_I2C_MODE;


typedef struct{
    uint8_t mode;
    uint8_t* buf;
    uint8_t buf_len;
    uint8_t index;
    uint8_t sla;
    bool busy;
    bool keep_alive;
}I2CFsm;


void i2c_init(uint8_t bit_rate);
void i2c_write(uint8_t sla, uint8_t* data_buf, uint8_t len, bool keep_alive);
void i2c_read(uint8_t sla, uint8_t* recv_buf, uint8_t len, bool keep_alive);

#endif
