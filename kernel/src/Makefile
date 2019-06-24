obj-m += i2c-devs.o
i2c-devs-y :=  gpio.o i2c.o lcd.o rtc.o i2c_devs.o \
	      			../test/unit/add_tests.o ../test/unit/test_gpio.o \
	      			../test/unit/test_i2c.o ../test/unit/test_lcd.o \
  	      		../test/unit/test_rtc.o

ccflags-y :=  -I${obj} \
      	      -I${obj}/../../shared \
      	      -I${obj}/../test/unit \
							-I$(KTF_INCLUDE_DIRS)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) $(filter-out all,$(MAKECMDGOALS))

clean:
	rm -Rf Module.symvers *.o *.ko modules.order .*.cmd .tmp_versions *.mod.c
