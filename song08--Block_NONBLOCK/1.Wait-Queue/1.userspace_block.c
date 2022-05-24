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

	if(argc > 1)
	{
		write(fd, argv[1], strlen(argv[1]));
		printf(TAG "Write String: %s, strlen(argv[1]):%d\n", argv[1], strlen(argv[1]));
	}

	ret = read(fd, &buf, LENGTH);

	printf(TAG "Read String: %s, ret = %d\n", buf, ret);


	close(fd);

	return 0;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ gcc 1.userspace_block.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ./a.out 
Open fail, fd: -1
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo ./a.out "hello wu"
[word_count_userspace] Write String: hello wu, strlen(argv[1]):8
[word_count_userspace] Read String: hello wu, ret = 8
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

*/

/*
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[12614.330492] [character_devices_wq] [globalfifo_open] container_of private_data.
[12614.330496] [character_devices_wq] [globalfifo_write] count: 8. start.
[12614.330498] [character_devices_wq] [globalfifo_write] written 8 bytes, current_len: 8.
[12614.330498] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[12614.330499] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[12614.330522] [character_devices_wq] [globalfifo_read] count: 500. start.
[12614.330523] [character_devices_wq] [globalfifo_read] read 8 bytes, current_len: 0.
[12614.330524] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[12614.330524] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[12614.330528] [character_devices_wq] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

*/
