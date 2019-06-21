#include "i2c.h"


int i2c_init(){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Call I2C init function
    int ret = ioctl(fd, CMD_I2C_INIT) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;
    return 0 ;
}
int i2c_lcd_setaddress(char address){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send address through i2c_data struct
    struct i2c_data q = {address, 0, 0} ;
    int ret = ioctl(fd, CMD_I2C_LCD_SETADDRESS, &q) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;
    return 0 ;
}
int i2c_writecmd2lcd(char cmd){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send command through i2c_data struct
    struct i2c_data q = {0, cmd, 0} ;
    int ret = ioctl(fd, CMD_I2C_LCD_WRITECMD, &q) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;
    return 0 ;
}
int i2c_writedata2lcd(char data){
    // Open device file
    int fd = open("/dev/"DEV_NAME"0", O_RDWR) ;
    if(fd < 0) {
        perror("Error opening file!\n");
        return -1 ;
    }
    // Send data through i2c_data struct
    struct i2c_data q = {0, 0, data} ;
    int ret = ioctl(fd, CMD_I2C_LCD_WRITEDATA, &q) ;

    if (ret < 0){
        perror("Error ioctling file!\n");
        return -1 ;
    }
    close(fd) ;
    return 0 ;
}
