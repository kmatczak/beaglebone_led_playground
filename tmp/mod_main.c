#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "mod_main.h"
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include "led_ioctl_cmd.h"
#include <asm/uaccess.h>


//MODULE_LICENSE("Dual BSD/GPL");



int in_use = 0;

static ssize_t led_write(struct file *file, const char __user *data, size_t len, loff_t *ppos){

    printk(KERN_INFO "led_write\n");
    return len;
}

static ssize_t led_read(struct file *file, char __user * buffer,  size_t length, loff_t * offset)
{
	/* 
	 * Number of bytes actually written to the buffer 
	 */
	int bytes_read = 0;
    return bytes_read;

}

static int led_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
   
    printk(KERN_INFO "led_ioctl\n");

    switch(cmd){
/*        case SCULL_IOCSQUANTUM:
                printk(KERN_INFO "received IOCTL_SET_INT");
                break;
*/      
        case IOCTL_DUMMY:
                printk(KERN_INFO "IOCTL_DUMMY received");
                break;
/*        case IOC_LED_ON:
                printk(KERN_INFO "IOC_LED_ON:%d",cmd);
                break;
        case IOC_LED_OFF:
                break;
        case IOC_LED_MODE_BLINK:
                break;
        case IOC_LED_MODE_TIMEOUT:
                break;
*/        default:
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
    .read = &led_read,
    .unlocked_ioctl = (void*)&led_ioctl,
    .compat_ioctl = (void*)&led_ioctl, 
    .open = &led_open,
    .release =&led_release,   
        
};



static struct miscdevice led_device = {
    .minor=MISC_DYNAMIC_MINOR,
    .name="led_device",
    .fops=&led_fops,
    .mode = S_IRWXUGO,
};








static int __init hello_init(void){
    
    printk(KERN_INFO "Hello world !\n");

//    ioctl_init();
    int retval;
    retval = misc_register(&led_device);
    if(retval) 
        printk(KERN_INFO "unable to  register device %i\n", led_device.minor);
    else    
        printk(KERN_INFO "misc device %i registered\n", led_device.minor);
    
    return 0;
}



static void __exit hello_exit(void){

    printk(KERN_INFO "Exit start\n");
    
    int retval;
    retval = misc_register(&led_device);
    if(retval) 
        printk(KERN_INFO "unable to  deregister device %i\n", led_device.minor);
    else    
        printk(KERN_INFO "misc device %i deregistered\n", led_device.minor);
    


//    ioctl_cleanup();


    printk(KERN_INFO "Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);


