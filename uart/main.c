#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"

ssize_t _write(int fd, const void *buf, size_t count) { 
	char * letter = (char *)(buf); 
	for (int i = 0; i < count; i++) { 
		uart_send(*letter); 
		letter++; 
	} 
	return count; 
}

void set_led_matrix() {
	for (int i = 0; i < NROWS; i++)
	{
		GPIO->OUTSET = (1<<MATRIX_ROWS[i]);
	}
}

void clear_led_matrix() {
	for (int i = 0; i < NROWS; i++)
	{
		GPIO->OUTCLR = (1<<i);
	}
}

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[__BUTTON_A_PIN__] = 0;
	GPIO->PIN_CNF[__BUTTON_B_PIN__] = 0;

	int sleep = 0;
	int led_matrix_on = 0;
	while(1){

		if (GPIO->IN[__BUTTON_A_PIN__] == __ACTIVE_BUTTON__) {
			uart_send('A');
			set_led_matrix();
			//iprintf("Norway has %d counties.\n\r", 18);
		}
		if (GPIO->IN[__BUTTON_B_PIN__] == __ACTIVE_BUTTON__) {
			uart_send('B');
			clear_led_matrix();
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


		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
