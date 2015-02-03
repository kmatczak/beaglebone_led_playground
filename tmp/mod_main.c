#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/delay.h>
//#include <linux/kthread.h>
#include "mod_main.h"

MODULE_LICENSE("Dual BSD/GPL");


//extern definitions
extern int ioctl_init(void);
extern int ioctl_cleanup(void);






static int __init hello_init(void){
    
    printk(KERN_INFO "Hello world !\n");

    ioctl_init();
    
    return 0;
}



static void __exit hello_exit(void){

    printk(KERN_INFO "Exit start\n");

    ioctl_cleanup();


    printk(KERN_INFO "Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);


