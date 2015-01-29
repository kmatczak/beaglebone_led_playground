#ifndef LED_IOCTL_H
#define LED_IOCTL_H


#define DEVICE                  "/dev/led_device" 

#define IOC_LED_ON              0x0001
#define IOC_LED_OFF             0x0002
#define IOC_LED_MODE_BLINK      0x0003
#define IOC_LED_MODE_TIMEOUT    0x0004


#endif
