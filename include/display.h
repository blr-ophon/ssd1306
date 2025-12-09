#ifndef DISPLAY_H
#define DISPLAY_H

#include <string.h>
#include <util/delay.h>
#include "ssd1306.h"
#include <stdlib.h>


void Display_Update(void);
void Display_DrawPixel(uint8_t x, uint8_t y);
void Display_ClearPixel(uint8_t x, uint8_t y);
void Display_EntireOn(void);
void Display_Clear(void);
void Display_DrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t fill);
void Display_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);


#endif
