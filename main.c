/********************************************************************
Main file inspired by the armc-013.c file from the Raspberry-Pi Bare
Metal Tutorials by Brian Sidebotham and modified to implement an
interrupt-driven device driver for the Raspberry Pi 1 Model b+.
********************************************************************/

#include "uart.h" // UART driver code file
#include "gpio.h"
#include "i2c.h"
#include "interrupts.h"
#include <stdio.h>

extern void _unlock(void);

void main(){
	//uart_init();				// initialize UARTs
	//uart_enable_interrupt();

	i2c_init();
	lcd_init();
	
	//spi_init();
	//spi_enable_interrupt();

	/* Enable interrupts */
	//_unlock();
	
	//while(1){
		//read adc
		//uart_printf("Soufiane Salama");
		//gpio_write_pin(ACT_LED, !gpio_read_pin(ACT_LED));
		
		//systim_waits(1);
		
	//}

}
// void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
// {
// 	gpio_init();
// 	set_GPIO_alterfunc(&gpio[14], 4);
// 	set_GPIO_alterfunc(&gpio[15], 4);

// 	/************************************************************* 
// 		LAB ASSIGNEMENT: ENABLE THE UART INTERRUPT IRQ HERE 
// 	*************************************************************/

// 	/* Initialize uart and allow uart to send interrupts */
// 	uart_init();				// initialize UARTs

// 	/* Enable interrupts */
// 	_unlock();

// 	char line[128];
// 	while(1){
// 		uprintf("Enter a line from UARTS\n\r");
// 		ugets(&uart, line);
// 		uprintf("%s\n", line);
// 	}
// }