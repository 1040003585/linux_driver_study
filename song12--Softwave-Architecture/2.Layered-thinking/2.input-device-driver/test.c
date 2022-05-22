#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>

int main()
{
    char          file_name[64];           /* RATS: Use ok, but could be better */
    char          buf[256] = { 0, };  /* RATS: Use ok */
    int           fd = 0;
    int           i;
    for (i = 0; i < 32; i++)
    {
        sprintf(file_name, "/dev/input/event%d", i);
        if ((fd = open(file_name, O_RDONLY, 0)) >= 0)
        {
 	   printf("\nOpen:\n");

           ioctl(fd, EVIOCGNAME(sizeof(buf)), buf);
            /*if(strstr(buf, "MTOUC Touch"))
            {
                close(fd);
                return i;
            }*/
            printf("file_name: %s\n", file_name);
            printf("read name : %s\n", buf);
            close(fd);
        }
    }

    printf("\nDone.\n");

    return -1;
}

/*
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/2.input-device-driver$ gcc test.c 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/2.input-device-driver$ sudo ./a.out 

Open:
file_name: /dev/input/event0
read name: Power Button

Open:
file_name: dev/input/event1
read name: AT Translated Set 2 keyboard

Open:
file_name: /dev/input/event2
read name: VMware VMware Virtual USB Mouse

Open:
file_name: dev/input/event3
read name: ImPS/2 Generic Wheel Mouse

Done.
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/2.input-device-driver$ 

*/
