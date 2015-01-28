#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>
//#include <linux/interrupt.h>
//#include <linux/kobject.h>
#include <linux/kthread.h>
#include "led1.h"

MODULE_LICENSE("Dual BSD/GPL");


//extern definitions
extern int sysfs_init(void);
extern int sysfs_cleanup(void);


//extern declarations
int blink_interval=50;
int timeout_interval=5000;
Mode led_mode = NORMAL;
int  gpio=54;


struct task_struct* blink_task; 
struct task_struct* timeout_task; 
int thr_flag[2] = { 0, 0 };

int led_control(int val){

//    printk(KERN_INFO "led_control called !\n");
    gpio_set_value(gpio, val);

    return 0;
}

static void led_blink(int interval){

    set_current_state(TASK_RUNNING);    
    
    printk(KERN_INFO "led_blink called !\n");
    
    thr_flag[0]=1;
    bool state=false;
    
    while (!kthread_should_stop()){
        
        set_current_state(TASK_RUNNING);    
        state=!state;
        led_control(state);
        msleep(interval);  
    }

    led_control(0);
    thr_flag[0]=0;

}

static void led_timer(int time){
    
    set_current_state(TASK_RUNNING);
    
    printk(KERN_INFO "led_on_timer called timeout=%d!\n", time);

    thr_flag[1]=1;

    led_control(1);
    set_current_state(TASK_INTERRUPTIBLE);
    msleep(time);
    led_control(0);

    thr_flag[1]=0;

}





int stop_led_threads(void){
    
    if (thr_flag[1]) kthread_stop(timeout_task);
    if (thr_flag[0]) kthread_stop(blink_task);

    return 0;
}


int start_blink_thread(void){

    blink_task = kthread_run(&led_blink, &blink_interval,"blink_thread");
    printk(KERN_INFO"Kernel Thread : %s\n",blink_task->comm);

    return 0;
}




int  start_timeout_thread(void){

    timeout_task = kthread_run(&led_timer, &timeout_interval,"timeout_thread");
    printk(KERN_INFO"Kernel Thread : %s\n",timeout_task->comm);

    return 0;
}




static int hello_init(void){
    
    printk(KERN_INFO "Hello world !\n");

    sysfs_init();

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
    

    sysfs_cleanup();
    stop_led_threads();
    
    printk(KERN_INFO "Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);


