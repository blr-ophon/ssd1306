#include "ssd1306.h"


static void hor_addressing_set_addr(uint8_t page_start, uint8_t page_end, uint8_t col_start, uint8_t col_end);
static void page_addressing_set_addr(uint8_t page_start, uint8_t column_start);
static void ssd1306_sendCommand(uint8_t cmd);
static void ssd1306_sendData(uint8_t data);


uint8_t ssd1306_framebuffer[128*8] = {0};

void fb_clear(void){
    memset(ssd1306_framebuffer, 0, 128*8);
    memset(ssd1306_framebuffer, 0xaa, 8);
    memset(&ssd1306_framebuffer[1024-8], 0xaa, 8);
}


void fb_entire_on(void){
    memset(ssd1306_framebuffer, 0xff, 128*8);
    memset(ssd1306_framebuffer, 0xaa, 8);
    memset(&ssd1306_framebuffer[1024-8], 0xaa, 8);
}


void ssd1306_init(){
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
        ssd1306_sendCommand(command_seq[i]);
    }
}


void ssd1306_sendFramebuffer(void){
    hor_addressing_set_addr(0, 7, 4, 123);

    uint8_t *data_buf = ssd1306_framebuffer;
    uint8_t cb[] = {CB_SINGLE_DATA};
    uint8_t margin[4] = {0};

    for (uint8_t packet = 0; packet < 64; packet++) {
        i2c_write(SSD1306_SLA_0, cb, 1, true);
        i2c_write(SSD1306_SLA_0, &data_buf[packet*16], 16, false); 
    }
}


static void hor_addressing_set_addr(uint8_t page_start, uint8_t page_end, uint8_t col_start, uint8_t col_end){
    uint8_t command_seq[] = {
        SET_ADDRESSING_MODE, HORIZONTAL_ADDR_MODE,
        SET_PAGE_ADDRESS, page_start, page_end,
        SET_COL_ADDRESS, col_start, col_end,
    };

    for(int i = 0; i < sizeof(command_seq); i++){
        ssd1306_sendCommand(command_seq[i]);
    }
}


static void ssd1306_sendCommand(uint8_t cmd){
    uint8_t cmd_buf[] = {CB_SINGLE_COMMAND, cmd};
    i2c_write(SSD1306_SLA_0, cmd_buf, sizeof(cmd_buf), false); 
}


static void ssd1306_sendData(uint8_t data){
    uint8_t data_buf[] = {CB_SINGLE_DATA, data};
    i2c_write(SSD1306_SLA_0, data_buf, sizeof(data_buf), false); 
}







static void page_addressing_set_addr(uint8_t page_start, uint8_t column_start){
    uint8_t command_seq[] = {
        (SET_PAGE_START | (page_start & 0x07)),
        (SET_COL_ADDR_L | (column_start & 0x0f)),
        (SET_COL_ADDR_H | ((column_start & 0xf0) >> 4)),
    };

    for(int i = 0; i < sizeof(command_seq); i++){
        ssd1306_sendCommand(command_seq[i]);
    }
}

void send_framebuftest(void){
    page_addressing_set_addr(2,0);
    uint8_t *data_buf = ssd1306_framebuffer;
    uint8_t cb[] = {CB_SINGLE_DATA};
    for (uint8_t packet = 0; packet < 8; packet++) {
        i2c_write(SSD1306_SLA_0, cb, 1, true);
        i2c_write(SSD1306_SLA_0, &data_buf[packet*16], 16, false); 
    }
}
