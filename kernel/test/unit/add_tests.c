#include "add_tests.h"

#include "ktf/ktf.h"

#include "shared.h"

#include "gpio.h"
#include "i2c.h"
#include "lcd.h"
#include "rtc.h"

#include "test_gpio.h"
#include "test_i2c.h"
#include "test_lcd.h"
#include "test_rtc.h"


void add_tests(void){
    add_test_gpio() ;
   add_test_i2c() ;
   add_test_lcd() ;
   add_test_rtc() ;
}
