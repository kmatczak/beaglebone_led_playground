#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
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
printf("IOCTL_LED_ON value: %x\n",IOCTL_LED_ON);
retval = ioctl(fd, IOCTL_LED_ON);

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
