#ifndef LCD_H
#define LCD_H


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
    * Set LCD address and has the initialization
    * commands.
    *
    * Inputs
    *             LCD address : Hex address
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int lcdinit(char) ;

/* =======================================================
    * Clear LCD display
    *
    * Inputs
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int lcdclr() ;

/* =======================================================
    * Send data string to LCD by sending 1-char at a time
    *
    * Inputs
    *        String   data
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
int lcdwr(char *) ;


#endif
