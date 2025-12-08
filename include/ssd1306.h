#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <string.h>
#include "i2c.h"


#define SSD1306_SLA_0         0x3c  /* Adress 1 */
#define SSD1306_SLA_1         0x3d  /* Another option */

/* Control Bytes */
#define CB_SINGLE_COMMAND       0x00
#define CB_MULTIPLE_COMMANDS    0x80
#define CB_SINGLE_DATA          0x40
#define CB_MULTIPLE_DATA        0xc0

// Fundamental Command
#define SET_CONTRAST        0x81
#define DISPLAY_ON_RAM      0xa4
#define DISPLAY_ON_ENTIRE   0xa5
#define NORMAL_DISPLAY      0xa6
#define INVERSE_DISPLAY     0xa7
#define SET_DISPLAY_OFF     0xae
#define SET_DISPLAY_ON      0xaf

// Hardware Configuration
#define SEGMENT_REMAP       0xa0
#define SET_COM_SCAN_DIR    0xc0
#define SET_MUX_RATIO       0xa8
#define SET_DISPLAY_OFFSET  0xd3
#define SET_START_LINE      0x40
#define SET_COM_PINS        0xda

// Timing scheme
#define SET_CLOCK_DIV       0xd5
#define SET_PRE_CHARGE      0xd9
#define SET_VCOM_DSEL       0xdb

// Charge Pump
#define CHARGE_PUMP_SETTING 0x8d

// Addressing Setting 
#define SET_ADDRESSING_MODE 0x20
/* Page Addressing mode */
#define SET_COL_ADDR_L      0x00
#define SET_COL_ADDR_H      0x10
#define SET_PAGE_START      0xb0
/* Horizontal or vertical addressing mode */
#define SET_COL_ADDRESS     0x21
#define SET_PAGE_ADDRESS    0x22

// Continuous vertical and horizontal scroll setup
#define R_HOR_SCROLL        0x26
#define L_HOR_SCROLL        0x27
#define VER_R_HOR_SCROLL    0x29
#define VER_L_HOR_SCROLL    0x2a
#define DEACTIVATE_SCROLL   0x2e
#define ACTIVATE_SCROLL     0x2f

#define FRAMEBUFFER_SIZE    (128*8)


typedef enum{
    HORIZONTAL_ADDR_MODE         = 0,
    VERTICAL_ADDR_MODE           = 1,
    PAGE_ADDR_MODE               = 2,
} E_ADDRESSING_MODE;


void SSD1306_Init(void);
void SSD1306_SendFramebuffer(uint8_t *fb);

#endif
