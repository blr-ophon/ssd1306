#include "display.h"


uint8_t ssd1306_framebuffer[FRAMEBUFFER_SIZE] = {0};


void Display_Update(void){
    SSD1306_SendFramebuffer(ssd1306_framebuffer);
}


void Display_DrawPixel(uint8_t x, uint8_t y){
    uint8_t page = y/8;
    uint8_t val = (1 << (y % 8));

    ssd1306_framebuffer[128*page + x] |= val;
}


void Display_ClearPixel(uint8_t x, uint8_t y){
    uint8_t page = y/8;
    uint8_t val = (1 << (y % 8));

    ssd1306_framebuffer[128*page + x] &= ~val;
}


void Display_Clear(void){
    memset(ssd1306_framebuffer, 0, 128*8);
}


void Display_EntireOn(void){
    memset(ssd1306_framebuffer, 0xff, 128*8);
}


void Display_DrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t fill){
    if(fill){
        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                Display_DrawPixel(x+i, y+j);
            }
        }

    }else{
        for(int i = 0; i < w; i++){
            Display_DrawPixel(x+i, y);
            Display_DrawPixel(x+i, y+h-1);
        }
        for(int i = 0; i < h; i++){
            Display_DrawPixel(x, y+i);
            Display_DrawPixel(x+w-1, y+i);
        }
    }
}


void Display_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
    /*
     * Bresenham Line Algorithm.
     */
    int dx = x1 - x0;
    int dy = y1 - y0;

    int sx = (dx > 0) ? 1 : -1;
    int sy = (dy > 0) ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);
    int err = dx - dy;  

    while (true) {
        Display_DrawPixel(x0, y0);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
