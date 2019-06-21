#ifndef GPIO_H
#define GPIO_H

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


#define STATE_HIGH    1
#define STATE_LOW     0
#define MODE_INPUT    0
#define MODE_OUTPUT   1



// GPIO continous memory mapping
struct gpioRegs {
    volatile uint32_t GPIO_FS[6] ;
    volatile uint32_t GPIO_RESERVED ;
    volatile uint32_t GPIO_SET[2] ;
    volatile uint32_t GPIO_RESERVED1 ;
    volatile uint32_t GPIO_CLR[2] ;
    volatile uint32_t GPIO_RESERVED2 ;
    volatile uint32_t GPIO_LEVEL[2] ;
} ;



/* =======================================================
    * Sets the pin operation mode
    *
    * Inputs
    *        Pin       : Board GPIOs
    *        Pinmode   : Operation modes in 3 bits.
    *                        Input          0x0
    *                        Output         0x1
    *                        Alt. func. 0   0x4
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int pinMode(int, int) ;

/* =======================================================
    * Makes a digital read from board's pin
    *
    * Inputs
    *        Pin       : Board GPIOs
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int digitalRead(int) ;

/* =======================================================
    * Makes a digital write to board's pin
    *
    * Inputs
    *        Pin       : Board GPIOs
    *        Pin state : Logical state
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int digitalWrite(int, int) ;

/* =======================================================
    * Writes to a 32 bits register
    *
    * Inputs
    *        Register       : 32 bits register
    *        Bit value      : Bit logical state
    *        Bit            : Bit offset
    * Output
    *        Error code
    * Restrictions
    *        Only handles 1 bit writes
* ======================================================== */
int i2c_write2register(volatile uint32_t *, int, int) ;

#endif
