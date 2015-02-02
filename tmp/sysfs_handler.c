

#include <linux/kernel.h>  /* We're doing kernel work */
#include <linux/module.h>  /* Specifically, a module  */
#include <linux/kobject.h>
#include "mod_main.h"
#include "led_handler.h"

#define __NO_VERSION__


const char* mod_txt[] = {"normal","blink","timeout"};


//----sysfs files creation---------------------------------


static char mode[20]; 
static int control;


static ssize_t mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
    //return sprintf(buf, "%d\n", mode);
    
    switch(led_mode){
        case BLINK:
            return sprintf(buf,"%s [%s=%d] %s=%d\n", mod_txt[0], mod_txt[1], blink_interval, mod_txt[2],  timeout_interval);
            break;
        case TIMEOUT:
            return sprintf(buf,"%s %s=%d [%s=%d]\n", mod_txt[0], mod_txt[1], blink_interval, mod_txt[2],  timeout_interval);
            break;
        case NORMAL:
        default:
            return sprintf(buf,"[%s] %s=%d %s=%d\n", mod_txt[0], mod_txt[1], blink_interval, mod_txt[2], timeout_interval);
            break;
    }
    
}

static ssize_t mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count){
    
    strncpy(mode,buf,20);
    printk(KERN_INFO "fetched mode: %s", mode);
    
    if ( NULL != strstr(mode, mod_txt[0]) ) led_mode = NORMAL;
    else if ( NULL != strstr(mode, mod_txt[1]) ) {
        led_mode = BLINK;
        char* pch; 
        pch = strchr(mode,'=');
        if (pch != NULL){
            ++pch;
            if ( 0 > sscanf(pch, "%d", &blink_interval) ) {
                printk(KERN_ERR "blink conversion error ! \n");
                return -1;
            }
       }

    }
    else if ( NULL != strstr(mode, mod_txt[2]) ) {
        led_mode = TIMEOUT;
        char* pch; 
        pch = strchr(mode,'=');
        if (pch != NULL){
            ++pch;
            if ( 0 > sscanf(pch, "%d", &timeout_interval) ) {
                printk(KERN_ERR "timeout conversion error ! \n");
                return -1;
            }
       }
    }
    else {
        printk(KERN_ERR "mode not supported or wrong syntax\n");
        return -EIO;
    }

    return count;
}

static ssize_t control_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
    return sprintf(buf, "%d\n", control);
}


static ssize_t control_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count){
    
    sscanf(buf, "%du", &control);

    switch(control){
        case 0:   
            switch(led_mode){
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
        case 1: 
            switch(led_mode){
                case BLINK:
                    stop_led_threads();
                    start_blink_thread();
                    break;
                case TIMEOUT:
                    stop_led_threads();
                    start_timeout_thread();
                    break;
                case NORMAL:
                default:
                    led_control(1);
                    break;
            }
            break;
        default: 
            printk(KERN_ERR "control attr valid values are 0 and 1\n");
            return -EIO;
    }



    return count;
}


static struct kobj_attribute mode_attribute = __ATTR(mode, 0666, mode_show, mode_store);
static struct kobj_attribute control_attribute = __ATTR(control, 0666, control_show, control_store);

/*
 * Create a group of attributes so that we can create and destory them all
 * at once.
 */
static struct attribute *attrs[] = {
    &mode_attribute.attr,
    &control_attribute.attr,
    NULL,  /* need to NULL terminate the list of attributes */
 };


/*
 * An unnamed attribute group will put all of the attributes directly in
 * the kobject directory.  If we specify a name, a subdirectory will be
 * created for the attributes with the directory being the name of the
 * attribute group.
 */
 static struct attribute_group attr_group = {
    .attrs = attrs,
 };

static struct kobject *example_kobj;



int sysfs_init(void){

    /*
    * Create a simple kobject with the name of "led_gpio_GPIO",
    * located under /sys/kernel/
    *
    * As this is a simple directory, no uevent will be sent to
    * userspace.  That is why this function should not be used for
    * any type of dynamic kobjects, where the name and number are
    * not known ahead of time.
    */
    char led_dir[64];
    snprintf(led_dir, 64, "led_gpio_%d", gpio);
    example_kobj = kobject_create_and_add(led_dir, kernel_kobj);
    if (!example_kobj) return -ENOMEM;

   /* Create the files associated with this kobject */
    int retval;
    retval  = sysfs_create_group(example_kobj, &attr_group);
    if (retval)  kobject_put(example_kobj); 
  
    
    return retval;


}    


int  sysfs_cleanup(void){

    kobject_put(example_kobj);   
    
    return 0; 

}


