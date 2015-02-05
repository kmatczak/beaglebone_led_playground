#ifndef LED_IOCTL_H
#define LED_IOCTL_H

#define MAJOR_NO               10 

#define DEVICE                  "/dev/led_device" 



//#define SCULL_IOC_MAGIC     'k'
//#define SCULL_IOCRESET      _IO(SCULL_IOC_MAGIC, 0)
//#define SCULL_IOCSQUANTUM   _IOW(SCULL_IOC_MAGIC,  1, int)






#define IOCTL_DUMMY 0x00000001

#define IOCTL_SET_MSG _IOWR(MAJOR_NO, 0, char*)
//#define IOCTL_SET_INT _IOR(MAJOR_NO, 0, int)

//#define IOC_LED_ON              0x0001
//#define IOC_LED_OFF             0x0002
//#define IOC_LED_MODE_BLINK      0x0003
//#define IOC_LED_MODE_TIMEOUT    0x0004


#endif
