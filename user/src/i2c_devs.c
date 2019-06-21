#include "i2c_devs.h"

// Share library between user and kernel space
#include "shared.h"

// Program libraries
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"
#include "lcd.h"



int run(){
    char time[50] ;

    while(1) {
        // Read hour from RTC by I2C comunication
        i2c_rtc_readdata(&time) ;
        // Write hour to LCD display
        lcdwr(time) ;
        usleep(LCD_REFRESH_TIME) ;
        // Clear display before
        lcdclr() ;
    }
    return 0 ;
}


int main(int argc, char *argv[]) {
    // Set LCD I2C bus address
    lcdinit(LCD_ADDR) ;
    // Set RTC I2C bus address
    rtcinit(RTC_ADDR) ;

    while (1){
        // Parse terminal program argument
        static struct option long_options[] = {
                {"verbose",   no_argument,             &verbose_flag, 1},
                {"run",       no_argument,             0,   0},
                {"set_time",  required_argument,       0,  't'},
                {"help",      no_argument,             0,  'h'}
        };
          int option_index = 0;
          int c = getopt_long (argc, argv, "bs",
                   long_options, &option_index);

          if (c == -1)
                break;

          switch (c){
                //  Run i2c-devs program
                // --run
                case 0:
                {
                  run() ;
                  break ;
                }
                //  Set RTC hour in format
                // --set_time 12:12:12
                case 't':
                {
                  rtchour(optarg) ;
                  break;
                }
                // Display commands into terminal
                // --help
                case 'h':
                    if (long_options[option_index].flag != 0)
                      break ;
                    printf (
                          " --run         no_argument          \n"
                          " --set_time    12:12:12             \n"
                          " --help        no_argument          \n"
                    ) ;
                    break;
                default:
                  abort ();
                }
        }



    return 0;
}
