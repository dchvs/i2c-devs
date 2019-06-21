#ifndef LCD_H
#define LCD_H

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/kobject.h>
#include <linux/io.h>
#include <linux/device.h> // for owner in THIS_MODULE
#include <linux/ioctl.h>
#include <linux/uaccess.h> // put_user

#include <linux/time.h>
#include <linux/delay.h>
#include <linux/random.h>

MODULE_LICENSE("GPL") ;
MODULE_AUTHOR("dchvs") ;
MODULE_DESCRIPTION("Linux kernel module 2") ;
MODULE_VERSION("0.1") ;


#include "shared.h"


#define CONTROLREG                  0x0E
#define STATUSREG                   0x0F


/* =======================================================
    * Setup for RTC
    *
    * Inputs
    * Output
    *        Error code
    * Restrictions
* ======================================================== */
 int i2c_rtc_setup(void) ;

/* =======================================================
    * Fills Rtc Struct with hour data
    *
    * Inputs
    *         struct     : Pointer to i2c_data struct
    * Output
    *        Error code
    * Restrictions
    *        Reads hour in 24-hours format
* ======================================================== */
 int i2c_rtc_readdata(struct i2c_data *) ;

/* =======================================================
    * Sets Rtc hour
    *
    * Inputs
    *         struct     : Rtc struct
    * Output
    *        Error code
    * Restrictions
    *        Time has to have 24-hour format this way: 121200
* ======================================================== */
 int i2c_rtc_sethour(struct rtc) ;


#endif
