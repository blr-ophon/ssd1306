#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <string.h>
#include <util/delay.h>
#include "ssd1306.h"


void fb_DrawPixel(uint8_t x, uint8_t y);
void fb_ClearPixel(uint8_t x, uint8_t y);
void fb_EntireOn(void);
void fb_Clear(void);


#endif
