
# Linux 异步通知和异步IO


异步通知的意思是：一旦设备就绪，则主动通知应用程序，这样应用程序根本就不需要查询设备状态，这一点非常类似于硬件上“中断“ 的概念，比较准确的称谓是“信号驱动的异步 I / O ”。
信号是在软件层次上对中断机制的一种模拟，在原理上，一个进程收到一个信号与处理器收到一个中断请求可以说是一样的。

信号是异步的，一个进程不必通过任何操作来等待信号的到达，事实上，进程也不知道信号到底什么时候到达。

这几种 I / O 方式可以相互补充，根据不同场景合理使用：

- 阻塞 I / O 意味着一直等待设备可访问后再访问，
- 非阻塞 I / O 中使用poll0）意味着查询设备是否可访问，
- 而异步通知则意味着设备通知用户自身可访问，之后用户再进行 I / O 处理。

![阻塞、非阻塞和异步通知](https://img-blog.csdnimg.cn/b4559b093fd8466993ae80c03d83dfa8.png)

# Linux 异步通知编程

## 信号的接收

例子：

```c
#include <stdio.h>
#include <signal.h> //signal()
#include <stdlib.h> //exit()

void sigterm_handler(int signo)
{
	printf("Have caught sig N.O. %d\n", signo);
	exit(0);
}

int main()
{
	signal(SIGINT , sigterm_handler); // Ctrl+C   : SIGINT:2
	signal(SIGTERM, sigterm_handler); // kill pid : SIGTERM:15
	while (1);

	return 0;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ gcc 1.Ctrl+C_signal.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ ./a.out 
^CHave caught sig N.O. 2
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ ./a.out &
[1] 15812
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ kill 15812
Have caught sig N.O. 15
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ 
[1]+  Done                    ./a.out
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ 

*/
```

除了signal() 函数外， sigaction （函数可用我改变进程接收到特定信号后的行为，它的原型为： 
```
int sigaction ( int signum , const struct sigaction * act , struct sigaction * oldact ));
```

- 该函数的第一个参数为信号的值，可以是除 SIGKILL 及 SIGSTOP 外的任何一个特定有效的信号。
- 第二个参数是指向结构体 sigaction 的一个实例的指针，在结构体 sigaction 的实例中，指定了对特定信号的处理函数，若为空，则进程会以缺省方式对信号处理；
- 第三个参数 oldact 指向的对象用来保存原来对相应信号的处理函数，可指定 oldact 为 NULL 。
- 如果把第二、第三个参数都设为 NULL ，那么该函数可用于检查信号的有效性。

先来看一个使用信号实现异步通知的例子，它通过 signal ( SIGIO , input handler ）对标准输人文件描述 STDIN_FILENO 启动信号机制。
用户输入后，应用程序将接收到 SIGIO 信号，其处理函数 input handler (）将被调用：

```c
#include <stdio.h>
#include <signal.h> //signal()
#include <fcntl.h>  //fcntl()
#include <unistd.h> //STDIN_FILENO

//#include <sys/types.h> //()
//#include <sys/stat.h> //()


#define MAX_LEN 100

void input_handler(int signo)
{
	char data[MAX_LEN];
	int len;

	printf("Have caught sig N.O. %d\n", signo);
	
	len = read(STDIN_FILENO, &data, MAX_LEN);
	data[len] = 0; 
	printf("Input available: %s\n", data);
}

int main()
{
	int oflags;

	printf("STDIN_FILENO:%d\n", STDIN_FILENO);
	printf("STDOUT_FILENO:%d\n", STDOUT_FILENO);
	printf("STDERR_FILENO:%d\n", STDERR_FILENO);
	// 1. set fd owner
	fcntl(STDIN_FILENO, F_SETOWN, getpid());
	// 2. change to FASYNC
	oflags = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC);
	// 3. add singnal function
	signal(SIGIO , input_handler); //SIGIO:29

	while (1);

	return 0;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ gcc 2.STDIN_FILENO_signal.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO$ ./a.out 
STDIN_FILENO:0
STDOUT_FILENO:1
STDERR_FILENO:2
Have caught sig N.O. 29

Input available: 

Have caught sig N.O. 29
Hello wu
Input available: Hello wu

Have caught sig N.O. 29
haha.................................
Input available: haha.................................

Have caught sig N.O. 29



*/
```

程序打印从中可以看出，当用户输入一串字符后，标准输入设备释放 SIGIO 信号，这个信号“中断”与驱使对应的应用程序中的 input_handler()得以执行，并将用户输人显示出来。
由此可见，为了能在用户空间中处理一个设备释放的信号，它必须完成3项工作：

1. 通过 F_SETOWN IO 控制命令设置设备文件的拥有者为本进程，这样从设备驱动发出的信号才能被本进程接收到。
2. 通过 F_SETFL IO控制命令设置设备文件以支持 FASYNC ，即异步通知模式。
3. 通过 signal() 函数连接信号和信号处理函数。


## 信号的释放

在设备驱动和应用程序的异步通知交互中，仅仅在应用程序端捕获信号是不够的，因为信号的源头在设备驱动端。
因此，应该在合适的时机让设备驱动释放信号，在设备驱动程序中增加信号释放的相关代码。
为了使设备支持异步通知机制，驱动程序中涉及3项工作。

1. 支持 F_SETOWN 命令，能在这个控制命令处理中设置 filp -> f_owner 为对应进程 ID 。不过此项工作已由内核完成，设备驱动无须处理。
2. 支持 F_SETFL 命令的处理，每当 FASYNC 标志改变时，驱动程序中的 fasync 函数将得以执行。因此，驱动中应该实现.fasync函数。
3. 在设备资源可获得时，调用 kill_fasync 函数激发相应的信号。

驱动中的上述3项工作和应用程序中的3项工作是一一对应的，如下所示为异步通知处理过程中用户空间和设备驱动的交互。

![异步通知中设备驱动和异步通知的交互](https://img-blog.csdnimg.cn/6f503933d97d49158456555e149e1f13.png)


设备驱动中异步通知编程比较简单，主要用到一项数据结构和两个函数。
数据结构是 fasync struct 结构体，两个函数分别是：

1. 处理 FASYNC 标志变更的函数。 
```
int fasync_helper ( int fd , struct file * filp , int mode , struct fasync_struct ** fa );
```
2. 释放信号用的函数。 
```
void kil1_fasync ( struct fasync_struct ** fa , int sig , int band );
```

和其他的设备驱动一样，将 fasync_struct 结构体指针放在设备结构体中仍然是最佳选择，驱动函数如下添加:

```c
struct globalfifo_dev {
	struct cdev cdev;
	unsigned char mem[GLOBALFIFO_SIZE];
	struct mutex mutex;//

	unsigned int current_len; /**/
	wait_queue_head_t r_wait; /**/
	wait_queue_head_t w_wait; /**/
	struct fasync_struct *async_queue; //**
};


static int globalfifo_fasync(int fd, struct file *filp, int mode) //**
{
	struct globalfifo_dev *dev = filp->private_data;

	printk(mode ? TAG "[%s] add.\n": TAG "[%s] remove.\n", __func__);
	fasync_helper(fd, filp, mode, &dev->async_queue);

	return 0;
}

static ssize_t globalfifo_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
...
		printk(TAG "[%s] wake_up_interruptible after.\n", __func__);

		if (dev->async_queue) {	//**
			kill_fasync(&dev->async_queue, SIGIO, POLLIN);
			printk(TAG "[%s] Sent kill SIGIO ... ...\n", __func__);
		}

		ret = count;
	}
...
}

static int globalfifo_release(struct inode *inode, struct file *filp)
{
	printk(TAG "[%s] release.\n", __func__);
	globalfifo_fasync(-1, filp, 0); //mode:0-> remove FASYNC from f_flags, 1 is add it.

	return 0;
}
static struct file_operations globalfifo_fops = {
...
	.fasync = globalfifo_fasync, //**

};
```

用户层测试程序：

```c
#include <stdio.h>
#include <signal.h> //signal()
#include <fcntl.h>  //fcntl()
#include <unistd.h> //STDIN_FILENO

//#include <sys/types.h> //()
//#include <sys/stat.h> //()

#define TAG "[userspace-signal] "

static void input_handler(int signo)
{
	printf(TAG "123.Have caught a signal from globalfifo, sig N.O. %d\n", signo);
}

void main()
{
	int fd, oflags;
	
	fd = open("/dev/globalfifo", O_RDWR, S_IRUSR | S_IWUSR);
	//fd = open("/dev/globalfifo", O_RDWR, S_IRWXU | S_IRWXG |S_IRWXO);
	//fd = open("/dev/globalfifo", O_RDONLY , S_IRUSR);
	//fd = open("/dev/globalfifo", O_RDONLY);
	if (fd == -1) {
		printf(TAG "Open fail, fd: %d\n", fd);		
	}

puts("");

printf(TAG "1. set fd owner\n");	
	// 1. set fd owner
	fcntl(fd, F_SETOWN, getpid());

printf(TAG "2. change to FASYNC\n");
	// 2. change to FASYNC
	oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags | FASYNC);

printf(TAG "3. add singnal function\n");
	// 3. add singnal function
	signal(SIGIO , input_handler); //SIGIO:29

printf(TAG "while.\n");
	while (1) {
		sleep(100);
	}

printf(TAG "Ending\n");

}

```

**AsyncIO 完整例子代码**：[1.signal](https://github.com/1040003585/linux_driver_study/tree/main/song09--AsyncNotify_AsyncIO/1.signal)


# Linux 异步IO

Linux 中最常用的输人／输出（ I / O ）模型是异步 I / O 。在这个模型中，当请求发出之后，应用程序就会阻塞，直到请求满足为止。
这是一种很好的解决方案，调用应用程序在等待10请求完成时不需要占用 CPU 。
但是在许多应用场景中， I / O 请求可能需要与 CPU 消耗产生交叠，以充分利用 CPU 和 I / O 提高吞吐率。

## GNU C 库的AIO

Linux 的 AIO 有多种实现，其中一种实现是在用户空间的 glibc 库中实现的，
它本质上是借用了多线程模型，用开启新的线程以同步的方法来做 I / O ，新的 AIO 辅助线程与发起 AIO 的线程以 pthread cond signal0的形式进行线程间的同步。 

glibc 的 AIO 主要包括如下函数：
```
1. aio_read(struct aiocb *aiocbp)，参数可为文件fd/套接字/管道，成功返回0，错误返回-1，并设置errno。
2. aio_write(struct aiocb *aiocbp)，成功返回0，错误返回-1，并设置errno。
3. aio_error(struct aiocb *aiocbp)，在处理返回EINPROGRESS，请求被取消返回ECANCELED，错误返回-1，并设置errno。
4. aio_return(struct aiocb *aiocbp)，aio_error判断之后调用这个，返回值等同与aio_read，aio_write。
5. aio_suspend(const struct aiocb *const aiocbp[], int n, const struct timespec *timout)，阻塞调用进程，直到异步完成，可以用信号或回调实现。
6. aio_cancel(int fd, struct aiocb *aiocbp)，取消IO请求，如果要取消全部：第二参数填NULL。
7. lio_listio(int mode, struct aiocb *list[], int nent, struct sigevent *sig)，同时发起多个IO请求。
```

例子1：

```c
#include <stdio.h>
#include <aio.h>
#include <errno.h> //EINPROGRESS
#include <stdlib.h> // malloc
#include <strings.h> // bzero
#include <fcntl.h>  //O_RDONLY

#define TAG "[1.aio.c] "
#define BUFSIZE 100

int main ()
{
	int fd, ret;
	struct aiocb my_aiocb;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		perror(TAG "Open");

	bzero(&my_aiocb, sizeof(struct aiocb));

	my_aiocb.aio_buf = malloc(BUFSIZE + 1);
	if (!my_aiocb.aio_buf)
		perror(TAG "malloc");	

	my_aiocb.aio_fildes = fd;
	my_aiocb.aio_nbytes = BUFSIZE;
	my_aiocb.aio_offset = 0;

	ret = aio_read(&my_aiocb);
	if (ret < 0)
		perror(TAG "aio_read");	

	while (aio_error(&my_aiocb) == EINPROGRESS)
		continue;

	if ((ret = aio_return(&my_aiocb)) > 0) {
		printf("ret:%d \n", ret);
		printf("my_aiocb.aio_buf:%s \n", my_aiocb.aio_buf);
	} else {
		printf("ret:%d \n", ret);
		// and errono...
	}
	return 0;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ gcc 1.aio.c 
/tmp/ccKiszY7.o: In function `main':
1.aio.c:(.text+0xa1): undefined reference to `aio_read'
1.aio.c:(.text+0xc9): undefined reference to `aio_error'
1.aio.c:(.text+0xda): undefined reference to `aio_return'
collect2: error: ld returned 1 exit status
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ gcc 1.aio.c -lrt
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ ./a.out 
ret:10 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ 

*/


// add printf("my_aiocb.aio_buf:%s \n", my_aiocb.aio_buf);

/*
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ gcc 1.aio.c -lrt
1.aio.c: In function ‘main’:
1.aio.c:39:3: warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘volatile void *’ [-Wformat=]
   printf("my_aiocb.aio_buf:%s \n", my_aiocb.aio_buf);
   ^
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ ./a.out 
ret:9 
my_aiocb.aio_buf:hello
..
 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ 

*/
```

例子2：

```c
#include <stdio.h>
#include <aio.h>
#include <errno.h> //EINPROGRESS
#include <stdlib.h> // malloc
#include <strings.h> // bzero
#include <fcntl.h>  //O_RDONLY

#define TAG "[2.lio_listio.c] "
#define BUFSIZE 100

#define MAX_LIST 4

int main ()
{
	int i, fd, ret;
	struct aiocb my_aiocb[MAX_LIST];
	struct aiocb *list[MAX_LIST];

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		perror(TAG "Open");

	bzero(my_aiocb, sizeof(struct aiocb) * MAX_LIST);//
	//bzero(my_aiocb, sizeof(my_aiocb));//
	bzero((char *)list, sizeof(list));

	for (i = 0; i < MAX_LIST - 1; i++) { // my_aiocb[MAX_LIST-1-1] is null
		my_aiocb[i].aio_buf = malloc(BUFSIZE + 1);
		if (!my_aiocb[i].aio_buf)
			perror(TAG "malloc");	

		my_aiocb[i].aio_fildes = fd;
		my_aiocb[i].aio_nbytes = BUFSIZE;
		my_aiocb[i].aio_offset = i; //0

		my_aiocb[i].aio_lio_opcode = LIO_READ; //or LIO_WRITE, LIO_NOP
	}

	// lio_listio
	ret = lio_listio(LIO_WAIT, list, MAX_LIST, NULL);
	if (ret < 0)
		perror(TAG "lio_listio");	

	for (i = 0; i < MAX_LIST; i++) {
		ret = aio_read(&my_aiocb[i]);
		if (ret < 0)
			perror(TAG "aio_read");	

		while (aio_error(&my_aiocb[i]) == EINPROGRESS)
			continue;

		if ((ret = aio_return(&my_aiocb[i])) > 0) {
			printf(TAG "ret:%d \n", ret);
			printf("my_aiocb[%d].aio_buf:%s \n", i, (char *)my_aiocb[i].aio_buf);
		} else {
			printf(TAG "ret:%d \n", ret);
			// and errono...
		}
	}

	return 0;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ gcc 2.lio_listio.c -lrt
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ ./a.out [2.lio_listio.c] ret:9 
my_aiocb[0].aio_buf:hello
..
 
[2.lio_listio.c] ret:8 
my_aiocb[1].aio_buf:ello
..
 
[2.lio_listio.c] ret:7 
my_aiocb[2].aio_buf:llo
..
 
[2.lio_listio.c] ret:0 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/2.Linux-AsyncIO/1.GNU_Clib_AIO$ 


*/
```

更多：
https://www.gnu.org/software/libc/sources.html
https://www.gnu.org/software/libc/manual/

## Linux 内核的AIO

Linux AIO 也可以由内核空间实现，异步 I / O 是 Linux 2.6以后版本内核的一个标准特性。

**对于块设备而言**， AIO 可以一次性发出大量的 read / write 调用并且通过通用块层的 I / O 调度来获得更好的性能，用户程序也可以减少过多的同步负载，还可以在业务逻辑中更灵活地进行并发控制和负载均衡。
相较于 glibc 的用户空间多线程同步等实现也减少了线程的负载和内核上下文切换等。

**对于网络设备而言**，在 socket 层面上，也可以使用 AIO ，让 CPU 和网卡的收发动作充分交叠以改善吞吐性能。
选择正确的 I / O 模型对系统性能的影响很大，有兴趣的读者可以参阅著名的C10K问题（指的是服务器同时支持成千上万个客户端的问题），详见网址: http://www.kegel.com/c10k.html

在用户空间中，我们一般要结合 libaio 来进行内核 AIO 的系统调用。
AIO 的读写请求都用 io_submit 下发。
下发前通过 io_prep_pwrite 和 io_prep_pread 生成 iocb 的结构体，作为 io_submit 的参数。
这个结构体指定了读写类型、起始地址、长度和设备标志符等信息。
读写请求下发之后，使用 io_getevents 函数等待 I /0完成事件。 
io_set_calback 则可设置一个 AIO 完成的回调函数。

如下演示了一个简单的利用 libaio 向内核发起 AIO 请求的模版。使用命令 `gcc aior.c -o aior -laio` 编译，运行时带1个文本文件路径作为参数，该程序会打印该文本文件前4096个字节的内容。

```c

```

用户空间调用 `io_submit()` 后，对应于用户传递的每一个 iocb 结构，内核会生成一个与之对应的 kiocb 结构。 
`file_operations` 包含3个与 AIO 相关的成员函数： 

```c
ssize_t (*aio_read )( struct kiocb * iocb , const struct iovec * iov , unsigned long nr_segs , loff_t pos ); 
ssize_t (*aio_write)( struct kiocb * iocb , const struct iovec * iov , unsigned long nr_segs , loff_t pos ); 
int (*aio_fsync )( struct kiocb * iocb , int datasync ); 
```

**`io_submit` 系统调用间接引起了 file_operations 中的 aio_read 和 aio_write 的调用**。

在新的原型中，则可以传递一个向量 iovec ，它含有多段缓冲区。详见位于 https://lwn.net/Articles/170954 的文档《 Asynchronous V O and vectored operations 》。 
AlO 一般由内核空间的通用代码处理，***对于块设备和网络设备而言，一般在 Linux 核心层的代码已经解决。字符设备驱动一般不需要实现 AIO 支持。***
Linux 内核中对字符设备驱动实现 AIO 的特例包括 `drivers/char/mem.c` 里实现的 null 、 zero 等，由于 zero 这样的虚拟设备其实也不存在在要去读的时候读不到东西的情况，
所以 aio_read_zero() 本质上也不包含异步操作，不过从代码aio_read_zero我们可以一窥 iovec 的全貌。

