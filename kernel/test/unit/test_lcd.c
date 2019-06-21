#include "test_lcd.h"

#include "ktf/ktf.h"

#include "shared.h"

#include "gpio.h"
#include "i2c.h"
#include "lcd.h"
#include "rtc.h"


TEST(SUCCESS_FAILURE, LCD_TEST) {
    int ret = 0 ;

    int rand_cmd = (int)prandom_u32_max(255) ;
    int rand_data = (int)prandom_u32_max(255) ;

    int rand_cmd_fail = (int)get_random_int()   | 0xffff ;
    int rand_data_fail = (int)get_random_int()  | 0xffff ;


    // ------------ Success cases --------------
    ret = i2c_lcd_writecmd(rand_cmd) ;
    EXPECT_INT_EQ(0, ret) ;

    ret = i2c_lcd_writedata(rand_data) ;
    EXPECT_INT_EQ(0, ret) ;

    // ------------ Error cases --------------
    ret = i2c_lcd_writecmd(rand_cmd_fail) ;
    EXPECT_INT_EQ(-ERANGE, ret) ;

    ret = i2c_lcd_writedata(rand_data_fail) ;
    EXPECT_INT_EQ(-ERANGE, ret) ;
}


void add_test_lcd(void){
    ADD_TEST(LCD_TEST) ;
}
