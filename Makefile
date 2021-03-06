
obj-m += led_driver.o
led_driver-objs := mod_main.o led_handler.o sysfs_handler.o ioctl_handler.o 

EXTRA_CFLAGS:=-g -Wno-declaration-after-statement -Wno-unused-result -Wno-parentheses  
KERNELDIR:=/home/ngnlab/workspace/buildroot-black/output/build/linux-7f280334068b7c875ade51f8f3921ab311f0c824
PWD:=$(shell pwd)

all: compile test_ioctl

compile:
	make -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=/home/ngnlab/workspace/buildroot-black/output/host/usr/bin/arm-linux- SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=/home/ngnlab/workspace/buildroot-black/output/host/usr/bin/arm-linux- SUBDIRS=$(PWD) clean

cleanall: clean
	rm -rf *.ko test_ioctl 	

test_ioctl:
	/home/ngnlab/workspace/buildroot-black/output/host/usr/bin/arm-linux-gcc   test_ioctl.c -o test_ioctl

