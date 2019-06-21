#include "i2c_devss.h"

// Share library between user and kernel space
#include "shared.h"

// Program libraries
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"
#include "lcd.h"





int main(int argc, char *argv[]) {
    // Set LCD I2C bus address
    lcdinit(LCD_ADDR) ;
    // Set RTC I2C bus address
    rtcinit(RTC_ADDR) ;

    rtchour("12:12:12") ;

    char time[50] ;
    printf("%s\n", time);
    i2c_rtc_readdata(&time) ;
    printf("%s\n", time);

    return 0;
}
