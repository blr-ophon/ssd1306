#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define BAUD 9600   /* UBRR calculation depends on this value */


void UART_Init(void);

void UART_SendPolling(uint8_t data);

uint8_t UART_ReceivePolling(void);

void UART_print(char *str);


#endif
