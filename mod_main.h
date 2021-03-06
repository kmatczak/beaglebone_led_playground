#ifndef LED1_H
#define LED1_H

/**
 *  
 *  \author     Krzysztof Matczak
 *  \brief      GPIO led driver. Features: ON/OFF, blink and timeout LED activity. Targeted and tested for Beaglebone Black rev C
 *  
 *
 *
 */

typedef enum modes {NORMAL, BLINK, TIMEOUT} Mode; 

extern const char* mod_txt[];
extern int gpio;



/**
 * set current mode and interval; interval respected only for blink and timeut mode
 */
int set_mode(Mode, int);



/**
 * get current mode and interval
 */
int get_mode (Mode *mode, int *blink_int, int *time_int);

#endif
