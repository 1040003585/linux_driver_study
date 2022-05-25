
# 阻塞和非阻塞I/O


**阻塞操作**是指在执行设备操作时，若不能获得资源，则挂起进程直到满足可操作的条件后再进行操作。被挂起的进程进人睡眠状态，被从调度器的运荷队列移走，直到等待的条件被满足。

**非阻塞操作**的进程在不能进行设备操作时，并不挂起，它要么放弃，要么不停地查询，直至可以进行操作为止。

在阻塞访问时，不能获取资源的进程将进人休眠，它将 CPU 资源“礼让”给其他进程。因为阻塞的进程会进入休眠状态，所以必须确保有个地方能够唤醒休眠的进程，否则，进程就真的“寿终正寝”了。
唤醒进程的地方最大可能发生在中断里面，因为在硬件资源获得的同时往往伴随着一个中断。而非阻塞的进程则不断尝试，直到可以进行 IO 。

![阻塞和非阻塞I/O](https://img-blog.csdnimg.cn/740a7e41b5d345a4b7603cdd84e9222c.png)

** 1. Kernel 空间增加等待队列对访问阻塞IO 支持的方法；**
** 2. 用户空间可以用轮询机制查询是否可进行非阻塞访问；**


## 1. 等待队列

Linux 驱动程序中，可以使用**等待队列（Wait Queue）** 来实现阻塞进程的唤醒。
它以队列为基础数据结构，与进程调度机制紧密结合，可以用来同步对系统资源的访问，信号量在内核中也依赖等待队列来实现。


**等待事件**

wait_event()和 wait_event_interruptible() 前者不能被信号唤醒，后者可以。
*_timeout(queue, condition, timeout) 表示如果达到阻塞等待的超时jiffy 时间，无论condition 是否满足都会返回。

**唤醒队列**

wake_up()和 wake_up_interruptible() 操作会唤醒以 queue 作为等待队列头部的队列中所有的进程。 

1. wake_up() 应该与 wait_event() 或 wait_event_timeout() 成对使用；
2. wake_up_interruptible() 则应与 wait_event_interruptible() 或 wait_event_interruptible_timeout() 成对使用。 

- wake_up() 可唤醒处于 TASK_INTERRUPTIBLE 和 TASK_UNINTERRUPTIBLE 的进程;
- wake_up_interruptible() 只能唤醒处于 TASK_INTERRUPTIBLE 的进程。


**在等待队列上睡眠**
```c
sleep_on(wait_queue_head_t * q ); 
interruptible_sleep_on(wait_queue_head_t * q); 
```

`sleep_on()`函数的作用就是将目前进程的状态置成 TASK UNINTERRUPTIBLE ，并定义一个等待队列元素，之后把它挂到等待队列头部 q 指向的双向链表，直到资源可获得， q 队列指向链接的进程被唤醒。 

`interruptible_sleep_on()`与 sleep_on()函数类似，其作用是将目前进程的状态置成 TASK INTERRUPTIBLE ，并定义一个等待队列元素，之后把它附属到 q 指向的队列，直到资源可获得（ q 指引的等待队列被唤醒）或者进程收到信号。 
 
- sleep_on()函数应该与 wake_up()成对使用；
- interruptible_sleep_on()应该与wake_up_interruptible()成对使用。


**等待队列例子：** `drivers/power/supply/mediatek/charger/mtk_charger.c` *（code来源开源托管平台）*
```c
void _wake_up_charger(struct charger_manager *info)
{
	unsigned long flags;

	if (info == NULL)
		return;

	spin_lock_irqsave(&info->slock, flags);
	if (!info->charger_wakelock.active)
		__pm_stay_awake(&info->charger_wakelock);
	spin_unlock_irqrestore(&info->slock, flags);
	info->charger_thread_timeout = true;
	wake_up(&info->wait_que);
}
...

static int charger_routine_thread(void *arg)
{
	struct charger_manager *info = arg;
	unsigned long flags;
	bool is_charger_on;
	int bat_current, chg_current;

	while (1) {
		wait_event(info->wait_que,
			(info->charger_thread_timeout == true));

		mutex_lock(&info->charger_lock);
		spin_lock_irqsave(&info->slock, flags);
		if (!info->charger_wakelock.active)
			__pm_stay_awake(&info->charger_wakelock);
		spin_unlock_irqrestore(&info->slock, flags);

		info->charger_thread_timeout = false;
	...
	
static int mtk_charger_probe(struct platform_device *pdev)
{
	init_waitqueue_head(&info->wait_que);
```

**使用等待队列完整例子代码**：[1.Wait-Queue](https://github.com/1040003585/linux_driver_study/tree/main/song08--Block_NONBLOCK/1.Wait-Queue)


## 2. 轮询操作

使用非阻塞 I/O 的应用程序通常会使用 select 和 poll 系统调用査询是否可对设备进行无阻塞的访问。 
select() 和poll() 系统调用最终会使设备驱动中的.poll() 函数被执行，在Linux2.5.45内核中还引入了epoll，即扩展的 poll()。

select 和poll系统调用的本质一样，前者在 BSD UNIX 中引入，后者在 System V 引入。


**1.select()**

应用程序中最广泛用到的是 BSD UNIX 中引人的 select （系统调用，其原型为： 

```c
int select ( int numfds , fd set * readfd , fd _ set * writefds , fd _ set * exceptfds , struct timeval * timeout );
```

其中 readfds 、 writefds 、 exceptfds 分别是被 select 监视的读写和异常处理的文件描述符集合， numfds 的值是需要检查的号码最高的 fd 加1。
 readfds 文件集中的任何一个文件变得可读，select 返回；同理， writefds 文件集中的任何一个文件变得可写， select 也饭回。
 
 如下图所示，第一次对 n 个文件进行 select 的时候，若任何一个文件满足要求， select 就直接返回；第2次再进行 select 的时候，没有文件满足读写要求，select 的进程阻裹且睡眼。
 由于调用 select 的时候，每个驱动的polI0接口都会被调用到，实际上执行 select 的进程被挂到了每个驱动的等待队列上，可以被任何一个驱动唤醒。如果 FD ，变得可读写， select 返回。

![多路复用select()](https://img-blog.csdnimg.cn/a2bee087f6414051901de7258d1bb0cc.png)


**2.poll()**

 poll 的功能和实现原理与 select相似，其函数原型为： 
 
```c
 int poll ( struct pollfd * fds , nfds t nfds , int timeout );
```
  
 
**3.epoll()**
 
当多路复用的文件数量庞大、 I/O 流量频繁的时候，一般不太适合使用 select 和poll, 此种情况下， selectO 和 pollO 的性能表现较差，我们宜使用 epoll 。
epoll 的最大好处是不会随着 fd 的数目增长而降低效率， select (）则会随着 fd 的数量增大性能下降明显。

与 epoll 相关的用户空间编程接口包括： 

```c
int epol1_ create ( int size );
```

创建 epoll 的句柄， size 用来告诉内核要监听多少个 fd 。
需要注意的是，当创建好 epoll 句柄后，它本身也会占用一个 fd 值，所以在使用完 epoll 后，必须调用close关闭。 

```c
int epoll_ctl ( int epfd , int op , int fd, struct epoll_event _* event );
```

告诉内核要监听什么类型的事件。

第1个参数是 epoll create (）的返回值。
第2个参数表示动作含：

- EPOLLCTL_ADD ：注册新的 fd 到 epfd 中。 
- EPOLLCTL_MOD ：修改已经注册的 fd 的监听事件。 
- EPOLL_CTLDEL ：从 pfd 中删除一个 fd 。 

第3个参数是需要监析的 fd ，
第4个参数是告诉内核需要监听的事件类型， 

event 结构如下：

```c
struct epoll_struct {
	__uint32_t events ; /* Epo11 events */
	epol1_data_t data ; /* User data variable */ 
}
```

events 可以是以下几个宏的“或”: 

- EPOLLIN ：表示对应的文件描述符可以读。 
- EPOLLOUT ：表示对应的文件描述符可以写。 
- EPOLLPRI ：表示对应的文件描述符有紧急的数据可读（这里应该表示的是有 socket 外部数据；
- ...
- EPOLLONESHOT ：意味着一次性监听，当监听完这次事件之后.

如果还需要继续监听这个 fd 的话，需要再次把这个 fd 加人到 epoll 队列里。 

```c
int epoll _ wait ( int epfd , struct epoll event * events , int maxevents , int timeout );
```

等待事件的产生，其中 events 参数是输出参数，用来从内核得到事件的集合， maxevents 告诉内核本次最多收多少事件， maxevents 的值不能大于创建 epol create 时的 size ，
参数 timeout 是超时时间（以毫秒为单位，0意味着立即返回，-1意味着永久等待）。
该函数的返回值是需要处理的事件数目，如返回0，则表示已超时。

位于https://www.kernel.org/doc/ols/2004/ols2004v1-pages-215-226.pdf的文档《 comparing and Evaluating epoll , select , and poll Event Mechanisms 》对比了 select 、 epoll 、 pol 之间的一些性能。

一般来说，***当涉及的 fd 数量较必的时候，使用 seleet 是合适的；如果涉及的 fd 很多，如在大规模并发的服务器中侦听许多 socket 的时候，则不太适合选用 select ，而适合选用 epoll。***



**轮询操作例子：**

设备驱动中的.poll()本身不会阻塞，但是与 poll() 、 select() 和 epoll() 相关的系统调用则会阻塞地等待至少一个文件描述符集合可访问或超时。

**1.驱动添加 .poll函数**

```c

static unsigned int globalfifo_poll(struct file *filp, poll_table *wait)
{
	unsigned int mask = 0;
	struct globalfifo_dev *dev = filp->private_data;

	mutex_lock(&dev->mutex);//
	poll_wait(filp, &dev->r_wait, wait);
	poll_wait(filp, &dev->w_wait, wait);

	if (dev->current_len != 0) {
		mask |= POLLIN | POLLRDNORM;
		printk(TAG "[%s] poll POLLIN | POLLRDNORM.\n", __func__);
	}
	if (dev->current_len != GLOBALFIFO_SIZE) {
		mask |= POLLOUT | POLLWRNORM;
		printk(TAG "[%s] poll POLLOUT | POLLWRNORM.\n", __func__);
	}

	mutex_unlock(&dev->mutex);//

	return mask;
}

static struct file_operations globalfifo_fops = {
	...
	.poll = globalfifo_poll, /**/

};
```

**2.使用 select() 监控驱动可读写状态**

```c
#include <stdio.h>
#include <fcntl.h>
//#include <string.h>

#include <sys/types.h>

//#define GLOBALFIFO_MAGIC 'g'
//#define FIFO_CLEAR _IO(GLOBALFIFO_MAGIC, 0)
//#define FIFO_CLEAR 0x1
#define FIFO_CLEAR 0x0

#define TAG "[userspace-select] "

int main(int argc, char * argv[])
{
	int fd, num;
	fd_set rfds, wfds;

//	fd = open("/dev/globalfifo", O_RDWR| O_NONBLOCK); // RDDW, MUST be: sudo ./a.out
/*
^Cwu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ gcc 1.userspace-select-NONBLOCK.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
Open fail, fd: -1
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ls -l
total 16
-rw-rw-r-- 1 wu-being wu-being  922 May 25 14:59 1.userspace-select-NONBLOCK.c
-rwxrwxr-x 1 wu-being wu-being 7511 May 25 14:59 a.out
-rw-rw-r-- 1 wu-being wu-being  506 May 21 22:39 Makefile
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ls -l /dev/globalfifo
crw-r--r-- 1 root root 250, 0 May 25 01:31 /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
*/
	fd = open("/dev/globalfifo", O_RDONLY| O_NONBLOCK); // can just ./a.out to run it.
	if (fd < 0) {
		printf("Open fail, fd: %d\n", fd);
		return -1;		
	}

	if (ioctl(fd, FIFO_CLEAR, 0) < 0 )
		printf(TAG "Ioctl fail.\n");

	while (1) {
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		FD_SET(fd, &rfds);
		FD_SET(fd, &wfds);

		select(fd+1, &rfds, &wfds, NULL, NULL);

		if (FD_ISSET(fd, &rfds))
			printf(TAG "Poll monitor: can be read.\n");
		if (FD_ISSET(fd, &wfds))
			printf(TAG "Poll monitor: can be written.\n");

		sleep(1);
	}

	printf(TAG "Ending");

	close(fd);

	return 0;
}
/*

test:

wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Ioctl fail.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[64130.272356] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[64130.272375] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64131.272905] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64132.273591] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64132.996937] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel22222 ' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[64144.985867] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[64144.985874] [character_devices_wq_poll] [globalfifo_write] count: 10. start.
[64144.985875] [character_devices_wq_poll] [globalfifo_write] written 10 bytes, current_len: 10.
[64144.985875] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[64144.985876] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[64144.985877] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Ioctl fail.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be written.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[64150.088260] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[64150.088297] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.
[64150.088298] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64151.088790] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.
[64151.088793] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64151.506281] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel22222 3333' > /dev/globalfifo"wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel22222 3333 444444444' > /dev/globalfifo"


pending writen. cat /dev/globalfifo:


wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ cat /dev/globalfifo 
hel22222 
hel22222 3333
hel22222 3333 444444444

wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices[64166.493266] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[64166.493273] [character_devices_wq_poll] [globalfifo_write] count: 14. start.
[64166.493308] [character_devices_wq_poll] [globalfifo_write] written 14 bytes, current_len: 24.
[64166.493309] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[64166.493309] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[64166.493312] [character_devices_wq_poll] [globalfifo_release] release.
[64171.072357] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[64171.072364] [character_devices_wq_poll] [globalfifo_write] count: 24. start.
[64171.072365] [character_devices_wq_poll] [globalfifo_write] written 8 bytes, current_len: 32.
[64171.072366] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[64171.072366] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[64171.072367] [character_devices_wq_poll] [globalfifo_write] count: 16. start.
[64171.072368] [character_devices_wq_poll] [globalfifo_write] schedule before.
[64190.394918] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[64190.394926] [character_devices_wq_poll] [globalfifo_read] count: 65536. start.
[64190.394929] [character_devices_wq_poll] [globalfifo_read] read 32 bytes, current_len: 0.
[64190.394929] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible before.
[64190.394941] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible after.
[64190.394946] [character_devices_wq_poll] [globalfifo_read] count: 65536. start.
[64190.394947] [character_devices_wq_poll] [globalfifo_read] schedule before.
[64190.394964] [character_devices_wq_poll] [globalfifo_write] schedule after.
[64190.394966] [character_devices_wq_poll] [globalfifo_write] signal_pending before.
[64190.394967] [character_devices_wq_poll] [globalfifo_write]  signal_pending after.
[64190.394968] [character_devices_wq_poll] [globalfifo_write] written 16 bytes, current_len: 16.
[64190.394969] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[64190.394978] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[64190.394983] [character_devices_wq_poll] [globalfifo_release] release.
[64190.394989] [character_devices_wq_poll] [globalfifo_read] schedule after.
[64190.394990] [character_devices_wq_poll] [globalfifo_read] signal_pending before.
[64190.394991] [character_devices_wq_poll] [globalfifo_read] signal_pending after.
[64190.394991] [character_devices_wq_poll] [globalfifo_read] read 16 bytes, current_len: 0.
[64190.394992] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible before.
[64190.394992] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible after.
[64190.394996] [character_devices_wq_poll] [globalfifo_read] count: 65536. start.
[64190.394996] [character_devices_wq_poll] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Ioctl fail.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices[64204.626854] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[64204.626874] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64205.627497] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64206.628029] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64207.628573] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[64207.724065] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel22222 3333' > /dev/globalfifo"wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Ioctl fail.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 


wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ cat /dev/globalfifo 
hel22222 
hel22222 3333
hel22222 3333 444444444
hel22222 3333


*/

```

**3.使用 epoll() 监控驱动可读状态**

```c
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
```


**使用等待队列完整例子代码**：[2.Poll](https://github.com/1040003585/linux_driver_study/tree/main/song08--Block_NONBLOCK/2.Poll)
