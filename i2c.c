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
            //usleep(1000);
            systim_waitus(5000);
        }
          if(timeout == 0)
            uart_printf("Error: wait_i2c_done() timeout.\n");
            
}

void lcd_init(){
    //Init volgens pythonscript
    // 0x33
    i2c_transfer(0b00111000); //4-bit, enable off, backlight on
    i2c_transfer(0b00111100); //4-bit, enable on, backlight on
    i2c_transfer(0b00111000); //4-bit, enable off, backlight on
    i2c_transfer(0b00111000); //4-bit, enable off, backlight on
    i2c_transfer(0b00111100); //4-bit, enable on, backlight on
    i2c_transfer(0b00111000); //4-bit, enable off, backlight on

    //0x32
    i2c_transfer(0b00111000); //4-bit, enable off, backlight on
    i2c_transfer(0b00111100); //4-bit, enable on, backlight on
    i2c_transfer(0b00111000); //4-bit, enable off, backlight on
    i2c_transfer(0b00101000); //4-bit, enable off, backlight on
    i2c_transfer(0b00101100); //4-bit, enable on, backlight on
    i2c_transfer(0b00101000); //4-bit, enable off, backlight on
    ////////////////////////////////////////////////////////////
    
    //0x06
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on
    i2c_transfer(0b00001100); //4-bit, enable on, backlight on
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on

    i2c_transfer(0b01101000); //4-bit, enable off, backlight on
    i2c_transfer(0b01101100); //4-bit, enable on, backlight on
    i2c_transfer(0b01101000); //4-bit, enable off, backlight on
    ////////////////////////////////////////////////////////////

    //0x0C
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on
    i2c_transfer(0b00001100); //4-bit, enable on, backlight on
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on

    i2c_transfer(0b11111000); //4-bit, enable off, backlight on
    i2c_transfer(0b11111100); //4-bit, enable on, backlight on
    i2c_transfer(0b11111000); //4-bit, enable off, backlight on
    ////////////////////////////////////////////////////////////

    //0x28
    i2c_transfer(0b00101000); //4-bit, enable off, backlight on
    i2c_transfer(0b00101100); //4-bit, enable on, backlight on
    i2c_transfer(0b00101000); //4-bit, enable off, backlight on

    i2c_transfer(0b10001000); //4-bit, enable off, backlight on
    i2c_transfer(0b10001100); //4-bit, enable on, backlight on
    i2c_transfer(0b10001000); //4-bit, enable off, backlight on

    ////////////////////////////////////////////////////////////

    //0x01 clear
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on
    i2c_transfer(0b00001100); //4-bit, enable on, backlight on
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on

    i2c_transfer(0b00011000); //4-bit, enable off, backlight on
    i2c_transfer(0b00011100); //4-bit, enable on, backlight on
    i2c_transfer(0b00011000); //4-bit, enable off, backlight on

     ////////////////////////////////////////////////////////////

    //0x01 clear
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on
    i2c_transfer(0b00001100); //4-bit, enable on, backlight on
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on

    i2c_transfer(0b00011000); //4-bit, enable off, backlight on
    i2c_transfer(0b00011100); //4-bit, enable on, backlight on
    i2c_transfer(0b00011000); //4-bit, enable off, backlight on
     ////////////////////////////////////////////////////////////

    //letter F
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b01101001); //4-bit, enable off, backlight on
    i2c_transfer(0b01101101); //4-bit, enable on, backlight on
    i2c_transfer(0b01101001); //4-bit, enable off, backlight on

    //letter U
    i2c_transfer(0b01011001); //4-bit, enable off, backlight on
    i2c_transfer(0b01011101); //4-bit, enable on, backlight on
    i2c_transfer(0b01011001); //4-bit, enable off, backlight on

    i2c_transfer(0b01011001); //4-bit, enable off, backlight on
    i2c_transfer(0b01011101); //4-bit, enable on, backlight on
    i2c_transfer(0b01011001); //4-bit, enable off, backlight on

    //letter C
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b00111001); //4-bit, enable off, backlight on
    i2c_transfer(0b00111101); //4-bit, enable on, backlight on
    i2c_transfer(0b00111001); //4-bit, enable off, backlight on

    //letter K
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b10111001); //4-bit, enable off, backlight on
    i2c_transfer(0b10111101); //4-bit, enable on, backlight on
    i2c_transfer(0b10111001); //4-bit, enable off, backlight on

    //letter _
    i2c_transfer(0b00101001); //4-bit, enable off, backlight on
    i2c_transfer(0b00101101); //4-bit, enable on, backlight on
    i2c_transfer(0b00101001); //4-bit, enable off, backlight on

    i2c_transfer(0b00001001); //4-bit, enable off, backlight on
    i2c_transfer(0b00001101); //4-bit, enable on, backlight on
    i2c_transfer(0b00001001); //4-bit, enable off, backlight on


    //letter E
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b01011001); //4-bit, enable off, backlight on
    i2c_transfer(0b01011101); //4-bit, enable on, backlight on
    i2c_transfer(0b01011001); //4-bit, enable off, backlight on


    //letter M
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b11011001); //4-bit, enable off, backlight on
    i2c_transfer(0b11011101); //4-bit, enable on, backlight on
    i2c_transfer(0b11011001); //4-bit, enable off, backlight on


    //letter B
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b00101001); //4-bit, enable off, backlight on
    i2c_transfer(0b00101101); //4-bit, enable on, backlight on
    i2c_transfer(0b00101001); //4-bit, enable off, backlight on



    //letter E
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b01011001); //4-bit, enable off, backlight on
    i2c_transfer(0b01011101); //4-bit, enable on, backlight on
    i2c_transfer(0b01011001); //4-bit, enable off, backlight on

    //letter D
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    //letter D
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

     //letter E
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b01011001); //4-bit, enable off, backlight on
    i2c_transfer(0b01011101); //4-bit, enable on, backlight on
    i2c_transfer(0b01011001); //4-bit, enable off, backlight on

    //letter D
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

    i2c_transfer(0b01001001); //4-bit, enable off, backlight on
    i2c_transfer(0b01001101); //4-bit, enable on, backlight on
    i2c_transfer(0b01001001); //4-bit, enable off, backlight on

}


