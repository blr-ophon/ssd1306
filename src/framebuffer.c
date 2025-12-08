#include "framebuffer.h"
#include "uart.h"

uint8_t ssd1306_framebuffer[128*8] = {0};

int main(void){
    i2c_init(32);

    ssd1306_init();
    UART_Init();

    fb_Clear();
    ssd1306_sendFramebuffer();
    _delay_ms(1500);
    fb_EntireOn();
    ssd1306_sendFramebuffer();
    _delay_ms(1500);

    for(;;){
        fb_Clear();
        fb_DrawPixel(63, 32);
        ssd1306_sendFramebuffer();
        _delay_ms(1500);
        fb_EntireOn();
        ssd1306_sendFramebuffer();
        _delay_ms(1500);
    }

    return 0;
}


void fb_DrawPixel(uint8_t x, uint8_t y){
    /* x to column and y to page */
    uint8_t page = y/8;
    uint8_t val = (1 << (y % 8));

    ssd1306_framebuffer[128*page + x] |= val;
}


void fb_Clear(void){
    memset(ssd1306_framebuffer, 0, 128*8);
    memset(ssd1306_framebuffer, 0xaa, 8);
    memset(&ssd1306_framebuffer[1024-8], 0xaa, 8);
}


void fb_EntireOn(void){
    memset(ssd1306_framebuffer, 0xff, 128*8);
    memset(ssd1306_framebuffer, 0xaa, 8);
    memset(&ssd1306_framebuffer[1024-8], 0xaa, 8);
}
