/********************************************************************
This header file is based on the original implementation of gpio.c
as described by K.C. Wang, <kwang@eecs.wsu.edu> in the book:
"Embedded and Real-Time Operation Systems" and modified for use 
on the Raspberry Pi 1 Model b+.

Additional comments/functions are added for a better explanation/
more functionality. 
********************************************************************/

#ifndef RPI_GPIO_H
#define RPI_GPIO_H

#include "defines.h"

#define ACT_LED 47 //https://raspberrypi.stackexchange.com/questions/67431/cant-turn-on-act-led-on-baremetal-pi3

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

#define GPIO_PUD_CLEAR 0
#define GPIO_PULLDOWN 1
#define GPIO_PULLUP 2

#define GPIO_ED_CLEAR 0
#define GPIO_RISING_EDGE 1
#define GPIO_FALLING_EDGE 2

void gpio_set_alt(int x, int alt);
void gpio_pinmode(int x, int io);
void gpio_set_output(int x);
void gpio_set_input(int x);
void gpio_write_pin(int x, int s);
void gpio_set_pin(int x);
void gpio_clear_pin(int x);
int gpio_read_pin(int x);
int gpio_read_event(int x);
void gpio_set_edge_detect(int x, int ed);
void gpio_pud(int x, int ud);


// /** @brief GPIO register which contains the GPIO base address of the 
// 	Raspberry Pi 1 Model b+ */
// static volatile unsigned int* gpio_reg;

// /** @brief The GPIO variable set */
// typedef volatile struct gpio{
// 	int sel;
// 	int bit;
// 	int set;
// 	int clr;
// 	int enable_falling_edge;
// 	int a_enable_falling_edge;	
// 	int detect_edge;
// 	int gpio_bit;
// }GPIO;

// GPIO gpio[27];

// extern void gpio_init();
// extern void set_GPIO_alterfunc(GPIO *up, int n);
// extern void set_GPIO_output(GPIO *up);
// extern void set_GPIO_input(GPIO *up);
// extern void set_pin(GPIO *up);
// extern void clear_pin(GPIO *up);
// extern void enable_edge_detect(GPIO *up);
// extern int edge_detect(GPIO *up);

// static void clear_detect(GPIO *up);
// static int getBit(int bitNumber, int reg);
// static void enable_falling_edge(GPIO *up);

#endif