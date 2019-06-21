#include "i2c.h"
#include "gpio.h"
#include "shared.h"


extern struct i2cRegs *i2cRegsp ;

int i2c_enable(int en){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    if(en < 0 || en > 1){
      printk("i2c_enable. The value inserted does not "
          "corresponds to enable state ");
      return -ERANGE ;
    }

    // Enables i2c hardware from Control Register
    int ret = i2c_write2register(&(i2cRegsp->I2C_CTRL), en, I2C_CTRL_EN_BIT) ;
    if(ret != 0)
        return ret ;

    return 0 ;
}
int i2c_clearfifo(void){
    // Clears protocol FIFO from Control Register
    int ret = i2c_write2register(&(i2cRegsp->I2C_CTRL), 1, I2C_CTRL_CLEAR_FIFO_BIT) ;
    if(ret != 0)
        return ret ;

    return 0 ;
}
int i2c_transfermode(int mode){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    if(mode < 0 || mode > 1){
      printk("i2c_transfermode. The value inserted does not "
          "corresponds to valid transfer mode ") ;
      return -ERANGE ;
    }

    // Sets transfer mode for comunication (Read(1) or Write(0))
    int ret = i2c_write2register(&(i2cRegsp->I2C_CTRL), mode, I2C_CTRL_TRANSFER_MODE_BIT) ;
    if(ret != 0)
        return ret ;

    return 0 ;
}
int i2c_slaveaddress(int address){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    // 7-bits address
    if(address < 0 || address > 128){
      printk("i2c_slaveaddress. The value inserted does not"
          "corresponds to valid address ") ;
      return -ERANGE ;
    }

    // Sets slave address (7-bits) to comunicate to
    i2cRegsp->I2C_SLAVEADD = (uint32_t)address ;

    return 0 ;
}
int i2c_fifo(int data){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    // Ascii data
    if(data < 0 || data > 255){
      printk("i2c_fifo. The value inserted does not"
          "corresponds to valid address ") ;
      return -ERANGE ;
    }

    // Stacks 1-byte data to FIFO
    i2cRegsp->I2C_DATAFIFO  = (uint32_t)data ;

    return 0 ;
}
int i2c_datalength(int bytes){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    // 15-bits data length range
    if(bytes < 0 || bytes > 32768){
      printk("i2c_datalength. The value inserted does not"
          "corresponds to FIFO size ") ;
      return -ERANGE ;
    }
    // Sets bytes number of FIFO stack
    i2cRegsp->I2C_DATALEN    = (uint32_t)bytes ;

    return 0 ;
}


int i2c_check_ack(void){
    int timeout = 100 ;
    // Polling acknowledgement
    while(((i2cRegsp->I2C_STATUS & I2C_S_ERR) >> I2C_S_ERRACK_BIT) && --timeout){
        udelay(500) ;
    }

    if(timeout == 0){
        printk("Error: timeout on i2c_check_ack()") ;
        return -ETIME ;
    }

    return 0 ;
}

int i2c_wait_tdone(void){
    int timeout = 100 ;
    // Polling transfer
    while(!((i2cRegsp->I2C_STATUS & I2C_S_DONE) >> I2C_S_DONETRANSF_BIT) && --timeout)
        udelay(500) ;

    if(timeout == 0){
        printk("Error, timeout on i2c_wait_tdone()") ;
        return -ETIME ;
    }

    return 0 ;
}

int i2c_startTransfer(void){
    int ret ;

    // Clear status
    ret = i2c_write2register(&(i2cRegsp->I2C_STATUS), 1, I2C_S_CLKTIMEOUT_BIT) ;
    if(ret != 0)
        return ret ;

    ret = i2c_write2register(&(i2cRegsp->I2C_STATUS), 1, I2C_S_ERRACK_BIT) ;
    if(ret != 0)
        return ret ;

    ret = i2c_write2register(&(i2cRegsp->I2C_STATUS), 1, I2C_S_DONETRANSF_BIT) ;
    if(ret != 0)
        return ret ;

    // This actually starts transfer
    ret = i2c_write2register(&(i2cRegsp->I2C_CTRL),   1, I2C_CTRL_ST_BIT) ;
    if(ret != 0)
        return ret ;

    return 0 ;
}

