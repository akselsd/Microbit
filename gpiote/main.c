#include "ppi.h"
#include "gpio.h"
#include "gpiote.h"
#define __BUTTON_A_PIN__ 17 //Datablad
#define NROWS 3
#define NCOLUMNS 9
const int MATRIX_ROWS[NROWS] = [13, 14, 15];
const int MATRIX_COLUMNS[NCOLUMNS] = [4, 5, 6, 7, 8, 9, 10, 11, 12];

int main() {

	for (int i = 0; i<NCOLUMNS) {
		GPIO->DIRSET = (1 << MATRIX_COLUMNS[i]);
		GPIO->OUTCLR = (1 << MATRIC_COLUMNS[1]);
	}

	//Set up A button
	uint32_t button_a_config = 0;
	button_a_config += 1; //Mode
	button_a_config += (__BUTTON_A_PIN__ << 8); //PSEL
	button_a_config += (2 << 16); //POLARITY
	GPIOTE->CONFIG[0] = button_a_config;

	//Set up led rows
	uint32_t led_row_config;
	for (int i = 0; i < NROWS; i++)
	{
		led_row_config = 0;
		led_row_config += 3; //Mode
		led_row_config += (MATRIX_ROWS[i] << 8); //PSEL
		led_row_config += (3 << 16); //POLARITY
		GPIOTE->CONFIG[i + 1] = led_row_config;
	}


	//Enable channels 0,1,2
	for (int i = 0; i < NROWS; i++)
	{
		PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->IN[0]); 
		PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->OUT[i+1]);
		PPI->CHENSET = (1 << i);
	}

	while (1) {

	}





}