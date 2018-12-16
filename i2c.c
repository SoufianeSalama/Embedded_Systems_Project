#include "i2c.h"

I2C i2c;

void i2c_init(){
    i2c.base = (int*)(I2C_BASE);

   
    gpio_set_alt(2, 0);  //SDA
    gpio_set_alt(3, 0);  //SCL
}


void i2c_transfer(){
    i2c.base[I2C_A] = 0x3f; // I2C Slave Address (3f = 16*2 Display) kan je controleren met 'i2cdetect 1'
    
    i2c.base[I2C_DLEN] |= 1;            // one byte
    i2c.base[I2C_FIFO] |= 2;            // value 2
    i2c.base[I2C_S] |= I2C_CLEAR_STATUS;    // Reset status bits (see #define)
    i2c.base[I2C_C] |= I2C_START_WRITE;     // Start Write (see #define)

    wait_i2c_done();
    
}

// Delay voor I2C transactie
void wait_i2c_done() {
 
        int timeout = 50;
        while((!((I2C_S) & I2C_DONE)) && --timeout) {
            //usleep(1000);
        }
}


void i2c_printf(char *fmt,...){
    // int *ip;
	// char *cp;
	// cp = fmt;
	// ip = (int *)&fmt + 1;

	// while(*cp){
	// 	if (*cp != '%'){
	// 		uart_putc( *cp);
	// 		if (*cp=='\n')
	// 			uart_putc('\r');
	// 		cp++;
	// 		continue;
	// 	}
	// 	cp++;
	// 	switch(*cp){
	// 		case 'c': uart_putc((char)*ip);     break;
	// 		case 's': uart_prints((char *)*ip); break;
	// 		case 'd': uart_printi(*ip);         break;
	// 		case 'u': uart_printu(*ip);         break;
	// 		case 'x': uart_printx(*ip);         break;
	// 		case 'b': uart_printb(*ip);         break; //print binary
	// 	}
	// 	cp++; ip++;
	// }
}

void i2c_putc(char c)
{
//   _lock();
// 	if (uart.txon){                                //if TX is on, enter c into outbuf[]
// 		uart.outbuf[uart.outhead++] = c;
// 		uart.outhead %= UART_SBUFSIZE;
// 		uart.outdata++; uart.outroom--;
// 		_unlock();
// 		return;
// 	}

// 	// txon==0 means TX is off => output c & enable TX interrupt
// 	// PL011 TX is riggered only if write char, else no TX interrupt
// 	int i = *(uart.base+UART_UFR); // read FR
// 	while( *(uart.base+UART_UFR) & 0x20 );            // loop while FR=TXF
// 	*(uart.base+UART_UDR) = (int)c;                   // write c to DR
// 	*(uart.base+UART_IMSC) |= 0x30;                   // 0000 0000: bit5=TX mask bit4=RX mask
// 	uart.txon = 1;
// 	_unlock();
}