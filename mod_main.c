#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
//#include <linux/delay.h>
//#include <linux/kthread.h>
#include "mod_main.h"
#include "led_handler.h"
#include "ioctl_handler.h"
#include "sysfs_handler.h"
#include <linux/semaphore.h>


MODULE_LICENSE("Dual BSD/GPL");



static int blink_interval=50;
static int timeout_interval=5000;
static Mode led_mode = NORMAL;

//extern decl
int  gpio=54;
const char* mod_txt[] = {"normal","blink","timeout"};


static struct semaphore mode_mutex;


int set_mode( Mode mod, int interval){


    if (down_interruptible(&mode_mutex)) return -ERESTARTSYS; 

    switch(mod){
        case NORMAL:
                led_mode=NORMAL; 
                //interval change ignored;
            break;
        case BLINK:
                led_mode=BLINK;
                blink_interval=interval;
            break;
        case TIMEOUT:
                led_mode=TIMEOUT;
                timeout_interval=interval;
            break;
    
    }
        
    up(&mode_mutex);

    return 0;
}



int get_mode (Mode *mode, int *blink_int, int *time_int){


    if (down_interruptible(&mode_mutex)) return -ERESTARTSYS; 
  
    *mode=led_mode;
    *blink_int=blink_interval;
    *time_int=timeout_interval;

    up(&mode_mutex);

    return 0;

}



       

static int __init hello_init(void){
    

	if ( 0!= gpio_request(gpio,"usr")){
	    printk(KERN_ERR "Sth went wrong  with gpio %d :( \n", gpio );
	    return -EIO;
    }
    
    if (0!=gpio_direction_output(gpio, 0)) {
	    printk(KERN_ERR "Sth went wrong  with gpio %d direction :( \n", gpio);
	    return -EIO;
    }
   
    sema_init(&mode_mutex, 1);
        
    sysfs_init();
    ioctl_init();
    
    return 0;
}



static void __exit hello_exit(void){

    printk(KERN_INFO "Exit start\n");

//    sema_destroy(mode_mutex);

    gpio_set_value(gpio,0);
    gpio_free(gpio);
    
    stop_led_threads();
    sysfs_cleanup();
    ioctl_cleanup();


    printk(KERN_INFO "Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);


