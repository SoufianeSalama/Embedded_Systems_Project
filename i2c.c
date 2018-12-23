#include "i2c.h"

I2C i2c;

void i2c_init(){
    i2c.base = (int*)(I2C_BASE);
    
    i2c.base[I2C_A] = 0x3f; // I2C Slave Address (3f = 16*2 Display) kan je controleren met 'i2cdetect 1'
   
    gpio_set_alt(2, 0);  //SDA1 Alternative function 0
    gpio_set_alt(3, 0);  //SCL1 Alternative function 0
}


void i2c_transfer(unsigned char send_value){
    i2c.base[I2C_DLEN] |= 1;            // twee bytes na elkaar sturen
    i2c.base[I2C_FIFO] |= send_value;

    i2c.base[I2C_S] |= I2C_CLEAR_STATUS;    // Reset status bits (see #define)
    i2c.base[I2C_C] |= I2C_START_WRITE;     // Start Write (see #define)

    wait_i2c_done();
    systim_waitus(5000);
}

// Delay voor I2C transactie
void wait_i2c_done() {
      int timeout = 50;
        while((!((i2c.base[I2C_S]) & i2c.base[I2C_DONE])) && --timeout) {
        //while((!((i2c.base[I2C_S]) & i2c.base[I2C_DONE]))) {
            systim_waitus(5000);
        }
        //   if(timeout == 0)
        //     uart_printf("Error: wait_i2c_done() timeout.\n");
            
}

void lcd_init(){
    lcd_parsebyte(0x33,0x00);     //init 8-bit
    lcd_parsebyte(0x32,0x00);     //init 8-bit
    lcd_parsebyte(0x06,0x00);     //Entry Mode Set: move cursor to right
    lcd_parsebyte(0x0C,0x00);     //Display On/Off: Cursor off, Blink off
    lcd_parsebyte(0x28,0x00);     //Function Set: 4-bit, 2-line, 5*8 dots
    lcd_parsebyte(0x01,0x00);     //Clear display
}

void lcd_parsebyte(unsigned char bits, unsigned char mode){
    // BITS => byte die in 2 gesplitst moet worden
    // MODE => 1(=DATA) of 0(=COMMAND)
    unsigned char backlight = 0x08;
    unsigned char enable = 0x04;
    unsigned char bits_hoog, bits_laag;

    bits_hoog = ((bits & 0xF0) | (backlight | mode)); 
    bits_laag = (((bits << 4) & 0xF0) | (backlight | mode));
    
    // Verzend de hoge bits (1keer zonder E, dan met E en dan weer zonder E)
    i2c_transfer(bits_hoog);
    i2c_transfer((bits_hoog | enable));
    i2c_transfer(bits_hoog);

    // Verzend de lage bits (1keer zonder E, dan met E en dan weer zonder E)
    i2c_transfer(bits_laag);
    i2c_transfer((bits_laag | enable));
    i2c_transfer(bits_laag);
}

void lcd_printtext(char message[]){
    // lcd_parsebyte(0b01001000,0x01);  
    lcd_parsebyte(' ',0x01);     // letter tussen enkele haken = unsigned
    lcd_parsebyte(' ',0x01);     
    lcd_parsebyte('H',0x01);     
    lcd_parsebyte('E',0x01);    
    lcd_parsebyte('L',0x01);    
    lcd_parsebyte('L',0x01);     
    lcd_parsebyte('O',0x01);    
    lcd_parsebyte(' ',0x01);     
    lcd_parsebyte('W',0x01);     
    lcd_parsebyte('O',0x01);     
    lcd_parsebyte('R',0x01);     
    lcd_parsebyte('L',0x01);     
    lcd_parsebyte('D',0x01);    
}

// void lcd_init(){
//     //Init volgens pythonscript
//     // 0x33
//     i2c_transfer(0b00111000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00111100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00111000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00111000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00111100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00111000); //4-bit, enable off, backlight on

