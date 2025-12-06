#include "ssd1306.h"

int main(void){
    return 0;
}



void set_addressing_mode(E_ADDRESSING_MODE addr_mode){
    // Send 0x20
    // Send addressing mode
}

/*
 * Page Addressing Mode
 * 8 pages, 128 columns.
 * Set the starting page and column. After each read/write it increments
 * column. Resets to start when ends.
 */
void page_addressing(uint8_t column_start, uint8_t page_start, uint8_t data){
    // Set Page Start (10110 + [2:0])
    // Send lower nibble (0x0 + [3:0])
    uint8_t column_start_l = column_start & 0x0f;
    // Send higher nibble (0x1 + [3:0])
    uint8_t column_start_h = column_start & 0xf0;

    // Send data byte (D/C = 1)
}


void hor_scroll_command(uint8_t vertical){
    // Send scroll command
    // Send 0x00
    // Start page address
    // Time interval
    // End page address
    // Send 0x00
    // Send 0xff
}
