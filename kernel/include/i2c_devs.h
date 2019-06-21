#ifndef I2C_DEVS_H
#define I2C_DEVS_H

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
MODULE_DESCRIPTION("Linux kernel module") ;
MODULE_VERSION("0.2") ;

// KTF files
#include "ktf/ktf.h"

// Share library between user and kernel space
#include "shared.h"

// Driver files
#include "gpio.h"
#include "i2c.h"
#include "lcd.h"
#include "rtc.h"

// Test files
#include "add_tests.h"

#define MAJOR_NUM 256
#define GPIO_ADDRESS    0x3F200000
#define I2C_ADDRESS     0x3F804000

#define MSG_SZ 1024


// Class to help create device on /dev/...
static struct class *class ;

// Fops. sysfs logical gpio state
static int pin_state = 0 ;
static struct kobject *led_kobj ;

// Registers pointer
struct gpioRegs *gpioRegsp ;
struct i2cRegs *i2cRegsp ;


///-------------------------------------------------------------------
///---------------------- EXTERN FUNCTIONS ---------------------------
///-------------------------------------------------------------------

// --- gpio
extern int pinMode(int, int) ;
extern int digitalRead(int) ;
extern int digitalWrite(int, int) ;
extern int i2c_write2register(volatile uint32_t *, int, int) ;
extern struct gpioRegs ;

// --- i2c
extern int i2c_enable(int) ;
extern int i2c_clearfifo(void) ;
extern int i2c_transfermode(int) ;
extern int i2c_slaveaddress(int) ;
extern int i2c_fifo(int) ;
extern int i2c_datalength(int) ;
extern int i2c_check_ack(void) ;
extern int i2c_wait_tdone(void) ;
extern int i2c_startTransfer(void) ;
extern int i2c_init(void) ;
extern int i2c_read_block(int, int, int) ;
extern int i2c_write_block(int, int, uint8_t *) ;

extern struct i2cRegs ;

// --- lcd
extern int i2c_lcd_writecmd(int) ;
extern int i2c_lcd_writedata(int) ;
extern char lcd_address ;

// --- rtc
extern int i2c_rtc_setup(void) ;
extern int i2c_rtc_readdata(struct i2c_data *) ;
extern int i2c_rtc_sethour(struct rtc) ;
extern char rtc_address ;

// --- ktf
extern void add_tests(void) ;
extern void add_test_gpio(void) ;
extern void add_test_i2c(void) ;
extern void add_test_lcd(void) ;
extern void add_test_rtc(void) ;

///-------------------------------------------------------------------
///----------------------- FILE OPERATIONS ---------------------------
///-------------------------------------------------------------------

// fops. counter for bytes from  message
static int n = 0 ;
// fops. flags to tell if device is open
volatile static bool is_open = false ;
// fops. buffers for rd/wr messages
static char msg[MSG_SZ], msg1[MSG_SZ] ;


// ioctl
static long etx_ioctl(struct file *, unsigned int, unsigned long) ;
// sysfs
static ssize_t pin_show(struct kobject *, struct kobj_attribute *, char *) ;
static ssize_t pin_store(struct kobject *, struct kobj_attribute *, const char *buf, size_t) ;
// accesing device
static int led_open(struct inode *, struct file *) ;
// reading from device
static ssize_t etx_read(struct file *, char  __user *, size_t , loff_t *) ;
// writing to device
static ssize_t etx_write(struct file *, const char __user *, size_t , loff_t *) ;
// egreasing device
static int led_release(struct inode *, struct file *) ;
// mounting device
static int __init led_init(void) ;
// unmounting device
static void __exit led_exit(void) ;


///----------------------- FILE OPERATIONS -----------------------------
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .read = etx_read,
    .write = etx_write,
    .unlocked_ioctl = etx_ioctl,
    .release = led_release
} ;

#endif
