#include "led_handler.h"
#include "mod_main.h"
#include <linux/kthread.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define __NO_VERSION__




//extern declarations
extern int blink_interval;
extern int timeout_interval;
extern Mode led_mode;
extern int gpio;


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

    blink_task = kthread_run(&led_blink, blink_interval,"blink_thread");
    printk(KERN_INFO"Kernel Thread : %s\n",blink_task->comm);

    return 0;
}




int  start_timeout_thread(void){

    timeout_task = kthread_run(&led_timer, timeout_interval,"timeout_thread");
    printk(KERN_INFO"Kernel Thread : %s\n",timeout_task->comm);

    return 0;
}



