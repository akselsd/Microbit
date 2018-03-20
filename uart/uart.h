#ifndef UART_H
#define UART_H
#include <stdint.h>
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)
#define TGT_RXD_PIN 25
#define TGT_TXD_PIN 24
#define MAX_BAUDRATE 0x00275000
typedef struct { 
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t RESERVED0[248/4];		
	volatile uint32_t RXDREADY;
	volatile uint32_t RESERVED1[16/4];
	volatile uint32_t TXDREADY;
	volatile uint32_t RESERVED3[992 / 4];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED4;
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED5;
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED6[68/4];
	volatile uint32_t CONFIG;

} NRF_UART_REG;

void uart_init(); 
void uart_send(const char letter); 
char uart_read();



#endif // !UART_H
