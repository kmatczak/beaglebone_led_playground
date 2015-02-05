#ifndef LED_IOCTL_H
#define LED_IOCTL_H

#define MAJOR_NO               10 

#define DEVICE                  "/dev/led_device" 


//define IOCTL_SET_MSG _IOWR(MAJOR_NO, 0, char*)
//#define IOCTL_SET_INT _IOR(MAJOR_NO, 0, int)

#define IOCTL_LED_ON _IOR(MAJOR_NO, 0, char*)     
//#define IOC_LED_OFF             0x0002
//#define IOC_LED_MODE_BLINK      0x0003
//#define IOC_LED_MODE_TIMEOUT    0x0004


#endif
