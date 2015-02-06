#ifndef LED1_H
#define LED1_H



typedef enum modes {NORMAL, BLINK, TIMEOUT} Mode; 

extern const char* mod_txt[];
extern Mode led_mode;
extern int blink_interval;
extern int timeout_interval;
extern int gpio;

#endif
