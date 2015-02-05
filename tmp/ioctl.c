#include "led_ioctl_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */

/* 
 * Main - Call the ioctl functions 
 */
main()
{
	int file_desc, ret_val;
    char *dev_name= DEVICE_FILE_NAME2 ;


	file_desc = open(dev_name, 0);

	if (file_desc < 0) {
		printf("Can't open device file: %s\n", dev_name ); 
		exit(-1);
	}

    printf("sending ioctl via  %s\n", dev_name ); 
	
    ret_val = ioctl(file_desc, IOCTL_DUMMY);
    
    if (ret_val < 0) {
		printf("ioctl_set_msg failed:%d\n", ret_val);
		exit(-1);
	}
	close(file_desc);
}
