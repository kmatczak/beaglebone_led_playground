
obj-m += led_driver.o
led_driver-objs := mod_main.o led_handler.o sysfs_handler.o ioctl_handler.o 

EXTRA_CFLAGS:=-g -Wno-declaration-after-statement -Wno-unused-result -Wno-parentheses  
KERNELDIR:=/home/ngnlab/workspace/buildroot-black/output/build/linux-7f280334068b7c875ade51f8f3921ab311f0c824
PWD:=$(shell pwd)

all: compile clean

compile:
	make -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=/home/ngnlab/workspace/buildroot-black/output/host/usr/bin/arm-linux- SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o .depend.*.cmd  *.mod.c .tmp_versions .led_driver* .*handler*  .mod_main* 	

cleanall: clean
	rm -rf *.ko test_ioctl 	

#test_ioctl:
#	make -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=/home/ngnlab/workspace/buildroot-black/output/host/usr/bin/arm-linux- SUBDIRS=$(PWD)  -v ./test_ioctl.o 

test_ioctl:
	/home/ngnlab/workspace/buildroot-black/output/host/usr/bin/arm-linux-gcc  -M -v   test_ioctl.c -o test_ioctl

