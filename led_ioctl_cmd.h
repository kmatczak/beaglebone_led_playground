#ifndef LED_IOCTL_H
#define LED_IOCTL_H

#define MAJOR_NO               10 

#define DEVICE                  "/dev/led_device" 


#define IOCTL_LED_ON            _IOR(MAJOR_NO, 0, char*)     
#define IOCTL_LED_OFF           _IOR(MAJOR_NO, 1, char*)
#define IOCTL_LED_MODE_BLINK    _IOR(MAJOR_NO, 2, char*)
#define IOCTL_LED_MODE_TIMEOUT  _IOR(MAJOR_NO, 3, char*)
#define IOCTL_LED_MODE_NORMAL   _IOR(MAJOR_NO, 4, char*)


#endif
