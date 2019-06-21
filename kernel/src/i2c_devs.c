#include "i2c_devs.h"


KTF_INIT() ;


///-------------------------------------------------------------------
///------------------ FILE OPERATIONS FUNCTIONS ----------------------
///-------------------------------------------------------------------

///----------------------- IOCTL FUNCTION ---------------------------
static long etx_ioctl(struct file *fp, unsigned int cmd, unsigned long arg){
    switch (cmd) {
    case CMD_PINMODE:
    {
        struct data q ;
        if(copy_from_user(&q, (void *)arg, sizeof (struct data))){
            printk("Error - copyfromuser no hace alloc de memoria de datap") ;
            return -EFAULT ;
        }
        printk("pinmode:: q.pin=%d, q.pinMode=%d",q.pin, q.pinMode ) ;
        pinMode(q.pin, q.pinMode) ;
        break ;
    }
    case CMD_DIGITALREAD:
    {
        struct data q ;
        if(copy_from_user(&q, (void *)arg, sizeof (struct data))){
            printk("Error - copyfromuser no hace alloc de memoria de datap") ;
            return -EFAULT ;
        }
        digitalRead(q.pin) ;
        break ;
    }
    case CMD_DIGITALWRITE:
    {
        struct data q ;
        if(copy_from_user(&q, (void *)arg, sizeof (struct data))){
            printk("Error - copyfromuser no hace alloc de memoria de datap") ;
            return -EFAULT ;
        }
        printk("digitalWrite:: q.pin=%d, q.pin_state=%d\n", q.pin, q.pin_state ) ;
        digitalWrite(q.pin, q.pin_state) ;
        break ;
    }
    case CMD_I2C_INIT:
    {
        i2c_init() ;
        break ;
    }
    case CMD_I2C_LCD_SETADDRESS:
    {
        struct i2c_data q ;
        if(copy_from_user(&q, (void *)arg, sizeof (struct i2c_data))){
            printk("Error - copyfromuser no hace alloc de memoria de datap") ;
            return -EFAULT ;
        }
        printk("i2c_init:: q.address=%d\n", q.address) ;

        lcd_address = q.address ;

        break ;
    }
    case CMD_I2C_LCD_WRITECMD:
    {
        struct i2c_data q ;
        if(copy_from_user(&q, (void *)arg, sizeof (struct i2c_data))){
            printk("Error - copyfromuser no hace alloc de memoria de datap") ;
            return -EFAULT ;
        }
        printk("i2c_lcd_fillfifo:: q.cmd=%d\n", q.cmd) ;
        i2c_lcd_writecmd(q.cmd) ;
        break ;
    }
    case CMD_I2C_LCD_WRITEDATA:
    {
        struct i2c_data q ;
        if(copy_from_user(&q, (void *)arg, sizeof (struct i2c_data))){
            printk("Error - copyfromuser no hace alloc de memoria de datap") ;
            return -EFAULT ;
        }
        i2c_lcd_writedata(q.data) ;
        break ;
    }
    case CMD_I2C_RTC_READDATA:
    {
      struct i2c_data q ;
      i2c_rtc_readdata(&q) ;
      if(copy_to_user((void *)arg, &q, sizeof (struct i2c_data))){
          printk("Error - copyfromuser no hace alloc de memoria de datap") ;
          return -EFAULT ;
      }
      break ;
    }
    case CMD_I2C_RTC_SETHOUR:
    {
      struct rtc q ;
      if(copy_from_user(&q, (void *)arg, sizeof (struct rtc))){
          printk("Error - copyfromuser no hace alloc de memoria de datap") ;
          return -EFAULT ;
      }
      i2c_rtc_sethour(q) ;
      break ;
    }
    case CMD_I2C_RTC_SETADDRESS:
    {
        struct i2c_data q ;
        if(copy_from_user(&q, (void *)arg, sizeof (struct i2c_data))){
            printk("Error - copyfromuser no hace alloc de memoria de datap") ;
            return -EFAULT ;
        }
        rtc_address = q.address ;

        break ;
    }

    default:
        printk("default entry\n") ;
        break ;
    }

    return 0 ;
}

///------------------ ACCESING DEVICE FUNCTION ----------------------
static int led_open(struct inode *inodep, struct file *fp){
    if(is_open){
        printk("Module was access and still busy\n") ;
        return -EBUSY ;
    }
    is_open = true ;
    printk("******* Accesing device - static int dev_open(..)\n") ;
    try_module_get(THIS_MODULE) ;

    return 0 ;
}

