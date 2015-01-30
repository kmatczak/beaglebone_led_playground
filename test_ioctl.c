//#include <stdio.h>
//#include <fcntl.h>
#include <linux/fs.h>
//#include <stdlib.h>
#include <linux/ioctl.h>
#include "led_ioctl_cmd.h"


int main (int argc , char** argv){

//printf("---- TEST START ----\n");

int fd=0;

if (fd=open(DEVICE,O_RDWR) < 0) {
//    perror("error while file opening\n");
    exit(1);
}

int retval=0;
char *msg="test_message";
//if ( retval = ioctl(fd, IOC_LED_ON, 0) == -1){
if ( retval = ioctl(fd, IOCTL_SET_INT, 0) == -1){
    
  //  perror("error while ioctl writing\n");
}
else{
 
  //  printf("ioctl write OK\n");
}

close(fd);

//printf("---- TEST STOP ----\n");


return 0;




}
