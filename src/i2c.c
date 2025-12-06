#include "i2c.h"

/*
 * 1) Not necessary to stop to switch between master transmit and master receive.
 */

static void i2c_start(void);
static void i2c_transmit(uint8_t data);
static void i2c_fsm_MT(void);
static void i2c_fsm_MR(void);


volatile I2CFsm I2C_FSM;


ISR(TWI_vect){
    if(!I2C_FSM.busy){
        /* Ignore interrupts */
        return;
    }

    switch(I2C_FSM.mode){
        case MASTER_TRANSMITTER_MODE:
            i2c_fsm_MT();
            break;
        case MASTER_RECEIVER_MODE:
            i2c_fsm_MR();
            break;
        case SLAVE_RECEIVER_MODE:
            break;
        default:
            break;
    }
}


void i2c_write(uint8_t sla, uint8_t* data_buf, uint8_t len, bool keep_alive){

    while(I2C_FSM.busy);        // block until free

    I2C_FSM.mode = MASTER_TRANSMITTER_MODE;
    I2C_FSM.buf = data_buf;
    I2C_FSM.buf_len = len;
    I2C_FSM.index = 0;
    I2C_FSM.sla = sla;
    I2C_FSM.busy = true;
    I2C_FSM.keep_alive = keep_alive;

    /* Send start condition / Repeated start */
    i2c_start();
}


void i2c_read(uint8_t sla, uint8_t* recv_buf, uint8_t len, bool keep_alive){

    while(I2C_FSM.busy);        // block until free

    I2C_FSM.mode = MASTER_RECEIVER_MODE;
    I2C_FSM.buf = recv_buf;
    I2C_FSM.buf_len = len;
    I2C_FSM.index = 0;
    I2C_FSM.sla = sla;
    I2C_FSM.busy = true;
    I2C_FSM.keep_alive = keep_alive;

    /* Send start condition / Repeated start */
    i2c_start();
}


void i2c_init(uint8_t bit_rate){
    TWBR = bit_rate;
    TWCR |= (1 << TWEN);
    sei();
}


void i2c_start(void){
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
}


void i2c_stop(void){
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}


void i2c_transmit(uint8_t data){
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
}


void i2c_state_machine(void){
}


static void i2c_fsm_MT(void){
    switch(TWSR){
        case 0x08:  /* START condition transmitted */
            /* Send SLA+W */
            i2c_transmit(I2C_FSM.sla << 1);
            break;
        case 0x10:  /* Repeated START condition transmitted */
            /* Send SLA+W */
            i2c_transmit(I2C_FSM.sla << 1);
            break;

        case 0x18:  /* SLA+W transmitted, ACK returned */
            /* Send data */
            i2c_transmit(I2C_FSM.buf[I2C_FSM.index]);
            break;

        case 0x20:  /* SLA+W transmitted, NACK returned */
            // TODO: Notify error. Finish FSM

        case 0x28:  /* Data byte has been transmitted. ACK returned */
            I2C_FSM.index ++;
            if(I2C_FSM.index == I2C_FSM.buf_len){
                I2C_FSM.busy = false;

                if(!I2C_FSM.keep_alive){
                    i2c_stop();
                }
            }
            break;

        case 0x30:  /* Data byte has been transmitted. NACK returned */
            /* Send data again */
            i2c_transmit(I2C_FSM.buf[I2C_FSM.index]);
            // TODO: count send attempts. Notify error if too much tries. 
            break;

        case 0x38:  /* Arbitration lost */
            break;
        default:
            break;
    }
}


static void i2c_fsm_MR(void){
    switch(TWSR){
        case 0x08:  /* START condition transmitted */
            /* Send SLA+W */
            i2c_transmit((I2C_FSM.sla << 1) | 1);
            break;
        case 0x10:  /* Repeated START condition transmitted */
            /* Send SLA+W */
            i2c_transmit((I2C_FSM.sla << 1) | 1);
            break;

        case 0x38:  /* Arbitration lost in SLA+R or NACK bit */
            // TODO
            break;

        case 0x40:  /* SLA+R transmitted, ACK returned */
            /* No Action */
            break;

        case 0x48:  /* SLA+R transmitted, NACK returned */
            // TODO
            break;

        case 0x50:  /* Data byte received. ACK returned */
            I2C_FSM.buf[I2C_FSM.buf_len++] = TWDR;
            if(I2C_FSM.index == I2C_FSM.buf_len){
                I2C_FSM.busy = false;

                if(!I2C_FSM.keep_alive){
                    i2c_stop();
                }
            }
            break;

        case 0x58:  /* Data byte received. NACK returned */
            // TODO
            break;

        default:
            break;
    }
}