void lcd_byte(unsigned char bits, char mode){
    // BITS => byte die in 2 gesplitst moet worden
    // MODE => 1(=DATA) of 0(=COMMAND)

    unsigned char bits_hoog, bits_laag;

    bits_hoog = (mode || (bits && 0xF0) || 0x08); //0x08=Backlight
    bits_laag = (mode || ((bits << 4) && 0xF0) || 0x08);
    
    uart_printf("De hoge bits%b\n", bits_hoog);
    uart_printf("De lage bits%b\n", bits_laag);
    
    // Verzend de hoge bits
    //i2c_transfer(bits_hoog);
    lcd_toggle_enable(bits_hoog);

    // Verzend de lage bits
    //i2c_transfer(bits_laag);
    lcd_toggle_enable(bits_laag);
}

void lcd_toggle_enable(unsigned char bits){
    //systim_waitus(1000);
    i2c_transfer(bits || 0x04); // Enable on
    //systim_waitus(1000);
    i2c_transfer(bits && ~(0x04)); // Enable off
    //systim_waitus(1000);
}

void lcd_string(){
    

    // 4-Bit init
    i2c_transfer(0b00101000); //4-bit, enable off, backlight on
    //uart_printf("4-Bit.\n");

    i2c_transfer(0b00101100); //4-bit, enable on, backlight on
    i2c_transfer(0b00101000); //4-bit, enable off, backlight on
    systim_waitus(5000);

    ////////////////////////////////////////////////////////////

    // 2lines, 5*8dots
    i2c_transfer(0b00101000); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
    //uart_printf("4-Bit, 2-lines, 5*8dots. (HIGH BITS)\n");

    i2c_transfer(0b00101100); //4-bit, enable on, backlight on, hoogste bits (D7-D4)
    i2c_transfer(0b00101000); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
   
    i2c_transfer(0b10001000); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    //uart_printf("4-Bit, 2-lines, 5*8dots. (LOW BITS)\n");

    i2c_transfer(0b10001100); //4-bit, enable on, backlight on, laagste bits (D3-D0)
    i2c_transfer(0b10001000); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    systim_waitus(5000);

    ////////////////////////////////////////////////////////////

    //Cursor on, Cursor Blink off
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
    //uart_printf("Cursor on, Cursor Blink off. (HIGH BITS)\n");

    i2c_transfer(0b00001100); //4-bit, enable on, backlight on, hoogste bits (D7-D4)
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
   
    i2c_transfer(0b11001000); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    //uart_printf("Cursor on, Cursor Blink off. (LOW BITS)\n");

    i2c_transfer(0b11001100); //4-bit, enable on, backlight on, laagste bits (D3-D0)
    i2c_transfer(0b11001000); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    systim_waitus(5000);
    ////////////////////////////////////////////////////////////

    //Entry Mode Set: Cursor moves to right
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
    // uart_printf("Entry Mode Set: Cursor moves to right. (HIGH BITS)\n");

    i2c_transfer(0b00001100); //4-bit, enable on, backlight on, hoogste bits (D7-D4)
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
    
    i2c_transfer(0b01101000); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    // uart_printf("Entry Mode Set: Cursor moves to right. (LOW BITS)\n");

    i2c_transfer(0b01101100); //4-bit, enable on, backlight on, laagste bits (D3-D0)
    i2c_transfer(0b01101000); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    systim_waitus(5000);
    ////////////////////////////////////////////////////////////


    //Clear Display
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
    i2c_transfer(0b00001100); //4-bit, enable on, backlight on, hoogste bits (D7-D4)
    i2c_transfer(0b00001000); //4-bit, enable off, backlight on, hoogste bits (D7-D4)

    i2c_transfer(0b00011000); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    i2c_transfer(0b00011100); //4-bit, enable on, backlight on, laagste bits (D3-D0)
    i2c_transfer(0b00011000); //4-bit, enable off, backlight on, laagste bits (D3-D0)

    ////////////////////////////////////////////////////////////


    //Write Data: letter H = 0x48
    // i2c_transfer(0b01001001); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
    // // uart_printf("Write Data: letter H = 0x48. (HIGH BITS)\n");

    // i2c_transfer(0b01001101); //4-bit, enable on, backlight on, hoogste bits (D7-D4)
    // i2c_transfer(0b01001001); //4-bit, enable off, backlight on, hoogste bits (D7-D4)
    
    // i2c_transfer(0b10001001); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    // // uart_printf("Write Data: letter H = 0x48. (LOW BITS)\n");

    // i2c_transfer(0b10001101); //4-bit, enable on, backlight on, laagste bits (D3-D0)
    // i2c_transfer(0b10001001); //4-bit, enable off, backlight on, laagste bits (D3-D0)
    // //systim_waits(1);
    ////////////////////////////////////////////////////////////

}