///--------------------- READING FROM DEVICE ---------------------------
static ssize_t etx_read(struct file *fp, char  __user *buffer, size_t len, loff_t *offset){
    // bytes read counter
    uint32_t i = 0 ;

    if(offset == NULL){
        printk("There's nothing to read \n") ;
        return -EINVAL ;
    }
    if(*offset >= n){
        return 0 ;
    }

    printk("Reading from device...") ;
    while (*offset < n && i < len) {
        put_user(msg[*offset], &buffer[i]) ;
        *offset = *offset + 1 ;
        i++ ;
    }
    printk("Device message was sent to userspace - static ssize_t(..)\n") ;

    return i ;
}
///--------------------- WRITING TO DEVICE ---------------------------
static ssize_t etx_write(struct file *fp, const char __user *buffer, size_t len, loff_t *offset){
    uint32_t i = 0 ;

    if(offset == NULL){
        printk("Any message\n") ;
        return -EINVAL ;
    }
    if(*offset >= MSG_SZ)
        return 0 ;

    while (i<len && *offset<MSG_SZ) {
        get_user(msg1[*offset], &buffer[i]) ;
        *offset = *offset + 1 ;
        i++ ;
    }
    printk("msg1 = %s", msg1) ;

    return i ;
}

///---------------------- EGRESSING DEVICE ----------------------------
static int led_release(struct inode *inodep, struct file *fp){
    printk("******* Egressing device - static int dev_release(..)\n") ;
    if(!is_open){
        printk("Device was never opened\n") ;
        return -EBUSY ;
    }
    is_open = false ;
    module_put(THIS_MODULE) ;

    return 0 ;
}

///-------------------------------------------------------------------
///----------------------- SYSFS FUNCTIONS ---------------------------
///-------------------------------------------------------------------
static ssize_t pin_show(struct kobject *kobj, struct kobj_attribute *kobj_attr, char *buf){ // hacerlo como kobject
    return sprintf(buf, "pin_state=%d\n", pin_state) ;
}
static ssize_t pin_store(struct kobject *kobj, struct kobj_attribute *kobj_attr, const char *buf, size_t count){ // hacerlo como kobject
    sscanf(buf, "%du", &pin_state) ;
    return (ssize_t)count ;
}

static struct kobj_attribute led_attr = __ATTR(led_pwr, 0660, pin_show, pin_store) ;



///----------------------- MOUNTING DEVICE -----------------------------
static int __init led_init(void){
    int status ;

    // Register & creates device
    status = register_chrdev(MAJOR_NUM, DEV_NAME, &fops) ;
    if (status < 0){
        printk("Mouting module error\n") ;
        return  -ENODEV ;
    }

    class = class_create(THIS_MODULE, DEV_NAME) ;
    device_create(class, NULL, MKDEV(MAJOR_NUM, 0), NULL, DEV_NAME"%d", 0) ;

    // MAP GPIO MEMORY
    gpioRegsp = ioremap(GPIO_ADDRESS, sizeof (struct gpioRegs)) ;
    i2cRegsp = ioremap(I2C_ADDRESS, sizeof (struct i2cRegs)) ;

    // SYSFS SYSCALLS
    led_kobj = kobject_create_and_add("led_ctrl_pwr", kernel_kobj) ;
    if(!led_kobj){
        printk("Error creating devices\n") ;
        return -ENOMEM ;
    }
    status = sysfs_create_file(led_kobj, &led_attr.attr) ;
    if(status){
        printk("Failed to register sysfs for led")    ;
        return status ;
    }

    // Setting some message
    strncpy(msg, "<1> This is a msg from kernel space\n", MSG_SZ-1) ;
    n = (int)strlen(msg) ;

    // Add tests
    add_tests() ;
    tlog(T_INFO, "Tests added");

    printk("<1> Mounting module - major is: %d \n", MAJOR_NUM) ;

    return 0 ;
}
///----------------------- UNMOUNTING DEVICE -----------------------------
static void __exit led_exit(void){
    // Unmap
    iounmap(gpioRegsp) ;
    iounmap(i2cRegsp) ;

    // Clean sysfs object
    kobject_put(led_kobj) ;

    // Unregister and deletes device
    device_destroy(class, MKDEV(MAJOR_NUM, 0)) ;
    class_destroy(class) ;
    unregister_chrdev(MAJOR_NUM, DEV_NAME) ;

    // Remove tests
    KTF_CLEANUP() ;

    printk("<2> Unmounting module\n") ;
}

module_init(led_init) ;
module_exit(led_exit) ;
