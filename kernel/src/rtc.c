
#include "rtc.h"
#include "i2c.h"



char rtc_address = 0 ;

extern struct i2cRegs *i2cRegsp ;

// --- shared
extern struct i2c_data ;
extern struct rtc ;

///-------------------------------------------------------------------
///--------------------- I2C RTC FUNCTIONS ---------------------------
///-------------------------------------------------------------------

 int i2c_rtc_setup(void){
      int ret ;
      // Enables rtc oscillator
      uint8_t initrtc[2] = {CONTROLREG, 0x0} ;
      // Restart rtc
      uint8_t initrtc1[2] = {STATUSREG, 0x8} ;

      ret = i2c_init() ;
      if(ret != 0)
          return ret ;

      // Write tuple to LCD througth I2C
      ret = i2c_write_block(rtc_address, 2, initrtc) ;
      if(ret != 0)
          return ret ;

      // Write tuple to LCD througth I2C
      ret = i2c_write_block(rtc_address, 2, initrtc1) ;
      if(ret != 0)
          return ret ;

      return 0 ;
}

 int i2c_rtc_readdata(struct i2c_data *q){
      int ret ;
      uint8_t timeout=50, time[3] ;
      uint8_t hour_dec, hour_unid, min_dec, min_unid, sec_dec, sec_unid ;
      char buffer[50] ;

      ret = i2c_rtc_setup() ;
      if(ret != 0)
          return ret ;

      // Points to seconds register in rtc
      ret = i2c_read_block(rtc_address, 0x0, 3) ;
      if(ret != 0)
          return ret ;

      // Read time from RTC registers
      time[0] = i2cRegsp->I2C_DATAFIFO ;
      time[1] = i2cRegsp->I2C_DATAFIFO ;
      time[2] = i2cRegsp->I2C_DATAFIFO ;

      // Parse each register tens and unids
      sec_unid = time[0]&0xF ;
      sec_dec = (time[0]&0x70)>>4 ;

      min_unid = time[1]&0xF ;
      min_dec = (time[1]&0x70)>>4 ;

      hour_unid = time[2]&0xF ;
      hour_dec = (time[2]&0x70)>>4 ;

      // Pack data for time 24-hour format
      sprintf(buffer, "%d%d:%d%d:%d%d", hour_dec, hour_unid, min_dec, min_unid, sec_dec, sec_unid);

      // Struct that shares hour to user-space
      memcpy(q->rtc, buffer, sizeof(buffer));

      return 0 ;
}

 int i2c_rtc_sethour(struct rtc q){
      // ------------------------------------------------------
      // Sanity checks
      // ------------------------------------------------------
      if(q.sec_unid < '0' || q.sec_unid > '9'){
        printk("i2c_rtc_sethour. The value inserted does not "
            "corresponds to seconds range for unids digit ") ;
        return -ERANGE ;
      }
      if(q.sec_dec < '0' || q.sec_dec > '9'){
        printk("i2c_rtc_sethour. The value inserted does not "
            "corresponds to seconds range for dozens digit ") ;
        return -ERANGE ;
      }
      if(q.min_unid < '0' || q.min_unid > '9'){
        printk("i2c_rtc_sethour. The value inserted does not "
            "corresponds to minutes range for unids digit ") ;
        return -ERANGE ;
      }
      if(q.min_dec < '0' || q.min_dec > '9'){
        printk("i2c_rtc_sethour. The value inserted does not "
            "corresponds to minutes range for dozens digit ") ;
        return -ERANGE ;
      }
      if(q.hour_unid < '0' || q.hour_unid > '9'){
        printk("i2c_rtc_sethour. The value inserted does not "
            "corresponds to hour range for unids digit ") ;
        return -ERANGE ;
      }
      if(q.hour_dec < '0' || q.hour_dec > '9'){
        printk("i2c_rtc_sethour. The value inserted does not "
            "corresponds to hour range for dozens digit ") ;
        return -ERANGE ;
      }

      int ret ;
      int secREG=0x0 ;
      // Enables rtc oscillator
      uint8_t initrtc[2] = {CONTROLREG, 0x0} ;
      // Command to restart rtc
      uint8_t initrtc2[2] = {STATUSREG, 0x88} ;

      ret = i2c_rtc_setup() ;
      if(ret != 0)
            return ret ;

      // Pack register to start pointing to, and subsequent data
      uint8_t set[4] = {secREG, ((q.sec_dec<<4)&0x70 | q.sec_unid&0xF),
                                ((q.min_dec<<4)&0x70 | q.min_unid&0xF),
                                ((q.hour_dec<<4)&0x70 | q.hour_unid&0xF)} ;

      // Write tuple to enable RTC througth I2C
      ret = i2c_write_block(rtc_address, 4, set) ;
      if(ret != 0)
            return ret ;

      // Write tuple to restart RTC througth I2C
      ret = i2c_write_block(rtc_address, 2, initrtc) ;
      if(ret != 0)
            return ret ;

      // Write hour tuple to RTC througth I2C
      ret = i2c_write_block(rtc_address, 2, initrtc2) ;
      if(ret != 0)
            return ret ;

      return 0 ;
}
