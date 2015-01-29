#include <linux/miscdevice.h>
#include <linux/fs.h>
#include "mod_main.h"
#include "led_ioctl_cmd.h"

#define __NO_VERSION__



/*
static ssize_t led_write(struct file *file, const char__user *data, size_t len, loff_t *ppos){

    printk(KERN_INFO "led_write\n");
    return 0;
}
*/

static long led_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
   
    printk(KERN_INFO "led_ioctl\n");

    switch(cmd){
        case IOCTL_SET_INT:
                printk(KERN_INFO "received IOCTL_SET_INT");
                break;
        case IOC_LED_ON:
                printk(KERN_INFO "IOC_LED_ON:%d",cmd);
                break;
        case IOC_LED_OFF:
                break;
        case IOC_LED_MODE_BLINK:
                break;
        case IOC_LED_MODE_TIMEOUT:
                break;
        default:
                break;        

    }

    return 0;
}


static int led_open(struct inode *inode, struct file *file){

    printk(KERN_INFO "led_open\n");
    return 0;
}


static int led_release(struct inode *inode, struct file *file){

    printk(KERN_INFO "led_open\n");
    return 0;
}





static const struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .llseek = no_llseek,
   // .write = &led_write,
    .unlocked_ioctl = &led_ioctl, 
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









