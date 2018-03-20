#include "uart.h"

void uart_init() {
	//Config pins
	GPIO->DIRCLR = (1 << TGT_RXD_PIN);
	GPIO->DIRSET = (1 << TGT_TXD_PIN);
	
	UART->PSELTXD = (TGT_TXD_PIN);
	UART->PSELRXD = (TGT_RXD_PIN);

	//Set baudrate limit
	UART->BAUDRATE = MAX_BAUDRATE;
	
	//Disable hardware flor control
	UART->CONFIG = 0;
	
	//Enable UART
	UART->ENABLE = 4;

	//Start reciver
	UART->STARTRX = 1;
}

void uart_send(const char letter) {
	UART->STARTTX = 1;
	UART->TXD = letter;

	//Wait for confirmation
	while (UART->TXDREADY != 1) {
	}
	
	//Clear event register
	UART->TXDREADY = 0;
}

char uart_read() {
	UART->RXDREADY = 0;
	UART->STARTRX = 1;

	if (UART->RXREADY) {
		return UART->TXD;
	}
	return '\0';
	

}