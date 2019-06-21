#include "gpio.h"


int pinMode(int pin, int pinMode){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send pin mode through data struct
    struct data q = {pinMode, pin, 0} ;
    int ret = ioctl(fd, CMD_PINMODE, &q) ;

    if (ret < 0){
		perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;

    return 0 ;
}
int digitalRead(int pin){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send pin through data struct
    struct data q = {0, pin, 0} ;

    int ret = ioctl(fd, CMD_DIGITALREAD, &q) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;
    return 0 ;
}
int digitalWrite(int pin, int pin_state){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send pin and pin state through data struct
    struct data q = {0, pin, pin_state} ;
    int ret = ioctl(fd, CMD_DIGITALWRITE, &q) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;
    return 0 ;
}