//     //0x32
//     i2c_transfer(0b00111000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00111100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00111000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00101000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00101100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00101000); //4-bit, enable off, backlight on
//     ////////////////////////////////////////////////////////////
    
//     //0x06
//     i2c_transfer(0b00001000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00001100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00001000); //4-bit, enable off, backlight on

//     i2c_transfer(0b01101000); //4-bit, enable off, backlight on
//     i2c_transfer(0b01101100); //4-bit, enable on, backlight on
//     i2c_transfer(0b01101000); //4-bit, enable off, backlight on
//     ////////////////////////////////////////////////////////////

//     //0x0C
//     i2c_transfer(0b00001000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00001100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00001000); //4-bit, enable off, backlight on

//     i2c_transfer(0b11111000); //4-bit, enable off, backlight on
//     i2c_transfer(0b11111100); //4-bit, enable on, backlight on
//     i2c_transfer(0b11111000); //4-bit, enable off, backlight on
//     ////////////////////////////////////////////////////////////

//     //0x28
//     i2c_transfer(0b00101000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00101100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00101000); //4-bit, enable off, backlight on

//     i2c_transfer(0b10001000); //4-bit, enable off, backlight on
//     i2c_transfer(0b10001100); //4-bit, enable on, backlight on
//     i2c_transfer(0b10001000); //4-bit, enable off, backlight on

//     ////////////////////////////////////////////////////////////

//     //0x01 clear
//     i2c_transfer(0b00001000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00001100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00001000); //4-bit, enable off, backlight on

//     i2c_transfer(0b00011000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00011100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00011000); //4-bit, enable off, backlight on

//      ////////////////////////////////////////////////////////////

//     //0x01 clear
//     i2c_transfer(0b00001000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00001100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00001000); //4-bit, enable off, backlight on

//     i2c_transfer(0b00011000); //4-bit, enable off, backlight on
//     i2c_transfer(0b00011100); //4-bit, enable on, backlight on
//     i2c_transfer(0b00011000); //4-bit, enable off, backlight on
//      ////////////////////////////////////////////////////////////

//     //letter F
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b01101001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01101101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01101001); //4-bit, enable off, backlight on

//     //letter U
//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01011101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on

//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01011101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on

//     //letter C
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b00111001); //4-bit, enable off, backlight on
//     i2c_transfer(0b00111101); //4-bit, enable on, backlight on
//     i2c_transfer(0b00111001); //4-bit, enable off, backlight on

//     //letter K
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b10111001); //4-bit, enable off, backlight on
//     i2c_transfer(0b10111101); //4-bit, enable on, backlight on
//     i2c_transfer(0b10111001); //4-bit, enable off, backlight on

//     //letter _
//     i2c_transfer(0b00101001); //4-bit, enable off, backlight on
//     i2c_transfer(0b00101101); //4-bit, enable on, backlight on
//     i2c_transfer(0b00101001); //4-bit, enable off, backlight on

//     i2c_transfer(0b00001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b00001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b00001001); //4-bit, enable off, backlight on


//     //letter E
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01011101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on


//     //letter M
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b11011001); //4-bit, enable off, backlight on
//     i2c_transfer(0b11011101); //4-bit, enable on, backlight on
//     i2c_transfer(0b11011001); //4-bit, enable off, backlight on


//     //letter B
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b00101001); //4-bit, enable off, backlight on
//     i2c_transfer(0b00101101); //4-bit, enable on, backlight on
//     i2c_transfer(0b00101001); //4-bit, enable off, backlight on



//     //letter E
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01011101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on

//     //letter D
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     //letter D
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//      //letter E
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01011101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01011001); //4-bit, enable off, backlight on

//     //letter D
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on
//     i2c_transfer(0b01001101); //4-bit, enable on, backlight on
//     i2c_transfer(0b01001001); //4-bit, enable off, backlight on

// }