int i2c_init(void){
    int ret ;

    // Enable protocol
    ret = i2c_enable(1) ;
    if(ret != 0)
        return ret ;

    // Sets pin to SDA mode
    ret = pinMode(I2C_SDA_PIN, I2C_ALT_MODE) ;
    if(ret != 0)
        return ret ;

    // Sets pin to SCL mode
    ret = pinMode(I2C_SCL_PIN, I2C_ALT_MODE) ;
    if(ret != 0)
        return ret ;

    return 0 ;
}

int i2c_read_block(int addr, int reg, int block_size){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    // 7-bits address
    if(addr < 0 || addr > 128){
      printk("i2c_read_block. The value inserted does not"
          "corresponds to 7-bits address ") ;
      return -ERANGE ;
    }
    // Limiting device register bank to 8-bits
    if(reg < 0 || reg > 255){
      printk("i2c_read_block. The value inserted does not"
          "corresponds to 8-bits register bank ") ;
      return -ERANGE ;
    }
    // Limiting device register block to read to 8-bits
    if(block_size < 0 || block_size > 255){
      printk("i2c_read_block. The value inserted does not"
          "corresponds to 8-bits register block size") ;
      return -ERANGE ;
    }

    int ret ;

    // Clear the fifo
    ret = i2c_clearfifo() ;
    if(ret != 0)
        return ret ;

    // Set write transfer mode
    ret = i2c_transfermode(0) ;
    if(ret != 0)
        return ret ;

    // Set new address
    ret = i2c_slaveaddress(addr) ;
    if(ret != 0)
        return ret ;

    // Set size of transfer
    ret = i2c_datalength(1) ;
    if(ret != 0)
        return ret ;

    // Write the register to the fifo
    ret = i2c_fifo(reg) ;
    if(ret != 0)
        return ret ;

    // Start write transfer
    ret = i2c_startTransfer() ;
    if(ret != 0)
        return ret ;

    // Check if there is slave address ACK
    ret = i2c_check_ack() ;
    if(ret != 0)
        return ret ;

    // Wait for transfer done
    ret = i2c_wait_tdone() ;
    if(ret != 0)
        return ret ;

    // Set read transfer mode
    ret = i2c_transfermode(1) ;
    if(ret != 0)
        return ret ;

    // Set length to block size
    ret = i2c_datalength(block_size) ;
    if(ret != 0)
        return ret ;

    // Start read transfer
    ret = i2c_startTransfer() ;
    if(ret != 0)
        return ret ;

    // Wait for transfer done
    ret = i2c_wait_tdone() ;
    if(ret != 0)
        return ret ;

    return 0 ;
}

int i2c_write_block(int addr, int size, uint8_t *content){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    // 7-bits address
    if(addr < 0 || addr > 128){
      printk("i2c_write_block. The value inserted does not"
          "corresponds to 7-bits address ") ;
      return -ERANGE ;
    }
    // Limiting device register block to write to 8-bits
    if(size < 0 || size > 255){
      printk("i2c_write_block. The value inserted does not"
          "corresponds to 7-bits address ") ;
      return -ERANGE ;
    }
    // if(*content ){ // limiting device register block to read to 8-bits
    //   printk("i2c_write_block. The value inserted does not"
    //       "corresponds to 7-bits address ") ;
    //   return -ERANGE ;
    // }

    int ret, i = 0 ;

    // Clear the fifo
    ret = i2c_clearfifo() ;
    if(ret != 0)
        return ret ;

    // Set write transfer mode
    ret = i2c_transfermode(0) ;
    if(ret != 0)
        return ret ;

    // Set dev address
    ret =  i2c_slaveaddress(addr) ;
    if(ret != 0)
        return ret ;

    // Set the length of the transfer + addr byte
    ret = i2c_datalength(size) ;
    if(ret != 0)
        return ret ;

    // Load the content into the fifo buffer
    while (i<size) {
      // Fill FIFO
      ret = i2c_fifo(content[i]) ;
      if(ret != 0)
          return ret ;
      i++ ;
    }

    // Start write transfer
    ret = i2c_startTransfer() ;
    if(ret != 0)
        return ret ;

    // Check if there is slave address ACK
    ret = i2c_check_ack() ;
    if(ret != 0)
        return ret ;

    // Wait for transfer done
    ret = i2c_wait_tdone() ;
    if(ret != 0)
        return ret ;

    return 0 ;
}
