#ifndef LED1_H
#define LED1_H

/*!
 *  
 *  \author     Krzysztof Matczak
 *  \brief      GPIO led driver. Features: ON/OFF, blink and timeout LED activity.
 *
 *
 */

typedef enum modes {NORMAL, BLINK, TIMEOUT} Mode; 

extern const char* mod_txt[];
extern int gpio;

int set_mode(Mode, int);
int get_mode (Mode *mode, int *blink_int, int *time_int);

#endif
