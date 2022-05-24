#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define TAG "[word_count_userspace] "
#define LENGTH 500

int main(int argc, char * argv[])
{
	char buf[LENGTH];
	int fd, ret;

	fd = open("/dev/globalfifo", O_RDWR| O_NONBLOCK);
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
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ gcc 2.userspace_nonblock.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ./a.out 
Open fail, fd: -1
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo ./a.out "hi"
[word_count_userspace] Write String: hi, strlen(argv[1]):2
[word_count_userspace] Read String: hit��
                                         s�, ret = 2
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[12793.149301] [character_devices_wq] [globalfifo_open] container_of private_data.
[12793.149304] [character_devices_wq] [globalfifo_write] count: 2. start.
[12793.149307] [character_devices_wq] [globalfifo_write] written 2 bytes, current_len: 2.
[12793.149307] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[12793.149308] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[12793.149340] [character_devices_wq] [globalfifo_read] count: 500. start.
[12793.149341] [character_devices_wq] [globalfifo_read] read 2 bytes, current_len: 0.
[12793.149341] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[12793.149342] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[12793.149348] [character_devices_wq] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

*/
