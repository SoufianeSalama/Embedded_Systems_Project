/********************************************************************
This c file is based on the original implementation of gpio.c
as described by K.C. Wang, <kwang@eecs.wsu.edu> in the book:
"Embedded and Real-Time Operation Systems" and modified for use 
on the Raspberry Pi 1 Model b+.

Additional comments/functions are added for a better explanation/
more functionality. 
********************************************************************/
#include "gpio.h"

volatile unsigned int* gpio_reg = (unsigned int*)GPIO_BASE;

//set alternative function of a pin
void gpio_set_alt(int x, int alt) {
	int bit = (x%10)*3;
	gpio_reg[GPIO_GPFSEL0 + (x/10)] &= ~(0x7 << bit);
	
	if (alt < 4)
		gpio_reg[GPIO_GPFSEL0 + (x/10)] |= ((0x4 | alt) << bit);
	else if (alt == 4)
		gpio_reg[GPIO_GPFSEL0 + (x/10)] |= (0x3 << bit);
	else if (alt == 5)
		gpio_reg[GPIO_GPFSEL0 + (x/10)] |= (0x2 << bit);
}

void gpio_pinmode(int x, int io) {
	int bit = (x%10)*3;
	gpio_reg[GPIO_GPFSEL0 + (x/10)] &= ~(0x7 << bit);
	if (io)
		gpio_reg[GPIO_GPFSEL0 + (x/10)] |= (0x1 << bit);
}

void gpio_set_output(int x){
	int bit = (x%10)*3;
	gpio_reg[GPIO_GPFSEL0 + (x/10)] &= ~(0x7 << bit);
	gpio_reg[GPIO_GPFSEL0 + (x/10)] |= (0x1 << bit);
}

void gpio_set_input(int x) {
	int bit = (x%10)*3;
	gpio_reg[GPIO_GPFSEL0 + (x/10)] &= ~(0x7 << bit);
}

void gpio_write_pin(int x, int s) {
	if (s)
		gpio_set_pin(x);
	else
		gpio_clear_pin(x);
}

void gpio_set_pin(int x){
	gpio_reg[GPIO_GPSET0 + (x/32)] |= (1 << (x%32));
}

void gpio_clear_pin(int x) {
	gpio_reg[GPIO_GPCLR0 + (x/32)] |= (1 << (x%32));
}

int gpio_read_pin(int x) {
	return ((gpio_reg[GPIO_GPLEV0 + (x/32)] >> (x%32)) & 0x1);
}

int gpio_read_event(int x) {
	int set = ((gpio_reg[GPIO_GPEDS0 + (x/32)] >> (x%32)) & 0x1);
	if (set)
		gpio_reg[GPIO_GPEDS0 + (x/32)] |= (1 << (x%32));
	return set;
}

void gpio_set_edge_detect(int x, int ed) {
	gpio_reg[GPIO_GPREN0 + (x/32)] &= ~(1 << (x%32));
	gpio_reg[GPIO_GPFEN0 + (x/32)] &= ~(1 << (x%32));
	
	if (ed & GPIO_RISING_EDGE)
		gpio_reg[GPIO_GPREN0 + (x/32)] |= (1 << (x%32));
	if (ed & GPIO_FALLING_EDGE)
		gpio_reg[GPIO_GPFEN0 + (x/32)] |= (1 << (x%32));
}

//set the pullup/down resistor on the given gpio pin
void gpio_pud(int x, int ud) {
	if (ud > 2)
		return;
	gpio_reg[GPIO_GPPUD] = ud;
	int i = 0;
	for (i = 0; i < 150; i++) ; //150 clock cycles
	gpio_reg[GPIO_GPPUDCLK0 + (x/32)] |= (1 << (x%32));
	for (i = 0; i < 150; i++) ;
	gpio_reg[GPIO_GPPUD] = 0;
	gpio_reg[GPIO_GPPUDCLK0 + (x/32)] = 0;
}









/** @brief GPIO initialization. For each gpio the correct registers are stored 
		   in variables declaired in the gpio struct */
// void gpio_init(){
// 	gpio_reg = (unsigned int*)GPIO_BASE;
// 	int i,j;
// 	int tiental;
// 	GPIO *gp;
// 	for(i = 0; i<=25;i++){
// 		j = i+2;
// 		gp = &gpio[j];
// 		gp->bit = (j%10)*3;
// 		gp->set = GPIO_GPSET0;
// 		gp->clr = GPIO_GPCLR0;
// 		gp->enable_falling_edge = GPIO_GPFEN0;
// 		gp->a_enable_falling_edge = GPIO_GPAFEN0;
// 		gp->detect_edge = GPIO_GPEDS0;
// 		gp->gpio_bit = j;
		
// 		tiental = j/10;
// 		switch (tiental){
// 			case 0:
// 				gp->sel = GPIO_GPFSEL0;
// 				break;
// 			case 1:
// 				gp->sel = GPIO_GPFSEL1;
// 				break;
// 			case 2:
// 				gp->sel = GPIO_GPFSEL2;
// 				break;
// 			default: break;
// 		}
// 	}
// }

// /** @brief Alter the gpio its functionality to an alternate function */
// void set_GPIO_alterfunc(GPIO *up, int n){
// 	gpio_reg[up->sel] |= (n << up->bit);
// }

// /** @brief Set the gpio as an output */
// void set_GPIO_output(GPIO *up){	
// 	gpio_reg[up->sel] |= (1 << up->bit);
// }

// /** @brief Set the gpio as an input */
// void set_GPIO_input(GPIO *up){	
// 	gpio_reg[up->sel] &= ~( 7<< up->bit);
// }

// /** @brief Set gpio output HIGH */
// void set_pin(GPIO *up){
// 	gpio_reg[up->set] = (1 << up->gpio_bit);
// }

// /** @brief Set gpio output LOW */
// void clear_pin(GPIO *up){
// 	gpio_reg[up->clr] = (1 << up->gpio_bit);
// }

// /** @brief Help function to clear the edge detect event */
// void clear_detect(GPIO *up){
// 	gpio_reg[up->detect_edge] = (1 << up->gpio_bit);
// }

// /** @brief Help function to enable the edge detect event*/
// void enable_falling_edge(GPIO *up){
// 	gpio_reg[up->enable_falling_edge] |= (1 << up->gpio_bit);
// 	gpio_reg[up->a_enable_falling_edge] |= (1 << up->gpio_bit);
// }

// /** @brief Enable edge detect event */
// void enable_edge_detect(GPIO *up){
// 	enable_falling_edge(up);
// }

// /** @brief  Return bit value for a specific register and corresponding bit number */
// int getBit(int bitNumber, int reg){	
// 	int bit = (reg >> bitNumber);
// 	return bit &= 1;
// }

// /** @brief Edge detect event check */
// int edge_detect(GPIO *up){
// 	if(getBit(up->gpio_bit, gpio_reg[up->detect_edge])){
// 		clear_detect(up);		
// 		return 1;
// 	}
// 	else{return 0;}
// }




