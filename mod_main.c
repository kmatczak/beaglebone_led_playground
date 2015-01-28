#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
//#include <linux/delay.h>
//#include <linux/kthread.h>
#include "mod_main.h"
#include "led_handler.h"

MODULE_LICENSE("Dual BSD/GPL");


//extern definitions
extern int sysfs_init(void);
extern int sysfs_cleanup(void);


//extern declarations
int blink_interval=50;
int timeout_interval=5000;
Mode led_mode = NORMAL;
int  gpio=54;





static int hello_init(void){
    
    printk(KERN_INFO "Hello world !\n");


	if ( 0!= gpio_request(gpio,"usr")){
	    printk(KERN_ERR "Somsing went wrong  with gpio %d :( \n", gpio );
	    return -EIO;
    }
    
    if (0!=gpio_direction_output(gpio, 0)) {
	    printk(KERN_ERR "Somsing went wrong  with gpio %d direction :( \n", gpio);
	    return -EIO;
    }
   
    sysfs_init();
    
    return 0;
}



static void hello_exit(void){

    printk(KERN_INFO "Exit start\n");

    gpio_set_value(gpio,0);
    gpio_free(gpio);
    

    sysfs_cleanup();
    stop_led_threads();
    
    printk(KERN_INFO "Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);


