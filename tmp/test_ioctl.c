#include "led_ioctl_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>


//int main (int argc , char** argv){
main()
{

    printf("---- TEST START ----\n");

    int fd=0;

    fd=open(DEVICE,O_RDWR);
    
    if( fd < 0) {
        perror("error while file opening\n");
        exit(1);
    }

    int retval=0;
    int quantum =5;

    char *msg="test_message";
    printf("IOCTL_DUMMY value: %x\n",IOCTL_DUMMY);
    printf("sending ioctl via  %s\n", DEVICE ); 
//printf("IOCTL_SET_MSG value: %x\n",IOCTL_SET_MSG);
//if ( retval = ioctl(fd, IOCTL_SET_MSG, msg ) == -1){
    retval = ioctl(fd, IOCTL_DUMMY);
    if (retval == -1) perror("error while ioctl writing");
//if ( retval = ioctl(fd, IOCTL_SET_INT, 0) == -1){
//if ( retval = ioctl(fd, SCULL_IOCSQUANTUM, &quantum) == -1){
/*    
  perror("error while ioctl writing");
}
else{
 
  printf("ioctl write OK\n");
}
*/
    close(fd);

    printf("---- TEST STOP ----\n");


return 0;




}
