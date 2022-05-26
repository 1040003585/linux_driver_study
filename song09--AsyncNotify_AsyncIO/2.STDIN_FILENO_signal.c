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
