
#ifndef LEDHANDLER_H
#define LEDHANDLER_H


int led_control(int);
int stop_led_threads(void);
int start_blink_thread(int);
int start_timeout_thread(int);
int get_interval(char *, int *); 
#endif

