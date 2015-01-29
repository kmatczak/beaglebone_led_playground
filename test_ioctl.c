#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "led_ioctl_cmd.h"


int main (int argc , char** argv){

int fd=0;

if (fd=open(DEVICE,O_RDWR) < 0) {
    perror("error while file opening\n");
    exit(1);
}

int retval=0;

if ( retval = ioctl(fd, IOC_LED_ON, 0) == -1){
    
    perror("error while ioctl writing\n");
}
else{
 
    printf("ioctl write OK\n");
}

close(fd);

return 0;




}
