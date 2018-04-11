#include "twi.h"

#define TWI0 ((NRF_TWI_REG*)0x40003000)
#define SDA_PIN 30
#define SCL_PIN 0


typedef struct {

	//Tasks
	volatile uint32_t STARTRX;
	volatile uint32_t RESERVED0;
	volatile uint32_t STARTTX;
	volatile uint32_t RESERVED1[2];
	volatile uint32_t STOP;
	volatile uint32_t RESERVED2;
	volatile uint32_t SUSPEND;
	volatile uint32_t RESUME;
	
	//EventS
	volatile uint32_t RESERVED3[56];
	volatile uint32_t STOPPED;
	volatile uint32_t RXDREADY;
	volatile uint32_t RESERVED14[4];
	volatile uint32_t TXDSENT;
	volatile uint32_t RESERVED4;
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED5[4];
	volatile uint32_t BB;
	
	//Registers
	volatile uint32_t RESERVED9[49];
	volatile uint32_t SHORTS;
	volatile uint32_t RESERVED6[63];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED7[110];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED8[14];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED10;
	volatile uint32_t PSELSCL;
	volatile uint32_t PSELSDA;
	volatile uint32_t RESERVED11[2];
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED12;
	volatile uint32_t FREQUENCY;
	volatile uint32_t RESERVED13[24];
	volatile uint32_t ADDRESS;
} NRF_TWI_REG;


void twi_init(){
	GPIO->PIN_CNF[0] = ((1<<10) | (1<<9) | (1<<3) | (1<<2));
	GPIO->PIN_CNF[30] = ((1<<10) | (1<<9) | (1<<3) | (1<<2));
	
	TWI0->ERROR = 0;
	TWI0->TXDSENT = 0;
	TWI0->RXDREADY = 0;
	
	TWI0->PSELSCL = SCL_PIN;
	TWI0->PSELSDA = SDA_PIN;
	TWI0->FREQUENCY = 0x01980000;
	
	TWI0->ENABLE = 5;

}


void twi_multi_read(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_read,
	uint8_t * data_buffer
	){
	
	TWI0->ADDRESS = slave_address;
	TWI0->STARTTX = 1;
	
	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;
	
	while(!TWI0->TXDSENT);
	TWI0->TXDSENT = 0;
	TWI0->RXDREADY = 0;
	TWI0->STARTRX = 1;
	
	for(int i = 0; i<registers_to_read - 1; ++i){
		while(!TWI0->RXDREADY);
		TWI0->RXDREADY = 0;
		data_buffer[i] = TWI0->RXD;
	}	

	TWI0->STOP = 1;
	while(!TWI0->RXDREADY);
	data_buffer[registers_to_read -1 ] = TWI0->RXD;
	
	
}
	
	
	
void twi_multi_write(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_write,
	uint8_t * data_buffer
	){
	
	TWI0->ADDRESS = slave_address;
	TWI0->STARTTX = 1;
	
	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;
	
	while(!TWI0->TXDSENT);


	for (int i = 0; i < registers_to_write; ++i){
		TWI0->TXDSENT = 0;
		TWI0->TXD = data_buffer[i];
		while(!TWI0->TXDSENT);
	}
	
	TWI0->STOP = 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
