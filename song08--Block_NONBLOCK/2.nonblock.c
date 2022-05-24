#include <stdio.h>
#include <fcntl.h>

int main()
{
	char buf;
	int fd;

	fd = open("/dev/input/mice", O_RDWR | O_NONBLOCK);
	//fd = open("/dev/input/event1", O_RDWR | O_NONBLOCK);
	//fd = open("/dev/input/event3", O_RDWR | O_NONBLOCK);
	if(fd < 0) 
		printf("Open fail, fd: %d\n", fd);

	while(read(fd, buf, 1) != 1)
		continue;

	printf("%c\n", buf);

	close(fd);
	return 0;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK$ gcc 2.nonblock.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK$ sudo ./a.out 


*/
