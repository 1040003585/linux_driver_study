
build ok:

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue/Character-devices_wq.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue/Character-devices_wq.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue/Character-devices_wq.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

```


1. read thread:

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo insmod Character-devices_wq.ko 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ cat /proc/devices |grep char
250 character_devices_wq-globalfifo_name2_n
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo mknod /dev/globalfifo c 250 0
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ls /dev/globalfifo -l
crw-r--r-- 1 root root 250, 0 May 25 00:26 /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[ 8531.959974] [character_devices_wq] character_devices_wq_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ cat /dev/globalfifo
hello wu 250

```
read thread log:

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[sudo] password for wu-being: 
[ 8672.443663] [character_devices_wq] [globalfifo_open] container_of private_data.
[ 8672.443672] [character_devices_wq] [globalfifo_read] count: 65536. start.
[ 8672.443673] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

```


2. write thread and log:

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo sh -c "echo 'hello wu 250' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[ 8747.971540] [character_devices_wq] [globalfifo_open] container_of private_data.
[ 8747.971548] [character_devices_wq] [globalfifo_write] count: 13. start.
[ 8747.971549] [character_devices_wq] [globalfifo_write] written 13 bytes, current_len: 13.
[ 8747.971550] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[ 8747.971560] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[ 8747.971562] [character_devices_wq] [globalfifo_release] release.
[ 8747.972582] [character_devices_wq] [globalfifo_read] schedule after.
[ 8747.972584] [character_devices_wq] [globalfifo_read] signal_pending before.
[ 8747.972585] [character_devices_wq] [globalfifo_read] signal_pending after.
[ 8747.972589] [character_devices_wq] [globalfifo_read] read 13 bytes, current_len: 0.
[ 8747.972590] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[ 8747.972590] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[ 8747.972601] [character_devices_wq] [globalfifo_read] count: 65536. start.
[ 8747.972602] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

```


3. background read and write thread and log:

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ cat /dev/globalfifo &
[1] 9261
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[ 8866.365249] [character_devices_wq] [globalfifo_open] container_of private_data.
[ 8866.365261] [character_devices_wq] [globalfifo_read] count: 65536. start.
[ 8866.365262] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ cat /dev/globalfifo &
[2] 9265
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[ 8878.576527] [character_devices_wq] [globalfifo_open] container_of private_data.
[ 8878.576534] [character_devices_wq] [globalfifo_read] count: 65536. start.
[ 8878.576535] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo sh -c "echo 'hello wu 250 to all' > /dev/globalfifo"
hello wu 250 to all
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[ 8896.250341] [character_devices_wq] [globalfifo_open] container_of private_data.
[ 8896.250348] [character_devices_wq] [globalfifo_write] count: 20. start.
[ 8896.250349] [character_devices_wq] [globalfifo_write] written 20 bytes, current_len: 20.
[ 8896.250350] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[ 8896.250368] [character_devices_wq] [globalfifo_read] schedule after.
[ 8896.250370] [character_devices_wq] [globalfifo_read] signal_pending before.
[ 8896.250371] [character_devices_wq] [globalfifo_read] signal_pending after.
[ 8896.250376] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[ 8896.250378] [character_devices_wq] [globalfifo_release] release.
[ 8896.250379] [character_devices_wq] [globalfifo_read] read 20 bytes, current_len: 0.
[ 8896.250380] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[ 8896.250380] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[ 8896.250394] [character_devices_wq] [globalfifo_read] schedule after.
[ 8896.250395] [character_devices_wq] [globalfifo_read] count: 65536. start.
[ 8896.250395] [character_devices_wq] [globalfifo_read] schedule before.
[ 8896.250398] [character_devices_wq] [globalfifo_read] signal_pending before.
[ 8896.250399] [character_devices_wq] [globalfifo_read] signal_pending after.
[ 8896.250399] [character_devices_wq] [globalfifo_read] schedule after.
[ 8896.250400] [character_devices_wq] [globalfifo_read] signal_pending before.
[ 8896.250401] [character_devices_wq] [globalfifo_read] signal_pending after.
[ 8896.250401] [character_devices_wq] [globalfifo_read] schedule before.
[ 8896.250403] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

