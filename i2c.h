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
//void i2c_transfer(unsigned char send_value1,unsigned char send_value2);
void i2c_transfer(unsigned char send_value);
void wait_i2c_done();
void lcd_init();
void lcd_byte(unsigned char bits, char mode);
void lcd_toggle_enable(unsigned char bits);
void lcd_string();

#endif