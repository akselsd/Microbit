#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

#define GPIO ((NRF_GPIO_REG*)0x50000000)
#define NROWS 3
#define NCOLUMNS 9
#define __BUTTON_A_PIN__ 17 //Datablad
#define __BUTTON_B_PIN__ 26 //Datablad
#define __ACTIVE_BUTTON__ 0 //Knapper aktive lave
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
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REG;


#endif
