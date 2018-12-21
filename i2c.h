#ifndef I2C_H
#define I2C_H

#include "defines.h"
#include "gpio.h"

typedef volatile struct {
	int* base;
	//char data[SPI_BUFSIZE];
	int dataLen, dataSend;
	int dataRdy;
} I2C;

extern I2C i2c;

void i2c_init();
void i2c_transfer(unsigned char send_value_byte_deel1, unsigned char send_value_byte_deel2);
void wait_i2c_done();
void lcd_init();


#endif