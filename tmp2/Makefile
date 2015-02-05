 

EXTRA_CFLAGS:=-g -Wno-declaration-after-statement -Wno-unused-result -Wno-parentheses  -DDEBUG 
KERNELDIR:=/lib/modules/$(shell uname -r)/build 
PWD:=$(shell pwd)

obj-m += chardev.o

all:  compile test_ioctl  

compile:
	make -C $(KERNELDIR)  M=$(PWD) modules

clean:
	make -C $(KERNELDIR)  M=$(PWD) clean 
#	rm -rf *.o .chardev* chardev.mod.c 	

cleanall: clean
	rm -rf *.ko test_ioctl 	

test_ioctl:
	gcc   ioctl.c -o test_ioctl

