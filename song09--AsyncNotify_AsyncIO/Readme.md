
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
```int sigaction ( int signum , const struct sigaction * act , struct sigaction * oldact ));```

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

![异步通知中设备驱动和异步通知的交互](https://img-blog.csdnimg.cn/6f503933d97d49158456555e149e1f13.png)

![异步IO的时序](https://img-blog.csdnimg.cn/a22522b9503d47c4b0c45f7a6780b066.png)
