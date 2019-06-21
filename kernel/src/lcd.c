#include "lcd.h"
#include "i2c.h"
#include "shared.h"


char lcd_address = 0 ;


///-------------------------------------------------------------------
///--------------------- I2C LCD FUNCTIONS ---------------------------
///-------------------------------------------------------------------

int i2c_lcd_writecmd(int cmd){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    if(cmd < 0 || cmd > 255){ // Ascii command
      printk("i2c_lcd_writecmd. The value inserted does not"
          "corresponds to cmd range ") ;
      return -ERANGE ;
    }

    int ret ;

    // Fills fifo for lcd 4-bit operation mode
    uint8_t nibbledata[4] = {(0xf0 &  cmd)       | LCD_BACKLIGHT | LCD_EN,
                             (0xf0 &  cmd)       | LCD_BACKLIGHT,
                             (0xf0 & (cmd<<4))   | LCD_BACKLIGHT | LCD_EN,
                             (0xf0 & (cmd<<4))   | LCD_BACKLIGHT } ;

    // Write tuple to LCD througth I2C
    ret = i2c_write_block(lcd_address, 4, nibbledata) ;
    if(ret != 0)
        return ret ;

    return 0 ;
}

int i2c_lcd_writedata(int data){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    if(data < 0 || data > 255){ // Ascii data
      printk("i2c_lcd_writedata. The value inserted does not"
          "corresponds to data ascii range ") ;
      return -ERANGE ;
    }
    // 7-bits address
    if(lcd_address < 0 || lcd_address > 128){
      printk("i2c_lcd_writedata. The value inserted does not"
          "corresponds to valid address ") ;
      return -ERANGE ;
    }

    int ret ;

  // Fills fifo for lcd 4-bit operation mode
    uint8_t nibbledata[4] = {(0xf0 &  data)       | LCD_BACKLIGHT | LCD_EN | LCD_RS,
                             (0xf0 &  data)       | LCD_BACKLIGHT,
                             (0xf0 & (data<<4))   | LCD_BACKLIGHT | LCD_EN | LCD_RS,
                             (0xf0 & (data<<4))   | LCD_BACKLIGHT } ;

    // Write tuple to LCD througth I2C
    ret = i2c_write_block(lcd_address, 4, nibbledata) ;
    if(ret != 0)
        return ret ;

    return 0 ;
}
