#include "framebuffer.h"


uint8_t ssd1306_framebuffer[FRAMEBUFFER_SIZE] = {0};


int main(void){
    i2c_init(32);

    SSD1306_Init();

    for(;;){
        FB_Clear();
        FB_DrawPixel(63, 32);
        FB_DrawRect(30,30,10,5,1);
        FB_DrawRect(30,36,10,5,0);
        SSD1306_SendFramebuffer(ssd1306_framebuffer);
        _delay_ms(1500);
        FB_EntireOn();
        FB_ClearPixel(63, 32);
        SSD1306_SendFramebuffer(ssd1306_framebuffer);
        _delay_ms(1500);
    }

    return 0;
}


void FB_DrawPixel(uint8_t x, uint8_t y){
    /* x to column and y to page */
    uint8_t page = y/8;
    uint8_t val = (1 << (y % 8));

    ssd1306_framebuffer[128*page + x] |= val;
}


void FB_ClearPixel(uint8_t x, uint8_t y){
    /* x to column and y to page */
    uint8_t page = y/8;
    uint8_t val = (1 << (y % 8));

    ssd1306_framebuffer[128*page + x] &= ~val;
}


void FB_Clear(void){
    memset(ssd1306_framebuffer, 0, 128*8);
    memset(ssd1306_framebuffer, 0xaa, 8);
    memset(&ssd1306_framebuffer[1024-8], 0xaa, 8);
}


void FB_EntireOn(void){
    memset(ssd1306_framebuffer, 0xff, 128*8);
    memset(ssd1306_framebuffer, 0xaa, 8);
    memset(&ssd1306_framebuffer[1024-8], 0xaa, 8);
}


void FB_DrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t fill){
    if(fill){
        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                FB_DrawPixel(x+i, y+j);
            }
        }

    }else{
        for(int i = 0; i < w; i++){
            FB_DrawPixel(x+i, y);
            FB_DrawPixel(x+i, y+h-1);
        }
        for(int i = 0; i < h; i++){
            FB_DrawPixel(x, y+i);
            FB_DrawPixel(x+w-1, y+i);
        }
    }
}


void FB_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
}
