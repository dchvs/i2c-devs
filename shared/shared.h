#ifndef SHARED_H
#define SHARED_H

#define DEV_NAME "i2c_devs"

#define HIGH   1
#define LOW    0

// IOCTL switch cases
enum CMD{CMD_PINMODE=100, CMD_DIGITALREAD=101,
         CMD_DIGITALWRITE=102, CMD_I2C_INIT=103,
         CMD_I2C_LCD_SETADDRESS=104, CMD_I2C_LCD_WRITECMD=105,
         CMD_I2C_LCD_WRITEDATA=106, CMD_I2C_READFROMLCD=107, CMD_I2C_FIFO=108,
         CMD_I2C_CLEARFIFO=109, CMD_I2C_TRANSFERMODE=110,
         CMD_I2C_SLAVEADDRESS=111, CMD_I2C_DATALENGTH=112,
         CMD_I2C_STARTTRANSFER=113, CMD_I2C_RTC_READDATA=114,
         CMD_I2C_RTC_SETADDRESS=115, CMD_I2C_RTC_SETHOUR=116
      } ;

// GPIO struct
struct data {
    volatile int pinMode  ;
    volatile int pin ;
    volatile int pin_state ;
} ;

// I2C struct
struct i2c_data {
    volatile char address ;
    volatile char cmd ;
    volatile char data ;
    volatile char rtc[50] ;
};

// RTC struct
struct rtc {
  volatile char sec_unid ;
  volatile char sec_dec  ;
  volatile char min_unid ;
  volatile char min_dec ;
  volatile char hour_unid ;
  volatile char hour_dec ;
} ;

#endif
