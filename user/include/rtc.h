#ifndef RTC_H
#define RTC_H


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

#include "shared.h"



/* =======================================================
    * Set device address
    *
    * Inputs
    *         Address     : RTC address
    * Output
    *        Error code
    * Restrictions
* ======================================================== */
int i2c_rtc_setaddress(char) ;

/* =======================================================
    * Sets Rtc hour
    *
    * Inputs
    *         Hour     : 121212
    * Output
    *        Error code
    * Restrictions
    *        Time has to have 24-hour format this way: 121200
* ======================================================== */
int i2c_rtc_sethour(char *) ;

/* =======================================================
    * Get the hour in string
    *
    * Inputs
    *         Pointer to char : Get the hour by parameter return
    * Output
    *        Error code
    * Restrictions
    *        Reads hour in 24-hours format
* ======================================================== */
int i2c_rtc_readdata(char *) ;

/* =======================================================
    * Initialize RTC
    *
    * Inputs
    *         RTC address
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int rtcinit(char) ;

/* =======================================================
    * Deletes char ':' to hour string
    *
    * Inputs
    *         Hour string: 12:12:12
    *         Char to remove:  ':'
    * Output
    *        Error code
    * Restrictions
    *        Reads hour in 24-hours format
* ======================================================== */
int removeChar(char *, char) ;

/* =======================================================
    * Send hour string to RTC
    *
    * Inputs
    *         Hour in string format : 12:12:12
    * Output
    *        Error code
    * Restrictions
    *        Reads hour in 24-hours format
* ======================================================== */
int rtchour(char *) ;


#endif
