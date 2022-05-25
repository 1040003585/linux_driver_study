#include <stdio.h>
#include <fcntl.h>
#include <string.h>  //bzero

#include <sys/epoll.h>

//FIFO_CLEAR:
#define FIFO_CLEAR 0x1 

// Not FIFO_CLEAR:
//#define FIFO_CLEAR 0x0 

#define TAG "[userspace-poll] "
#define TIMEOUT 15000

int main(int argc, char * argv[])
{
	int fd, err, epfd;
	struct epoll_event ev_globalfifo;

	fd = open("/dev/globalfifo", O_RDONLY| O_NONBLOCK); // can just ./a.out to run it.
	if (fd < 0) {
		printf(TAG "Open fail, fd: %d\n", fd);
		return -1;		
	}

	if (ioctl(fd, FIFO_CLEAR, 0) < 0 )
		printf(TAG "Ioctl fail.\n");

	epfd = epoll_create(1);
	if (epfd < 0) {
		printf(TAG "epoll_create fail, epdf: %d\n", epfd);
		return -1;		
	}

	bzero(&ev_globalfifo, sizeof(struct epoll_event));
	ev_globalfifo.events = EPOLLIN |EPOLLPRI;

	printf(TAG "epoll_ctl ADD before.\n");
	err = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev_globalfifo);
	if (err < 0) {
		printf(TAG "epoll_ctl ADD fail, err: %d\n", err);
		return -1;		
	}
	printf(TAG "epoll_ctl ADD after.\n");

	// epoll_wait
	printf(TAG "epoll_wait before.\n");
	err = epoll_wait(epfd, &ev_globalfifo, 1, TIMEOUT);
	if (err < 0)
		printf(TAG "epoll_wait fail, err: %d\n", err);
	else if (err == 0)
		printf(TAG "epoll_wait no data input in FIFO whthin : %d ms\n", TIMEOUT);
	else
		printf(TAG "FIFO is not empty\n");
	printf(TAG "epoll_wait after.\n");

	printf(TAG "epoll_ctl DEL before.\n");
	err = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev_globalfifo);
	if (err < 0) {
		printf(TAG "epoll_ctl DEL fail, err: %d\n", err);
		return -1;		
	}
	printf(TAG "epoll_ctl DEL after.\n");

	printf(TAG "Ending\n");

	close(fd);

	return 0;
}

/*

test 1

wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ gcc 2.userspace-poll-NONBLOCK.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-poll] epoll_ctl ADD before.
[userspace-poll] epoll_ctl ADD after.
[userspace-poll] epoll_wait before.
[userspace-poll] epoll_wait no data input in FIFO whthin : 15000 ms
[userspace-poll] epoll_wait after.
[userspace-poll] epoll_ctl DEL before.
[userspace-poll] epoll_ctl DEL after.
[userspace-poll] Ending
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[67744.355913] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[67744.355917] [character_devices_wq_poll] [globalfifo_ioctl] ioctl CLEAR.
[67744.355939] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.  // can wr
[67759.376476] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 


test 2

wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[67871.257592] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[67871.257596] [character_devices_wq_poll] [globalfifo_ioctl] ioctl CLEAR.
[67871.257614] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM. // can wr
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hello wu 233' > /dev/globalfifo"
[userspace-poll] FIFO is not empty
[userspace-poll] epoll_wait after.
[userspace-poll] epoll_ctl DEL before.
[userspace-poll] epoll_ctl DEL after.
[userspace-poll] Ending
[1]+  Done                    ./a.out
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[67878.949698] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[67878.949705] [character_devices_wq_poll] [globalfifo_write] count: 13. start.
[67878.949707] [character_devices_wq_poll] [globalfifo_write] written 13 bytes, current_len: 13.
[67878.949707] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[67878.949727] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[67878.949729] [character_devices_wq_poll] [globalfifo_release] release.
[67878.949736] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.  // can RD
[67878.949738] [character_devices_wq_poll] [globalfifo_read] schedule after.
[67878.949739] [character_devices_wq_poll] [globalfifo_read] signal_pending before.
[67878.949740] [character_devices_wq_poll] [globalfifo_read] signal_pending after.
[67878.949741] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[67878.949743] [character_devices_wq_poll] [globalfifo_read] read 13 bytes, current_len: 0.
[67878.949745] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible before.
[67878.949746] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible after.
[67878.949755] [character_devices_wq_poll] [globalfifo_read] count: 65536. start.
[67878.949756] [character_devices_wq_poll] [globalfifo_read] schedule before.
[67878.949758] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 

*/
