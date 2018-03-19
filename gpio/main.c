#include <stdint.h>

#define __BUTTON_A_PIN__ 17 //Datablad
#define __BUTTON_B_PIN__ 26 //Datablad
#define __ACTIVE_BUTTON__ 0 //Knapper aktive lave
#define __RESREVED1_SIZE__ 120 //480 bytes mellom DIRCLR og PIN_CNF gir 120 ord offset
#define __GPIO_BASE_ADRESS__ 0x50000000 //Fra datablad
#define GPIO ((NRF_GPIO_REGS*)__GPIO_BASE_ADDRESS__)
#define NROWS 3
#define NCOLUMNS 9
const int MATRIX_ROWS[NROWS] = [13, 14, 15];
const int MATRIX_COLUMNS[NCOLUMNS] = [4, 5, 6, 7, 8, 9, 10, 11, 12];

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[__RESERVED1_SIZE__];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

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
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if (GPIO->IN[__BUTTON_B_PIN__] == __ACTIVE_BUTTON__) {
			set_led_matrix();
		}


		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if (GPIO->IN[__BUTTON_A_PIN__] == __ACTIVE_BUTTON__) {
			set_led_matrix(0);
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
