/********************************************************************
Main file inspired by the armc-013.c file from the Raspberry-Pi Bare
Metal Tutorials by Brian Sidebotham and modified to implement an
interrupt-driven device driver for the Raspberry Pi 1 Model b+.
********************************************************************/

#include "uart.h" // UART driver code file
#include "gpio.h"
#include "i2c.h"
#include "interrupts.h"
#include "spi.h"
#include "systimer.h"
#include "pcd8544.h"
#include "mcp3202.h"
#include <stdio.h>

#define nrMeasurements 20
#define XO 2
#define YO 45

extern void _unlock(void);

int measurements[nrMeasurements];

void addMeasurement(int meas);
void drawGraph();
int map(int x, int in_min, int in_max, int out_min, int out_max);


void main(){
	uart_init();				// initialize UARTs
	uart_enable_interrupt();
	
	spi_init();
	spi_enable_interrupt();
	spi_set_clk_freq(500000); //500 khz for adc

	/* Enable interrupts */
	_unlock();

	spi_set_clk_div(0);

	gpio_set_output(ACT_LED);
	pcd8544_init(4, 17, 1);
	mcp3202_init(0);
	systim_waits(3);

	int i;
	for (i = 0; i < nrMeasurements; i++)
		measurements[i] = 0;
	
	//start first measurements
	mcp3202_read_int(0);


	i2c_init();
	lcd_init();

	while(1){
		if (spi_rdy_int()) {
			pcd8544_clear();
			
			//read adc
			spi_set_clk_freq(500000); //500 khz for adc
			int adc = mcp3202_rdy_int();
			uart_printf("ADC: %u\r\n", adc);
			
			addMeasurement(adc);
			spi_set_clk_freq(4000000); //4 mhz for display
			drawGraph();
			
			pcd8544_display();
			gpio_write_pin(ACT_LED, !gpio_read_pin(ACT_LED));
			systim_waitms(500);
			
			mcp3202_read_int(0);

			if (adc>=150){
				// Te hoge waarde -> ALARM
				lcd_printtext("ALARM");
			}
			else{
				lcd_printtext("SAFE");
			}
		}
		
	}

}

void addMeasurement(int meas) {
	int i;
	for (i = 1; i < nrMeasurements; i++)
		measurements[i-1] = measurements[i];
	measurements[nrMeasurements-1] = meas;
}

void drawGraph() {
	pcd8544_drawline(XO, 0, XO, YO, PCD8544_BLACK);
	pcd8544_drawline(XO, YO, PCD8544_LCDWIDTH-1, YO, PCD8544_BLACK);
	
	int spacing = (PCD8544_LCDWIDTH-XO)/(nrMeasurements-1);
	int i;
	for (i = 0; i < nrMeasurements-1; i++) {
		int y1 = map(measurements[i], 0, MCP3202_MAX, YO, 0);
		int y2 = map(measurements[i+1], 0, MCP3202_MAX, YO, 0);
		pcd8544_drawline(XO + i*spacing, y1, XO + (i+1)*spacing, y2, PCD8544_BLACK);
	}
}

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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