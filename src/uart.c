/**
 * @file uart.c
 * @brief Simple UART driver.
 */


#include "uart.h"
#include <util/setbaud.h>


/**
 * @brief Initializes UART0 peripheral.
 * @note Asyncrhonous. No double speed. TX and RX. 8-bit character with one stop bit.
 */
void UART_Init(void){
    /* Configure UBBR (must define BAUD) */
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    UCSR0A &= ~(1 << U2X0);

    /* Enable TX and RX */
    UCSR0B |= (1 << RXEN0);
    UCSR0B |= (1 << TXEN0);

    /* 8-bit Character size */
    UCSR0C |= (1 << UCSZ00);
    UCSR0C |= (1 << UCSZ01);
}


/** 
 * @brief Send Data through UART.
 * @note Polling Mode 
 * @param data Byte to be sent.
 */
void UART_SendPolling(uint8_t data){
    /*
     * Bit UDREn of UCSR0A indicates transmit buffer is ready to receive
     * new data.
     */
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}


/** 
 * @brief Send Data through UART.
 * @note Polling Mode. 
 * @return Byte received.
 */
uint8_t UART_ReceivePolling(void){
    /* Bit UDREn of UCSR0A flags end of transmission (data register empty) */
    loop_until_bit_is_set(UCSR0A, RXC0);
    /* 
     * AVR uses the same address/register for receive and transmit, but treats
     * them separately
     */
    return UDR0;
}


/** 
 * @brief Sends a string of characters through UART.
 * @note Polling Mode. 
 * @param str The string to be sent.
 */
void UART_print(char *str){
    for(int i = 0; str[i] != '\0'; i++){
        UART_SendPolling(str[i]);
    }
}
