#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>
//#include <linux/interrupt.h>
#include <linux/kobject.h>
#include <linux/kthread.h>


MODULE_LICENSE("Dual BSD/GPL");

static int  gpio=54;
const char* mod_txt[] = {"normal","blink","timeout"};
typedef enum modes {NORMAL, BLINK, TIMEOUT} Mode; 
static Mode led_mode = NORMAL;

struct task_struct* blink_task; 
struct task_struct* timeout_task; 
int thr_flag[2] = { 0, 0 }; 

int blink_interval=50;
int timeout_interval=5000;




static int led_control(int val){
    
    gpio_set_value(gpio, val);
    return 0;
}

static void led_blink(int interval){
    
    printk(KERN_INFO "led_blink called !\n");
    thr_flag[0]=1;
    bool state=false;
    while (!kthread_should_stop()){
      state=!state;
      led_control(state);
      msleep(interval);  
    }

    led_control(0);

    thr_flag[0]=0;
}

static void led_timer(int time){
    thr_flag[1]=1;
    printk(KERN_INFO "led_on_timer called timeout=%d!\n", time);
    led_control(1);
    msleep(time);

    led_control(0);
    thr_flag[1]=0;
}



//----sysfs files creation---------------------------------

static char mode[20]; 
static int control;


static ssize_t mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
    //return sprintf(buf, "%d\n", mode);
    
    switch(led_mode){
        case BLINK:
            return sprintf(buf,"%s [%s] %s=%d\n", mod_txt[0], mod_txt[1], mod_txt[2], timeout_interval);
            break;
        case TIMEOUT:
            return sprintf(buf,"%s %s [%s=%d]\n", mod_txt[0], mod_txt[1], mod_txt[2], timeout_interval);
            break;
        case NORMAL:
        default:
            return sprintf(buf,"[%s] %s %s=%d\n", mod_txt[0], mod_txt[1], mod_txt[2], timeout_interval);
            break;
    }
    
}

static ssize_t mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count){
    
    strncpy(mode,buf,20);
    printk(KERN_INFO "fetched mode: %s", mode);
    
    if ( NULL != strstr(mode, mod_txt[0]) ) led_mode = NORMAL;
    else if ( NULL != strstr(mode, mod_txt[1]) ) led_mode = BLINK;
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

static void stop_led_threads(void){
   // printk(KERN_INFO "##KM %s %d\n", __FILE__,  __LINE__);
    if (thr_flag[1]) kthread_stop(timeout_task);
   // printk(KERN_INFO "##KM %s %d\n", __FILE__,  __LINE__);
    if (thr_flag[0]) kthread_stop(blink_task);
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
                    blink_task = kthread_run(&led_blink,(void *)blink_interval,"blink_thread");
                    printk(KERN_INFO"Kernel Thread : %s\n",blink_task->comm);
                    break;
                case TIMEOUT:
                    stop_led_threads();
                    timeout_task = kthread_run(&led_timer,(void *)timeout_interval,"timeout_thread");
                    printk(KERN_INFO"Kernel Thread : %s\n",timeout_task->comm);
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


//------------------



static int hello_init(void){
    
    printk(KERN_INFO "Hello world !\n");

    /*
    * Create a simple kobject with the name of "led_gpio_GPIO",
    * located under /sys/kernel/
    */
    char led_dir[64];
    snprintf(led_dir, 64, "led_gpio_%d", gpio);
    example_kobj = kobject_create_and_add(led_dir, kernel_kobj);
    if (!example_kobj) return -ENOMEM;

   /* Create the files associated with this kobject */
    int retval;
    retval  = sysfs_create_group(example_kobj, &attr_group);
    if (retval)  kobject_put(example_kobj); 
  


	if ( 0!= gpio_request(gpio,"usr")){
	    printk(KERN_ERR "Somsing went wrong  with gpio %d :( \n", gpio );
	    return -EIO;
    }
    
    if (0!=gpio_direction_output(gpio, 0)) {
	    printk(KERN_ERR "Somsing went wrong  with gpio %d direction :( \n", gpio);
	    return -EIO;
    }
    
    return 0;

}


static void hello_exit(void){

    printk(KERN_INFO "Exit start\n");

    gpio_set_value(gpio,0);
    gpio_free(gpio);
    
    kobject_put(example_kobj);    
    stop_led_threads();
    
    printk(KERN_INFO "Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);


