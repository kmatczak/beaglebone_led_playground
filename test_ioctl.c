#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>
#include "led_ioctl_cmd.h"

int main (int argc , char** argv){

int fd;
fd=open(DEVICE,O_RDWR) ;

if (fd < 0) {
    perror("error while file opening\n");
    exit(1);
}

int retval=0;

printf("TEST 1: blink 100ms\n");
retval = ioctl(fd, IOCTL_LED_MODE_BLINK,"blink=100");
retval = ioctl(fd, IOCTL_LED_ON);
sleep(6);
retval = ioctl(fd, IOCTL_LED_OFF);

printf("TEST 2: blink 10ms\n");
retval = ioctl(fd, IOCTL_LED_MODE_BLINK,"blink=10");
retval = ioctl(fd, IOCTL_LED_ON);
sleep(6);
retval = ioctl(fd, IOCTL_LED_OFF);

printf("TEST 3: timeout 3000ms\n");
retval = ioctl(fd, IOCTL_LED_MODE_TIMEOUT,"timeout=3000");
retval = ioctl(fd, IOCTL_LED_ON);
sleep(6);
retval = ioctl(fd, IOCTL_LED_OFF);


printf("TEST 4: ON - 5s - OFF\n");
retval = ioctl(fd, IOCTL_LED_MODE_NORMAL) ;
retval = ioctl(fd, IOCTL_LED_ON);
sleep(5);
retval = ioctl(fd, IOCTL_LED_OFF);


if (retval == -1)  perror(" TEST PASSED \n");

close(fd);



return 0;




}
