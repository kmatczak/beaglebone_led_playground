
#ifndef LEDHANDLER_H
#define LEDHANDLER_H


int led_control(int val);
int stop_led_threads(void);
int start_blink_thread(void);
int start_timeout_thread(void);
int get_interval(char *, int *); 
#endif

