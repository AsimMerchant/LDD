#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include <unistd.h>


int main(void)
{
	int fd,ret;
	char data[100];
	fd=open("/dev/testcDev",O_RDWR);
	if(fd<0)
	{
		printf("Failed to open\n");
		return fd;
	}
	
	ret=read(fd,data,10);
	printf("Read bytes =%d\n",ret);
	if(ret<0)
	{
		printf("Read failed\n");
		return ret;
	}

	ret=write(fd,"Hello",strlen("Hello"));
	printf("Written bytes=%d\n",ret);
	if(ret<0)
        {
                printf("Write failed\n");
                return ret;
        }

	ret=read(fd,data,10);
        printf("Read2 bytes =%d\n",ret);
        if(ret<0)
        {
                printf("Read2 failed\n");
                return ret;
        }
	return 0;
}
