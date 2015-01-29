#ifndef LED_IOCTL_H
#define LED_IOCTL_H

#define MAJOR_NO                60

#define DEVICE                  "/dev/led_device" 


#define IOCTL_SET_MSG _IOR(MAJOR_NO, 0, char*)
#define IOCTL_SET_INT _IOR(MAJOR_NO, 0, int)

#define IOC_LED_ON              0x0001
#define IOC_LED_OFF             0x0002
#define IOC_LED_MODE_BLINK      0x0003
#define IOC_LED_MODE_TIMEOUT    0x0004


#endif
