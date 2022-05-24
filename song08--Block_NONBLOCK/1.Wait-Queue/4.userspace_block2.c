#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define TAG "[word_count_userspace] "
#define LENGTH 500

int main(int argc, char * argv[])
{
	char buf[LENGTH];
	int fd, ret;

	fd = open("/dev/globalfifo", O_RDWR);
	if(fd < 0) {
		printf("Open fail, fd: %d\n", fd);
		return 0;		
	}

	printf(TAG "1.Read before: %s, ret = %d\n", buf, ret);
	ret = read(fd, &buf, LENGTH);
	printf(TAG "1.Read after: %s, ret = %d\n", buf, ret);

	if(argc > 1)
	{
		write(fd, argv[1], strlen(argv[1]));
		printf(TAG "Write String: %s, strlen(argv[1]):%d\n", argv[1], strlen(argv[1]));
	}

	ret = read(fd, &buf, LENGTH);
	printf(TAG "2Read String: %s, ret = %d\n", buf, ret);


	close(fd);

	return 0;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ gcc 4.userspace_block2.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo ./a.out "hi 2"
[word_count_userspace] 1.Read before: , ret = -1216673704
^C


*/

// Because of BLOCK, pending read....
