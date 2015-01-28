
obj-m += led_driver.o
led_driver-objs := mod_main.o led_handler.o sysfs_handler.o 

EXTRA_CFLAGS:=-g -Wno-declaration-after-statement -Wno-unused-result
KERNELDIR:=/home/ngnlab/workspace/buildroot-black/output/build/linux-7f280334068b7c875ade51f8f3921ab311f0c824
PWD:=$(shell pwd)

all:
	make -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=/home/ngnlab/workspace/buildroot-black/output/host/usr/bin/arm-linux- SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o .depend.*.cmd *.ko *.mod.c .tmp_versions .led1*  .sysfs_handler* .led_handler* .mod_main*	
