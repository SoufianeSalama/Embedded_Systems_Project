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
void i2c_transfer();
void wait_i2c_done();

// void i2c_set_();
// void i2c_set_();
// void i2c_set_();

void i2c_printf(char *fmt, ...);
void i2c_uputc(char c);

#endif