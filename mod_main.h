#ifndef LED1_H
#define LED1_H



typedef enum modes {NORMAL, BLINK, TIMEOUT} Mode; 

extern const char* mod_txt[];
extern int gpio;

int set_mode(Mode, int);
int get_mode (Mode *mode, int *blink_int, int *time_int);

#endif
