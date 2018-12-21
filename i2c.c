#include "i2c.h"

I2C i2c;
extern volatile unsigned int* REG;
void i2c_init(){
    i2c.base = (int*)(I2C_BASE);

   
    gpio_set_alt(2, 0);  //SDA
    gpio_set_alt(3, 0);  //SCL
}


void i2c_transfer(unsigned char send_value_byte_deel1, unsigned char send_value_byte_deel2 ){
    i2c.base[I2C_A] = 0x3f; // I2C Slave Address (3f = 16*2 Display) kan je controleren met 'i2cdetect 1'
    
    i2c.base[I2C_DLEN] |= 2;            // twee bytes na elkaar sturen
    i2c.base[I2C_FIFO] |= send_value_byte_deel1;            // Deel 1
    i2c.base[I2C_FIFO] |= send_value_byte_deel2;            // Deel 2
    i2c.base[I2C_S] |= I2C_CLEAR_STATUS;    // Reset status bits (see #define)
    i2c.base[I2C_C] |= I2C_START_WRITE;     // Start Write (see #define)

    
    wait_i2c_done();
    
}

// Delay voor I2C transactie
void wait_i2c_done() {
 
       // int timeout = 50;
       // while((!((I2C_S) & I2C_DONE)) && --timeout) {
        while((!((i2c.base[I2C_S]) & i2c.base[I2C_DONE]))) {
            //usleep(1000);
            systim_waitus(2000);
        }
}

void lcd_init(){
     /*LCD werkt met 11 (of 7) bits:
        RS:     H=Data Input    L=Instruction Input
        R/W:    H=Read          l=Write
        E:      H/l Enable Signal
        DB0->DB7:   Data bus 8 bit transfer
        (DB4->DB7:   Data bus 4 bit transfer)

        De verschillende fases (bytes) om data op de LCD weer te geven  
                                    RS  RW  DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0     
        Stap 1: Clear Display ->    0   0   0   0   0   0   0   0   0   1       -> 0x01
        Stap 2: Return Home   ->    0   0   0   0   0   0   0   0   1   .       -> 0x02
        Stap 3: Entry Mode S. ->    0   0   0   0   0   0   0   1   I/D S       -> 0x06 (Shift the display to the right)
        Stap 4: Display ON/OFF->    0   0   0   0   0   0   1   D   C   B       -> 0x0C
        Stap 5: Cursor/Display->    0   0   0   0   0   1   S/C R/L .   .       -> 0x1C (Shift the curser to the right)
        Stap 6: Function Set  ->    0   0   0   0   1   DL  N   F   .   .       -> 0x38 (8-bit bus; 2-line display mode; 5*8 dots format)
        Stap 7: CGRAM address ->    0   0   0   1   AC5 AC4 AC3 AC2 AC1 A0      ->
        Stap 8: DDRAM address ->    0   0   0   AC6 AC5 AC4 AC3 AC2 AC1 A0
        Stap 9:
        Stap 10:Write data    ->    1   0   .D7  D6  D5  D4  .D3  D2  D1  D0      -> 0x2F4 (=O), 0x2B4 (=K)
        */

        //i2c_transfer(0x00, 0x01);   // Clear Display
        //i2c_transfer(0x00,0x06);    // Return Home
        i2c_transfer(0x00,0x0C);    // Display Aan
        //i2c_transfer(0x00,0x38);    //
        // i2c_transfer(0x02,0xF4);    // Letter O
        //i2c_transfer(0x02,0xB4);    // Letter K
}
