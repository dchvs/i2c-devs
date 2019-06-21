#include "test_gpio.h"

#include "ktf/ktf.h"

#include "shared.h"

#include "gpio.h"
// #include "i2c.h"
// #include "lcd.h"
// #include "rtc.h"


TEST(SUCCESS_FAILURE, GPIO_TEST) {
    int ret = 0 ;

    int rand_pin = (int)prandom_u32_max(40) ;
    int rand_state = (int)prandom_u32_max(1) ;

    int rand_bit = (int)prandom_u32_max(32) ;
    int rand_bit_value = (int)prandom_u32_max(1) ;

// ------------ Success cases --------------
    ret = pinMode(rand_pin, rand_state) ;
    EXPECT_INT_EQ(0, ret) ;

    ret = digitalRead(rand_pin) ;
    EXPECT_INT_EQ(0, ret) ;

    ret = digitalWrite(rand_pin, rand_state) ;
    EXPECT_INT_EQ(0, ret) ;

// ------------ Error cases --------------
    ret = pinMode(rand_pin, rand_state) ;
    EXPECT_INT_NE(-ERANGE, ret) ;

    ret = digitalRead(rand_pin) ;
    EXPECT_INT_NE(-ERANGE, ret) ;

    ret = digitalWrite(rand_pin, rand_state) ;
    EXPECT_INT_NE(-ERANGE, ret) ;

}


void add_test_gpio(void){
    ADD_TEST(GPIO_TEST) ;
}
