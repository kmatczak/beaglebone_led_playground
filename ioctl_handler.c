#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include "mod_main.h"
#include "led_ioctl_cmd.h"
#include <asm/uaccess.h>
#include "led_handler.h"

#define __NO_VERSION__


int in_use = 0;

static ssize_t led_write(struct file *file, const char __user *data, size_t len, loff_t *ppos){

    printk(KERN_INFO "led_write\n");
    return len;
}



static int led_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
   
//    printk(KERN_INFO "led_ioctl\n");
  
    int interval=0;
    Mode lm;
    int bl_int;
    int tm_int;
    
    get_mode(&lm, &bl_int, &tm_int );


    switch(cmd){

        case IOCTL_LED_ON:
                
                switch(lm){
                    case BLINK:
                        stop_led_threads();
                        start_blink_thread(bl_int);
                        break;
                    case TIMEOUT:
                        stop_led_threads();
                        start_timeout_thread(tm_int);
                        break;
                    case NORMAL:
                    default:
                        led_control(1);
                    break;
                }
                break;
        case IOCTL_LED_OFF:
                
                switch(lm){
                    case BLINK:
                        stop_led_threads();
                    break;
                        case TIMEOUT:
                        stop_led_threads();
                    break;
                    case NORMAL:
                    default:
                        led_control(0);
                    break;            
                }

                break;
        case IOCTL_LED_MODE_BLINK:
                
                if ( get_interval( (char*)arg, &interval) == -1 ) return -1; 
                set_mode(BLINK, interval);
                break;
        case IOCTL_LED_MODE_TIMEOUT:
                
                if ( get_interval( (char*)arg, &interval) == -1 ) return -1; 
                set_mode(TIMEOUT, interval);
                break;
        case IOCTL_LED_MODE_NORMAL:
                
                set_mode(NORMAL, interval);
                break;
        default:
                break;        

    }

    return 0;
}



static int led_open(struct inode *inode, struct file *file){


    if(in_use) return -EBUSY;
    ++in_use;

    printk(KERN_INFO "/dev/led_driver open\n");

    return 0;
}



static int led_release(struct inode *inode, struct file *file){

    --in_use;

    printk(KERN_INFO "/dev/led_driver release\n");
    return 0;
}


    
static const struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .llseek = no_llseek,
    .write = &led_write,
    .unlocked_ioctl = (void*)&led_ioctl,
    .compat_ioctl = (void*)&led_ioctl, 
    .open = &led_open,
    .release =&led_release,   
        
};



static struct miscdevice led_device = {
    .minor=MISC_DYNAMIC_MINOR,
    .name="led_device",
    .fops=&led_fops,
};



int ioctl_init(void){

    int retval;
    if (retval = misc_register(&led_device)) return retval;

    printk(KERN_INFO "misc device %i registered\n", led_device.minor);
    return 0;

}



int ioctl_cleanup(void){

    int retval;
    if (retval = misc_deregister(&led_device)) return retval;

    printk(KERN_INFO "misc device %i deregistered\n", led_device.minor);
    return 0;

}









