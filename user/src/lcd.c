#include "lcd.h"
#include "i2c.h"


int lcdinit(char address){
    i2c_init() ;
    i2c_lcd_setaddress(address) ;

    // Clear display
    i2c_writecmd2lcd(0x01) ;
    // Place cursor to home
    i2c_writecmd2lcd(0x02) ;
    // Sets LCD 4-bits operation mode
    i2c_writecmd2lcd(0x28) ;
    // Initialize
    i2c_writecmd2lcd(0x0F) ;

    return 0 ;
}
int lcdclr(){
    // Place cursor to home
    i2c_writecmd2lcd(0x02) ;
    // Clear cursor
    i2c_writecmd2lcd(0x0C) ;
}
int lcdwr(char *byte){
    size_t i = 0 ;

    do {
        // Send 1-byte at a time to LCD
        i2c_writedata2lcd(byte[i]) ;
    }   while(++i < strlen(byte)) ;

    return 0 ;
}
