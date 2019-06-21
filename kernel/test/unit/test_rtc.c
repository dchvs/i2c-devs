#include "test_rtc.h"

#include "ktf/ktf.h"

#include "shared.h"

#include "rtc.h"
#include "gpio.h"
#include "i2c.h"
#include "lcd.h"



TEST(SUCCESS_FAILURE, RTC_TEST) {
    int ret = 0 ;

    int rand_pin = (int)prandom_u32_max(40) ;
    int rand_state = (int)prandom_u32_max(1) ;

    int rand_bit = (int)prandom_u32_max(32) ;
    int rand_bit_value = (int)prandom_u32_max(1) ;
    uint32_t rand_i2c_register = 0 ;

    char rand_secU = (char)prandom_u32_max(9) + '0' ;
    char rand_secD = (char)prandom_u32_max(9) + '0' ;
    char rand_minU = (char)prandom_u32_max(9) + '0' ;
    char rand_minD = (char)prandom_u32_max(9) + '0' ;
    char rand_hourU = (char)prandom_u32_max(9) + '0' ;
    char rand_hourD = (char)prandom_u32_max(9) + '0' ;

    // ------------ Success cases --------------
    ret = i2c_rtc_setup() ;
    EXPECT_INT_EQ(0, ret) ;

    struct i2c_data q ;
    ret = i2c_rtc_readdata(&q) ;
    EXPECT_INT_EQ(0, ret) ;

    struct rtc q1 = {rand_secU, rand_secD, rand_minU, \
                     rand_minD, rand_hourU, rand_hourD} ;

    ret = i2c_rtc_sethour(q1);
    EXPECT_INT_EQ(0, ret) ;

    // ------------ Error cases --------------

    struct rtc q2 ;
    ret = i2c_rtc_sethour(q2);
    EXPECT_INT_EQ(-ERANGE, ret) ;
}


void add_test_rtc(void){
    ADD_TEST(RTC_TEST) ;
}
