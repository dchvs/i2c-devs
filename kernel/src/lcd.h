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


// LCD control bits
#define LCD_RS          (1 << 0)
#define LCD_RW          (1 << 1)
#define LCD_EN          (1 << 2)
#define LCD_BACKLIGHT   (1 << 3)


/* =======================================================
    * Writes a command to LCD in 4-bits nibble data
    *
    * Inputs
    *        Command    : 1 byte hex command
    *        Control    : Control mode
    *                     Write command   LCD_EN      0x4
    * Output
    *        Error code
    * Restrictions
    *        Push 1 command at a time to LCD
    *        Increase data length in FIFO x4 times
* ======================================================== */
int i2c_lcd_writecmd(int) ;

/* =======================================================
    * Writes data to LCD in 4-bits nibble data
    *
    * Inputs
    *        Data    : 1 byte Ascii data
    *        Control : Control mode
    *                     Write data      LCD_EN | LCD_RS   0x5
    * Output
    *        Error code
    * Restrictions
    *        Push 1 data byte at a time to LCD
    *        Increase data length in FIFO x4 times
* ======================================================== */
int i2c_lcd_writedata(int) ;

#endif
