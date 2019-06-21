#ifndef I2C_H
#define I2C_H

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
MODULE_DESCRIPTION("Linux kernel module 2") ;
MODULE_VERSION("0.1") ;


//-------------------- I2C -------------------
// I2C Control register
#define I2C_C_EN        (1 << 15)
#define I2C_C_INTR      (1 << 10)
#define I2C_C_INTT      (1 << 9)
#define I2C_C_INTD      (1 << 8)
#define I2C_C_ST        (1 << 7)
#define I2C_C_CLR       (1 << 4)
#define I2C_C_READ      (1 << 0)
#define I2C_C_WRITE     (0 << 0)

// I2C Status register
#define I2C_S_CLKT      (1 << 9)
#define I2C_S_ERR       (1 << 8)
#define I2C_S_RXF       (1 << 7)
#define I2C_S_TXE       (1 << 6)
#define I2C_S_RXD       (1 << 5)
#define I2C_S_TXD       (1 << 4)
#define I2C_S_RXR       (1 << 3)
#define I2C_S_TXW       (1 << 2)
#define I2C_S_DONE      (1 << 1)
#define I2C_S_TA        (1 << 0)

#define CLEAR_STATUS  (I2C_S_CLKT | I2C_S_ERR | I2C_S_DONE)

// cambiarlos por
#define I2C_CTRL_EN_BIT             15
#define I2C_CTRL_ST_BIT             7
#define I2C_CTRL_CLEAR_FIFO_BIT     4
#define I2C_CTRL_TRANSFER_MODE_BIT  0

#define I2C_S_CLKTIMEOUT_BIT  9
#define I2C_S_ERRACK_BIT      8
#define I2C_S_DONETRANSF_BIT  1

 
#define I2C_SDA_PIN   2
#define I2C_SCL_PIN   3
#define I2C_ALT_MODE  4



// I2C continous memory mapping
struct i2cRegs {
    volatile uint32_t I2C_CTRL ;
    volatile uint32_t I2C_STATUS ;
    volatile uint32_t I2C_DATALEN ;
    volatile uint32_t I2C_SLAVEADD ;
    volatile uint32_t I2C_DATAFIFO ;
    volatile uint32_t I2C_CLKDIV ;
    volatile uint32_t I2C_DATADELAY ;
    volatile uint32_t I2C_CLKTIMEOUT ;
};



/* =======================================================
    * Enables I2C protocol
    *
    * Inputs
    *        Enable       : Enable logical state
    *                         Controller disabled  0x0
    *                         Controller enabled   0x1
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
 int i2c_enable(int) ;

/* =======================================================
    * Clears the I2C FIFO register
    *
    * Inputs
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
 int i2c_clearfifo(void) ;

/* =======================================================
    * Enables I2C protocol
    *
    * Inputs
    *        Transfer mode: Packet transfer direction
    *                         Write     0x0
    *                         Read      0x1
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
 int i2c_transfermode(int) ;

/* =======================================================
    * Sets the I2C slave device address
    *
    * Inputs
    *        Address : Device I2C bus address
    * Output
    *        Error code
    * Restrictions
    *        Supports 7 bits addressing (128 devices)
* ======================================================== */
 int i2c_slaveaddress(int) ;

/* =======================================================
    * Write 1 byte data to FIFO
    *
    * Inputs
    *        Data byte : 1 byte data
    * Output
    *        Error code
    * Restrictions
    *        Stacks 1 byte size data chunks at a time
* ======================================================== */
 int i2c_fifo(int) ;

/* =======================================================
    * Sets the number of data bytes in a transfer
    *
    * Inputs
    *        Data length : Number of data bytes
    * Output
    *        Error code
    * Restrictions
    *        Consistentance with number of data bytes
    *        stacked into FIFO
* ======================================================== */
 int i2c_datalength(int) ;


/* =======================================================
    * Cheacks acknowledgement
    *
    * Inputs
    * Output
    *        Error code
    * Restrictions
    *        Timeouts if no acknowledgement
* ======================================================== */
 int i2c_check_ack(void) ;

/* =======================================================
    * Wait for transfer done
    *
    * Inputs
    * Output
    *        Error code
    * Restrictions
    *        Timeout if transfer is not done
* ======================================================== */
 int i2c_wait_tdone(void) ;

/* =======================================================
    * Starts a new transfer
    *
    * Inputs
    * Output
    *        Error code
    * Restrictions
* ======================================================== */
 int i2c_startTransfer(void) ;

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
    * Reads from a particular device register
    *
    * Inputs
    *         Address              :  Device address
    *         Register             :  Device register address
    *                                 to start reading at
    *         Block size to read   :  Bytes number to read
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
 int i2c_read_block(int addr, int reg, int block_size) ;

/* =======================================================
    * Writes to a particular device register
    *
    * Inputs
    *         Address          :  Device address
    *         Size             :  Tuple size
    *         Content          :  1-byte data tuple
    * Output
    *        Error code
    * Restrictions
    *        Consistent data
* ======================================================== */
 int i2c_write_block(int addr, int size, uint8_t *content) ;


#endif
