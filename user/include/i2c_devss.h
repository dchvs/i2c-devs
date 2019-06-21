#ifndef I2C_DEVSS_H
#define I2C_DEVSS_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>      /* open */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>     /* exit */
#include <string.h>
#include <getopt.h>


#define LCD_ADDR    0x27
#define RTC_ADDR    0x68
#define LCD_REFRESH_TIME 300000

static int verbose_flag;


/* =======================================================
    * Run i2c-devs program. It's a loop that reads hour
    * from RTC and displaying it in LCD.
    *
    * Inputs
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */


#endif
