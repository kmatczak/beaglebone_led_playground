obj-m += chardev.o
 

EXTRA_CFLAGS:=-g -Wno-declaration-after-statement -Wno-unused-result -Wno-parentheses  
KERNELDIR:=/lib/modules/$(shell uname -r)/build 
PWD:=$(shell pwd)

all: compile clean

compile:
	make -C $(KERNELDIR)  M=$(PWD) modules

clean:
	rm -rf *.o .chardev* chardev.mod.c 	

cleanall: clean
	rm -rf *.ko test_ioctl 	

test_ioctl:
	gcc   ioctl.c -o test_ioctl

