
obj-m += led_driver.o
led_driver-objs := mod_main.o  ioctl_handler.o 

EXTRA_CFLAGS:=-g -Wno-declaration-after-statement -Wno-unused-result -Wno-parentheses  
KERNELDIR:=/lib/modules/$(shell uname -r)/build 
PWD:=$(shell pwd)

all: compile clean

compile:
	make -C $(KERNELDIR)  M=$(PWD) modules

clean:
	rm -rf *.o .depend.*.cmd  *.mod.c .tmp_versions .led_driver* .*handler*  .mod_main* 	

cleanall: clean
	rm -rf *.ko test_ioctl 	

test_ioctl:
	gcc   test_ioctl.c -o test_ioctl

