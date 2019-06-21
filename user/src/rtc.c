#include "rtc.h"
#include "i2c.h"

int i2c_rtc_setaddress(char address){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send device address through i2c_data struct
    struct i2c_data q = {address, 0, 0} ;
    int ret = ioctl(fd, CMD_I2C_RTC_SETADDRESS, &q) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;
    return 0 ;
}
int i2c_rtc_sethour(char *hour){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send hour digits through rtc struct
    struct rtc q = {hour[5], hour[4], hour[3], hour[2], hour[1], hour[0]} ;

    int ret = ioctl(fd, CMD_I2C_RTC_SETHOUR, &q) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;
    return 0 ;
}

int i2c_rtc_readdata(char *time){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send device address through i2c_data struct
    struct i2c_data q = {0, 0, 0} ;
    int ret = ioctl(fd, CMD_I2C_RTC_READDATA, &q) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;

    // Save time into string by parameter return
    memcpy(time, q.rtc, sizeof(q.rtc)) ;

    return 0 ;
}


int rtcinit(char address){
    // Initialize I2C protocol
    i2c_init() ;
    // Set RTC address
    i2c_rtc_setaddress(address) ;

    return 0 ;
}
int removeChar(char *q, char ch){
    int i=0, j=0 ;
    char t[10] ;
    while (i < strlen(q)) {
        if(q[i] != ch){
            t[j] = q[i] ;
            j++ ;
        }
      i++ ;
    }
    t[j] = '\0' ;
    // Save the clean string to return
    memcpy(q, t, sizeof(t)) ;

    return 0 ;
}
int rtchour(char *hour){
    // Remove : from hour
    removeChar(hour, ':') ;
    // Send hour to RTC device
    i2c_rtc_sethour(hour) ;

    return 0 ;
}
