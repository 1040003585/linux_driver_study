# 1.userspace-select-NONBLOCK.c

build ok :
```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll/Character-devices_wq_poll.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll/Character-devices_wq_poll.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll/Character-devices_wq_poll.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo insmod Character-devices_wq_poll.ko 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ cat /proc/devices |grep gl
250 character_devices_wq_poll-globalfifo_name2_n
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo mknod /dev/globalfifo c 250 0
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ls /dev/globalfifo -l
crw-r--r-- 1 root root 250, 0 May 25 15:25 /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 

```

1. first, Poll monitor: only can be written
```
^Cwu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ gcc 1.userspace-select-NONBLOCK.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
...
```

2. write some data to /dev/globalfifo: 
```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hello wu 250' > /dev/globalfifo"

```

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be read.
...
```

3. written full outof GLOBALFIFO_SIZE:
```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ cat /dev/globalfifo &
[1] 14199
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hello wu 25011' > /dev/globalfifo"
hello wu 25011
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hello wu 25011222' > /dev/globalfifo"
hello wu 25011222
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ kill 14199
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
[1]+  Terminated              cat /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hello wu 25011222333' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hello wu 2501122233344444444 ' > /dev/globalfifo"
^[[A^[[B^C
```
pending write, and Poll monitor: can be read.

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.

```

add sleep(1) for test:
```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ man sleep
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ gcc 1.userspace-select-NONBLOCK.c 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./A
bash: ./A: No such file or directory
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[sudo] password for wu-being: 
Sorry, try again.
[sudo] password for wu-being: 
[63369.065869] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63369.065884] [character_devices_wq_poll] [globalfifo_ioctl] ioctl CLEAR.
[63369.065886] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63370.066358] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63371.066946] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63372.067394] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63373.067955] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63373.070796] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 


```


log:

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[63741.596291] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63741.596295] [character_devices_wq_poll] [globalfifo_ioctl] ioctl CLEAR.
[63741.596297] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63742.597051] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63743.597570] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63744.598090] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63744.619219] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel ' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[63794.640801] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63794.640808] [character_devices_wq_poll] [globalfifo_write] count: 5. start.
[63794.640809] [character_devices_wq_poll] [globalfifo_write] written 5 bytes, current_len: 5.
[63794.640810] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[63794.640810] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[63794.640812] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be written.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[63802.622604] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63802.622608] [character_devices_wq_poll] [globalfifo_ioctl] ioctl CLEAR.
[63802.622610] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.
[63802.622611] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63803.623273] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.
[63803.623276] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63804.461878] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel22222 ' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel2222233333 ' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel22222333334444 ' > /dev/globalfifo" 
^Cwu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Pollsudo dmesg -c|grep character_devices
[63833.971556] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63833.971564] [character_devices_wq_poll] [globalfifo_write] count: 10. start.
[63833.971565] [character_devices_wq_poll] [globalfifo_write] written 10 bytes, current_len: 15.
[63833.971566] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[63833.971566] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[63833.971568] [character_devices_wq_poll] [globalfifo_release] release.
[63837.346568] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63837.346575] [character_devices_wq_poll] [globalfifo_write] count: 15. start.
[63837.346576] [character_devices_wq_poll] [globalfifo_write] written 15 bytes, current_len: 30.
[63837.346577] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[63837.346577] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[63837.346578] [character_devices_wq_poll] [globalfifo_release] release.
[63840.819417] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63840.819424] [character_devices_wq_poll] [globalfifo_write] count: 19. start.
[63840.819425] [character_devices_wq_poll] [globalfifo_write] written 2 bytes, current_len: 32.
[63840.819426] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[63840.819426] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[63840.819427] [character_devices_wq_poll] [globalfifo_write] count: 17. start.
[63840.819428] [character_devices_wq_poll] [globalfifo_write] schedule before.
[63849.078145] [character_devices_wq_poll] [globalfifo_write] schedule after.
[63849.078148] [character_devices_wq_poll] [globalfifo_write] signal_pending before.
[63849.078149] [character_devices_wq_poll] [globalfifo_write] signal_pending.
[63849.078214] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.
[userspace-select] Poll monitor: can be read.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[63858.362516] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63858.362520] [character_devices_wq_poll] [globalfifo_ioctl] ioctl CLEAR.
[63858.362523] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.
[63859.363071] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.
[63860.363962] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.
[63861.364532] [character_devices_wq_poll] [globalfifo_poll] poll POLLIN | POLLRDNORM.
[63861.650459] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ cat /dev/globalfifo &
[1] 14432
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[63892.016217] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63892.016227] [character_devices_wq_poll] [globalfifo_read] count: 65536. start.
[63892.016230] [character_devices_wq_poll] [globalfifo_read] read 32 bytes, current_len: 0.
[63892.016231] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible before.
[63892.016232] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible after.
[63892.016237] [character_devices_wq_poll] [globalfifo_read] count: 65536. start.
[63892.016238] [character_devices_wq_poll] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ ./a.out 
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
[userspace-select] Poll monitor: can be written.
^C
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices
[63900.091058] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63900.091061] [character_devices_wq_poll] [globalfifo_ioctl] ioctl CLEAR.
[63900.091064] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63901.091926] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63902.092405] [character_devices_wq_poll] [globalfifo_poll] poll POLLOUT | POLLWRNORM.
[63902.775001] [character_devices_wq_poll] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo sh -c "echo 'hel22222333334444 ' > /dev/globalfifo"hel22222333334444 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ sudo dmesg -c|grep character_devices[63912.966374] [character_devices_wq_poll] [globalfifo_open] container_of private_data.
[63912.966381] [character_devices_wq_poll] [globalfifo_write] count: 19. start.
[63912.966382] [character_devices_wq_poll] [globalfifo_write] written 19 bytes, current_len: 19.
[63912.966383] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible before.
[63912.966393] [character_devices_wq_poll] [globalfifo_write] wake_up_interruptible after.
[63912.966395] [character_devices_wq_poll] [globalfifo_release] release.
[63912.966407] [character_devices_wq_poll] [globalfifo_read] schedule after.
[63912.966408] [character_devices_wq_poll] [globalfifo_read] signal_pending before.
[63912.966409] [character_devices_wq_poll] [globalfifo_read] signal_pending after.
[63912.966411] [character_devices_wq_poll] [globalfifo_read] read 19 bytes, current_len: 0.
[63912.966411] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible before.
[63912.966412] [character_devices_wq_poll] [globalfifo_read] wake_up_interruptible after.
[63912.966420] [character_devices_wq_poll] [globalfifo_read] count: 65536. start.
[63912.966421] [character_devices_wq_poll] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 

```

not FIFO_CLEAR
```c
//#define FIFO_CLEAR 0x1
#define FIFO_CLEAR 0x0

	if (ioctl(fd, FIFO_CLEAR, 0) < 0 )
		printf(TAG "Ioctl fail.\n");
```

test:
```
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

```
pending writen. cat /dev/globalfifo:

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ cat /dev/globalfifo 
hel22222 
hel22222 3333
hel22222 3333 444444444

```

```
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

```

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/2.Poll$ cat /dev/globalfifo 
hel22222 
hel22222 3333
hel22222 3333 444444444
hel22222 3333

```

# 2.userspace-poll-NONBLOCK.c

test 1

```
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

```

test 2

```
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

```
