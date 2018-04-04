
#include <stdio.h>
#include "uart.h"
#include "gpio.h"



void set_led_matrix() {
	for (int i = 13; i < 16; i++)
	{
		GPIO->OUTSET = (1<<i);
	}
}

void clear_led_matrix() {
	for (int i = 13; i < 16; i++)
	{
		GPIO->OUTCLR = (1<<i);
	}
}

ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
	uart_init();
	int led_matrix_on = 0;

	iprintf("Norway has %d counties.\n\r", 18);
	while(1){

		if (!(GPIO->IN & (1<<17))) {
			uart_send('A');
		}
		if (!(GPIO->IN & (1<<26))) {
			uart_send('B');
		}
		
		char read_char = uart_read();
		if (read_char != '\0') {
			uart_send(read_char);

			if (led_matrix_on){
				clear_led_matrix();
			}
			else {
				set_led_matrix();
			}
			led_matrix_on = !led_matrix_on;
		}
		

	}
	return 0;
}
