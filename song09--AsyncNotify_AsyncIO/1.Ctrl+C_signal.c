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
