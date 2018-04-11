#include "twi.h"
#include <stdlib.h>
#include "ubit_led_matrix.h"
#include "utility.h"
#include "uart.h"
#include "accel.h"

#define WHO_AM_I 0x0D
#define ACC_ADDRESS 0x01D


void set_led_matrix() {
	for (int i = 13; i < 16; i++)
	{
		GPIO->OUTSET = (1<<i);
	}
}


int main(){

	
	ubit_led_matrix_init();
	uart_init();
	twi_init();
	accel_init();
	int data_buffer[3];
	int sleep = 0;
	int x_accel = data_buffer[0];
	int y_accel = data_buffer[1];
	int x_dot = x_accel / 50;
	int y_dot = - y_accel / 50;
	ubit_led_matrix_light_only_at(x_dot, y_dot);
	while(1){
		accel_read_x_y_z(data_buffer);
		x_accel = data_buffer[0];
		y_accel = data_buffer[1];
		x_dot = x_accel / 50;
		y_dot = - y_accel / 50;
		
		ubit_led_matrix_light_only_at(x_dot, y_dot);
		sleep = 500d0;
		while(sleep--);
		
		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", data_buffer[0], data_buffer[1], data_buffer[2]);
	}
}
