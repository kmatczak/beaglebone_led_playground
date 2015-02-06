#ifndef LED_IOCTL_H
#define LED_IOCTL_H

#define MAJOR_NO               10 

#define DEVICE                  "/dev/led_device" 


#define IOCTL_LED_ON            _IO(MAJOR_NO, 0)     
#define IOCTL_LED_OFF           _IO(MAJOR_NO, 1)
#define IOCTL_LED_MODE_BLINK    _IOW(MAJOR_NO, 2, char*)
#define IOCTL_LED_MODE_TIMEOUT  _IOW(MAJOR_NO, 3, char*)
#define IOCTL_LED_MODE_NORMAL   _IOW(MAJOR_NO, 4, char*)


#endif
