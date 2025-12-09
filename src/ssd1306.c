#include "ssd1306.h"
#include <util/delay.h>


static void SetPageColAddress(uint8_t page_start, uint8_t page_end, uint8_t col_start, uint8_t col_end);
static void SendCommand(uint8_t cmd);
static void SendData(uint8_t data);


extern volatile I2CFsm I2C_FSM;


void SSD1306_Init(){
    uint8_t command_seq[] = {
        SET_DISPLAY_OFF,
        SET_CLOCK_DIV, 0x80,
        SET_MUX_RATIO, 0x3f,        /* 64MUX */
        SET_DISPLAY_OFFSET, 0x00,
        (SET_START_LINE | 0x00),
        CHARGE_PUMP_SETTING, 0x14,
        SET_ADDRESSING_MODE, HORIZONTAL_ADDR_MODE,
        (SEGMENT_REMAP | 0x01),
        (SET_COM_SCAN_DIR | 0x80),
        SET_COM_PINS, 0x12,
        SET_CONTRAST, 0xcf,
        SET_PRE_CHARGE, 0xf1,
        SET_VCOM_DSEL, 0x20,
        DISPLAY_ON_RAM,
        NORMAL_DISPLAY, 
        SET_DISPLAY_ON
    };
    for(int i = 0; i < sizeof(command_seq); i++){
        SendCommand(command_seq[i]);
    }
}


void SSD1306_SendFramebuffer(uint8_t *fb){
    SetPageColAddress(0, 7, 0, 127);

    uint8_t cb[] = {CB_SINGLE_DATA};

    for (uint8_t packet = 0; packet < 64; packet++) {
        i2c_write(SSD1306_SLA_0, cb, 1, true);
        i2c_write(SSD1306_SLA_0, &fb[packet*16], 16, false); 
    }
}


static void SetPageColAddress(uint8_t page_start, uint8_t page_end, uint8_t col_start, uint8_t col_end){
    uint8_t command_seq[] = {
        SET_ADDRESSING_MODE, HORIZONTAL_ADDR_MODE,
        SET_PAGE_ADDRESS, page_start, page_end,
        SET_COL_ADDRESS, col_start, col_end,
    };

    for(int i = 0; i < sizeof(command_seq); i++){
        SendCommand(command_seq[i]);
    }
}


static void SendCommand(uint8_t cmd){
    uint8_t cmd_buf[] = {CB_SINGLE_COMMAND, cmd};
    i2c_write(SSD1306_SLA_0, cmd_buf, sizeof(cmd_buf), false); 
}


static void SendData(uint8_t data){
    uint8_t data_buf[] = {CB_SINGLE_DATA, data};
    i2c_write(SSD1306_SLA_0, data_buf, sizeof(data_buf), false); 
}