```


kill all read cat thread:

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps 
  PID TTY          TIME CMD
 9275 pts/11   00:00:00 bash
 9287 pts/11   00:00:00 cat
 9379 pts/11   00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps |grep 9287
 9287 pts/11   00:00:00 cat
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps |grep 9365
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps -A|grep 9365
 9365 pts/3    00:00:00 cat
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ kill 9287
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps |grep 9287
[1]+  Terminated              cat /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps 
  PID TTY          TIME CMD
 9275 pts/11   00:00:00 bash
 9393 pts/11   00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps |grep 9287
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
```
```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 6032 pts/4    00:00:00 bash
 9261 pts/4    00:00:00 cat
 9265 pts/4    00:00:00 cat
 9390 pts/4    00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ kill 9261
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ kill 9265
[1]-  Terminated              cat /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 6032 pts/4    00:00:00 bash
 9400 pts/4    00:00:00 ps
[2]+  Terminated              cat /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 6032 pts/4    00:00:00 bash
 9401 pts/4    00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
```
```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ PS
PS: command not found
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 3845 pts/3    00:00:00 bash
 9365 pts/3    00:00:00 cat
 9389 pts/3    00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ kill 9365
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 3845 pts/3    00:00:00 bash
 9396 pts/3    00:00:00 ps
[1]+  Terminated              cat /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 3845 pts/3    00:00:00 bash
 9397 pts/3    00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 3845 pts/3    00:00:00 bash
 9398 pts/3    00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

```

retest, first write than read :

```
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo sh -c "echo 'hello wu25033333333333333' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[10786.809896] [character_devices_wq] [globalfifo_open] container_of private_data.
[10786.809903] [character_devices_wq] [globalfifo_write] count: 26. start.
[10786.809904] [character_devices_wq] [globalfifo_write] written 26 bytes, current_len: 26.
[10786.809905] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[10786.809905] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[10786.809906] [character_devices_wq] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ cat /dev/globalfifo &
[1] 9439
hello wu25033333333333333
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[10795.357704] [character_devices_wq] [globalfifo_open] container_of private_data.
[10795.357712] [character_devices_wq] [globalfifo_read] count: 65536. start.
[10795.357715] [character_devices_wq] [globalfifo_read] read 26 bytes, current_len: 0.
[10795.357716] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[10795.357716] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[10795.357719] [character_devices_wq] [globalfifo_read] count: 65536. start.
[10795.357720] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo sh -c "echo 'hello wu, niubi honghong haha' > /dev/globalfifo"
hello wu, niubi honghong haha
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[10804.579582] [character_devices_wq] [globalfifo_open] container_of private_data.
[10804.579589] [character_devices_wq] [globalfifo_write] count: 30. start.
[10804.579591] [character_devices_wq] [globalfifo_write] written 30 bytes, current_len: 30.
[10804.579591] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[10804.579601] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[10804.579602] [character_devices_wq] [globalfifo_release] release.
[10804.579615] [character_devices_wq] [globalfifo_read] schedule after.
[10804.579617] [character_devices_wq] [globalfifo_read] signal_pending before.
[10804.579618] [character_devices_wq] [globalfifo_read] signal_pending after.
[10804.579619] [character_devices_wq] [globalfifo_read] read 30 bytes, current_len: 0.
[10804.579620] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[10804.579620] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[10804.579628] [character_devices_wq] [globalfifo_read] count: 65536. start.
[10804.579629] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

```

write double at start, current_len will add again until read to clear current_len: 

