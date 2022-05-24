#include <stdio.h>
#include <fcntl.h>

int main()
{
	char buf;
	int fd, ret;

	fd = open("/dev/input/mice", O_RDWR);
	//fd = open("/dev/input/mouse1", O_RDWR);
	//fd = open("/dev/input/event1", O_RDWR);
	//fd = open("/dev/input/event3", O_RDWR);
	if(fd < 0) 
		printf("Open fail, fd: %d\n", fd);

	ret = read(fd, &buf, 1);

	if (ret == 1)
		printf("%c\n", buf);


	close(fd);

	return 0;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK$ gcc 1.block.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK$ sudo ./a.out 
(
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK$

*/
