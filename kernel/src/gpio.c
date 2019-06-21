#include "gpio.h"
#include "shared.h"

#define HIGH          1
#define LOW           0


extern struct gpioRegs *gpioRegsp ;


///-------------------------------------------------------------------
///----------------------- GPIO FUNCTIONS ----------------------------
///-------------------------------------------------------------------
int pinMode( int pin, int pin_mode){
   // ------------------------------------------------------
   // Sanity checks
   // ------------------------------------------------------
   if(pin<0 || pin>40){
       printk("pin_mode_parameters. The value inserted does not"
           "corresponds to pin range in board.");
       return -ERANGE ;
   }
   if(pin_mode > 4){ //alt4 para i2c
       printk("pin_mode_parameters. The value inserted does not"
           "corresponds to input/output/alt pin mode state in board.");
       return -ERANGE ;
   }

   uint32_t registerPrint = 0 ;
   uint32_t fs_new = 0, aux_set = 0, aux_clr = 0, aux_fs_cleared = 0 ;
   uint32_t fs_prev = (uint32_t)gpioRegsp->GPIO_FS[pin/10] ;

   aux_set = (uint32_t)(pin_mode << (pin*3)) ;       // holds the pin mode for pin
   aux_clr = (uint32_t)(7 << (pin*3)) ;              // 3 bits offset for pin
   aux_fs_cleared = (uint32_t)(fs_prev & ~aux_clr) ; // clears pin mode for pin

   fs_new = (uint32_t)(aux_set | aux_fs_cleared) ;
   gpioRegsp->GPIO_FS[pin/10] = (uint32_t)fs_new ;   // sets the pin mode for pin

   return 0 ;
}

int digitalRead(int pin){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    if(pin<0 || pin>40){
        printk("digital_read_parameters. The value inserted does not"
            "corresponds to pin range in board.");
        return -ERANGE ;
    }

    // Read pin logical state from pin offset on register
    uint32_t read = (uint32_t)(gpioRegsp->GPIO_LEVEL[pin/32] >> pin) ;
    read &= 0x1 ;

    return 0 ;
}

int digitalWrite(int pin, int pin_state){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    if(pin<0 || pin>40){
        printk("digital_write_parameters. The value inserted does not"
            "corresponds to pin range in board.");
        return -ERANGE ;
    }
    if(pin_state!=LOW && pin_state!=HIGH){
        printk("digital_write_parameters. The value inserted does not"
            "corresponds to logical input/output pin state in board.");
        return -ERANGE ;
    }

    uint32_t aux_prev = (uint32_t)0, aux_new = (uint32_t)0, aux_set = (uint32_t)0;

    if(pin_state == HIGH){
        // SET
        aux_prev = (uint32_t)gpioRegsp->GPIO_SET[pin/32] ;
        // Offsets high state for pin
        aux_set = (uint32_t)(1 << pin) ;
        aux_new = aux_prev | aux_set ;

        gpioRegsp->GPIO_SET[pin/32] = aux_new ;
    }
    else if (pin_state == LOW){
        // CLR
        aux_prev = (uint32_t)gpioRegsp->GPIO_CLR[pin/32] ;
        // Offsets low state for pin
        aux_set = (uint32_t)(1 << pin) ;
        aux_new = aux_prev | aux_set ;

        gpioRegsp->GPIO_CLR[pin/32] = aux_new ;
    }

    return 0 ;
}

 int i2c_write2register(volatile uint32_t *i2c_register, int bit_value, int bit){
    // ------------------------------------------------------
    // Sanity checks
    // ------------------------------------------------------
    if(bit_value < 0 || bit_value > 1){
        printk("i2c_write2register_parameters. The bit_value inserted"
             "is not in range.");
        return -ERANGE ;
    }
    if(bit < 0 || bit > 31){
        printk("i2c_write2register_parameters. The bit value inserted does not"
            "corresponds to 32 bit range.");
        return -ERANGE ;
    }
    // Offsets value on register
    uint32_t i2c_ctrl_field         = (uint32_t)(bit_value << bit) ;
    uint32_t reg_clr                = (uint32_t)(1 << bit) ;
    // Previously clears bit value field on register
    uint32_t reg_i2c_ctrl_cleared   = (uint32_t)(*i2c_register & ~reg_clr) ;

    uint32_t reg_new                = reg_i2c_ctrl_cleared | i2c_ctrl_field ;

    // Set the value
    *i2c_register = reg_i2c_ctrl_cleared | reg_new ;

    return   0 ;
}
