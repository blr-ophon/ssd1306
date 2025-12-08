#include "framebuffer.h"
#include "uart.h"


int main(void){
    i2c_init(32);

    ssd1306_init();
    UART_Init();

    fb_clear();
    ssd1306_sendFramebuffer();
    _delay_ms(1500);
    fb_entire_on();
    ssd1306_sendFramebuffer();
    _delay_ms(1500);

    for(;;){
        fb_clear();
        ssd1306_sendFramebuffer();
        _delay_ms(1500);
        fb_entire_on();
        ssd1306_sendFramebuffer();
        _delay_ms(1500);
    }

    return 0;
}


