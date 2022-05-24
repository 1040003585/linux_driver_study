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

	ret = read(fd, &buf, LENGTH);
	printf(TAG "1Read String: %s, ret = %d\n", buf, ret);

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
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ gcc 3.userspace_nonblock2.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ./a.out "hello"
Open fail, fd: -1
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo ./a.out "hello"
[word_count_userspace] 1Read String: , ret = -1
[word_count_userspace] Write String: hello, strlen(argv[1]):5
[word_count_userspace] 2Read String: hello�z�, ret = 5
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[13020.185332] [character_devices_wq] [globalfifo_open] container_of private_data.
[13020.185335] [character_devices_wq] [globalfifo_read] count: 500. start.
[13020.185336] [character_devices_wq] [globalfifo_read] filp->f_flags is O_NONBLOCK. ret.
[13020.185353] [character_devices_wq] [globalfifo_write] count: 5. start.
[13020.185354] [character_devices_wq] [globalfifo_write] written 5 bytes, current_len: 5.
[13020.185355] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[13020.185359] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[13020.185362] [character_devices_wq] [globalfifo_read] count: 500. start.
[13020.185363] [character_devices_wq] [globalfifo_read] read 5 bytes, current_len: 0.
[13020.185364] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[13020.185364] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[13020.185367] [character_devices_wq] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

*/
