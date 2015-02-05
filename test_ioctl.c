#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>
#include "led_ioctl_cmd.h"


int main (int argc , char** argv){

printf("---- TEST START ----\n");

int fd;
fd=open(DEVICE,O_RDWR) ;

if (fd < 0) {
    perror("error while file opening\n");
    exit(1);
}

int retval=0;
int quantum =5;

char *msg="test_message";


retval = ioctl(fd, IOCTL_LED_MODE_BLINK);
retval = ioctl(fd, IOCTL_LED_ON);
sleep(6);
retval = ioctl(fd, IOCTL_LED_OFF);

retval = ioctl(fd, IOCTL_LED_MODE_TIMEOUT) ;
retval = ioctl(fd, IOCTL_LED_ON);
sleep(6);

retval = ioctl(fd, IOCTL_LED_MODE_NORMAL) ;
retval = ioctl(fd, IOCTL_LED_ON);
sleep(5);



if (retval == -1){
  
  perror("error while ioctl writing");
}
else{
 
  printf("ioctl write OK\n");
}

close(fd);

printf("---- TEST STOP ----\n");


return 0;




}