```

wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo sh -c "echo 'aa' > /dev/globalfifo"
aa
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[11162.049283] [character_devices_wq] [globalfifo_open] container_of private_data.
[11162.049290] [character_devices_wq] [globalfifo_write] count: 3. start.
[11162.049292] [character_devices_wq] [globalfifo_write] written 3 bytes, current_len: 3.
[11162.049292] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[11162.049301] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[11162.049303] [character_devices_wq] [globalfifo_release] release.
[11162.049332] [character_devices_wq] [globalfifo_read] schedule after.
[11162.049334] [character_devices_wq] [globalfifo_read] signal_pending before.
[11162.049335] [character_devices_wq] [globalfifo_read] signal_pending after.
[11162.049336] [character_devices_wq] [globalfifo_read] read 3 bytes, current_len: 0.
[11162.049337] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[11162.049338] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[11162.049349] [character_devices_wq] [globalfifo_read] count: 65536. start.
[11162.049349] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo sh -c "echo 'aabbbb' > /dev/globalfifo"
aabbbb
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[11177.183316] [character_devices_wq] [globalfifo_open] container_of private_data.
[11177.183325] [character_devices_wq] [globalfifo_write] count: 7. start.
[11177.183326] [character_devices_wq] [globalfifo_write] written 7 bytes, current_len: 7.
[11177.183328] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[11177.183338] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[11177.183340] [character_devices_wq] [globalfifo_release] release.
[11177.183353] [character_devices_wq] [globalfifo_read] schedule after.
[11177.183355] [character_devices_wq] [globalfifo_read] signal_pending before.
[11177.183356] [character_devices_wq] [globalfifo_read] signal_pending after.
[11177.183357] [character_devices_wq] [globalfifo_read] read 7 bytes, current_len: 0.
[11177.183358] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[11177.183359] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[11177.183373] [character_devices_wq] [globalfifo_read] count: 65536. start.
[11177.183374] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 3845 pts/3    00:00:00 bash
 9439 pts/3    00:00:00 cat
 9462 pts/3    00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ kill 9439
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ kill 9439
bash: kill: (9439) - No such process
[1]+  Terminated              cat /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ ps
  PID TTY          TIME CMD
 3845 pts/3    00:00:00 bash
 9463 pts/3    00:00:00 ps
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[11214.256811] [character_devices_wq] [globalfifo_read] schedule after.
[11214.256813] [character_devices_wq] [globalfifo_read] signal_pending before.
[11214.256820] [character_devices_wq] [globalfifo_read] signal_pending.
[11214.256879] [character_devices_wq] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo sh -c "echo 'aa' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[11225.795209] [character_devices_wq] [globalfifo_open] container_of private_data.
[11225.795216] [character_devices_wq] [globalfifo_write] count: 3. start.
[11225.795217] [character_devices_wq] [globalfifo_write] written 3 bytes, current_len: 3.
[11225.795218] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[11225.795218] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[11225.795219] [character_devices_wq] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo sh -c "echo 'aabbbb' > /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[11232.195545] [character_devices_wq] [globalfifo_open] container_of private_data.
[11232.195552] [character_devices_wq] [globalfifo_write] count: 7. start.
[11232.195553] [character_devices_wq] [globalfifo_write] written 7 bytes, current_len: 10.
[11232.195554] [character_devices_wq] [globalfifo_write] wake_up_interruptible before.
[11232.195554] [character_devices_wq] [globalfifo_write] wake_up_interruptible after.
[11232.195556] [character_devices_wq] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ cat /dev/globalfifo &
[1] 9477
aa
aabbbb
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ sudo dmesg -c|grep character_devices
[11250.808577] [character_devices_wq] [globalfifo_open] container_of private_data.
[11250.808585] [character_devices_wq] [globalfifo_read] count: 65536. start.
[11250.808587] [character_devices_wq] [globalfifo_read] read 10 bytes, current_len: 0.
[11250.808588] [character_devices_wq] [globalfifo_read] wake_up_interruptible before.
[11250.808589] [character_devices_wq] [globalfifo_read] wake_up_interruptible after.
[11250.808591] [character_devices_wq] [globalfifo_read] count: 65536. start.
[11250.808592] [character_devices_wq] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 
wu-being@ubuntu:~/code/linux_driver_study/song08--Block_NONBLOCK/1.Wait-Queue$ 

```

