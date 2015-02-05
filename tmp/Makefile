
obj-m += led_driver.o
led_driver-objs := mod_main.o   

EXTRA_CFLAGS:=-g -Wno-declaration-after-statement -Wno-unused-result -Wno-parentheses  
KERNELDIR:=/lib/modules/$(shell uname -r)/build 
PWD:=$(shell pwd)

all: cleanall compile test_ioctl 

compile:
	make -C $(KERNELDIR)  M=$(PWD) modules

clean:
	make -C $(KERNELDIR)  M=$(PWD) clean

cleanall: clean
	rm -rf *.ko test_ioctl test_ioctl2 	

test_ioctl:
	gcc   test_ioctl.c -o test_ioctl

test_ioctl2:
	gcc   ioctl.c -o test_ioctl2

