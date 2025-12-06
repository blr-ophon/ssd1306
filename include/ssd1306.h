#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>


// Fundamental Command
#define CONTRAST_CONTROL    0x81
#define DISPLAY_ON_RAM      0xa4
#define DISPLAY_ON_IGNORE   0xa5
#define NORMAL_DISPLAY      0xa6
#define INVERSE_DISPLAY     0xa7
#define SET_DISPLAY_ON      0xae
#define SET_DISPLAY_OFF     0xaf

// Addressing Setting 
#define SET_ADDRESSING_MODE 0x20
/* Horizontal or vertical addressing mode */
#define SET_COLUMN_ADDRESS  0x21
#define SET_PAGE_ADDRESS    0x22


// Continuous vertical and horizontal scroll setup
#define R_HOR_SCROLL        0x26
#define L_HOR_SCROLL        0x27
#define VER_R_HOR_SCROLL    0x29
#define VER_L_HOR_SCROLL    0x2a
#define DEACTIVATE_SCROLL   0x2e
#define ACTIVATE_SCROLL     0x2f


typedef enum{
    HORIZONTAL_ADDR_MODE         = 0,
    VERTICAL_ADDR_MODE           = 1,
    PAGE_ADDR_MODE               = 2,
} E_ADDRESSING_MODE;


#endif
