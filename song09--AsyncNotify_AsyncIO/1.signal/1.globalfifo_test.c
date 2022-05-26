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

/*

*/
