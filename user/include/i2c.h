#ifndef I2C_H
#define I2C_H


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
    * Initializes I2C protocol hardware: SDA & SCL wires
    *
    * Inputs
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
 int i2c_init(void) ;


 /* =======================================================
     * Set address for device
     *
     * Inputs
     *        Address : Hex address
     * Output
     *        Error code
     * Restrictions
     *        Consistent data
 * ======================================================== */
int i2c_lcd_setaddress(char address) ;

/* =======================================================
    * Write command to device
    *
    * Inputs
    *        Command  : Hex command
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int i2c_writecmd2lcd(char cmd) ;

/* =======================================================
    * Write data byte to device
    *
    * Inputs
    *        Data         : Write 1-char data to LCD
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int i2c_writedata2lcd(char data) ;

#endif
