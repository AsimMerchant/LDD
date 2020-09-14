#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "ioctl_cmd.h"

int main(void)
{
	int fd,ret,data;
	fd=open("/dev/ioctlTest",O_RDWR);
	if(fd<0)
	{
		printf("Failed to open\n");
		return fd;
	}
	
	ret=ioctl(fd,READ_CMD,&data);
	printf("%d\n",data);
	
	return 0;
}
