#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <string.h>
#include <util/delay.h>
#include "ssd1306.h"


void FB_DrawPixel(uint8_t x, uint8_t y);
void FB_ClearPixel(uint8_t x, uint8_t y);
void FB_EntireOn(void);
void FB_Clear(void);
void FB_DrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t fill);


#endif
