#ifndef GPIO_H
#define GPIO_H

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

#define STATE_HIGH    1
#define STATE_LOW     0
#define MODE_INPUT    0
#define MODE_OUTPUT   1


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

#endif
