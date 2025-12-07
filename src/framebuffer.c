#include "framebuffer.h"

uint8_t ssd1306_framebuffer[FRAMEBUFFER_SIZE] = {0};

int main(void){
    i2c_init(32);

    ssd1306_init(HORIZONTAL_ADDR_MODE);

    fb_clear();
    ssd1306_sendFramebuffer();


    for(;;){
        _delay_ms(100);
    }

    return 0;
}


void fb_clear(void){
    memset(ssd1306_framebuffer, 0, FRAMEBUFFER_SIZE);
}


void fb_entire_on(void){
    memset(ssd1306_framebuffer, 0xff, FRAMEBUFFER_SIZE);
}
