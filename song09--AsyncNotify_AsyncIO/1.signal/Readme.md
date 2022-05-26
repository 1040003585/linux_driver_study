
Cant not Sent signal !

```c

static int globalfifo_fasync(int fd, struct file *filp, int mode) //**
{
	struct globalfifo_dev *dev = filp->private_data;

	printk(mode ? TAG "[%s] add.\n": TAG "[%s] remove.\n", __func__);
	fasync_helper(fd, filp, mode, &dev->async_queue);

	return 0;
}

static int globalfifo_release(struct inode *inode, struct file *filp)
{
	printk(TAG "[%s] release.\n", __func__);
	globalfifo_fasync(-1, filp, 0); //mode:0-> remove FASYNC from f_flags, 1 is add it.

	return 0;
}
static struct file_operations globalfifo_fops = {
	.owner = THIS_MODULE,
	.open = globalfifo_open,
	.read = globalfifo_read,
	.write = globalfifo_write,
	.release = globalfifo_release,
	//.poll = globalfifo_poll, /**/
	.llseek = globalfifo_llseek,
	.unlocked_ioctl = globalfifo_ioctl,

};
```

```
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  Building modules, stage 2.
  MODPOST 1 modules
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 

insmod ...
mknod ...
...


wu-being@ubuntu:~$ cd code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal/
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ ls
1.globalfifo_test.c            Character-devices_wq_signal.ko     Character-devices_wq_signal.o  Module.symvers
a.out                          Character-devices_wq_signal.mod.c  Makefile                       Readme.md
Character-devices_wq_signal.c  Character-devices_wq_signal.mod.o  modules.order
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ cat /proc/devices |grep char
250 character_devices_wq_signal-globalfifo_name2_n
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ ls /dev/globalfifo  -l
crw-r--r-- 1 root root 250, 0 May 26 14:16 /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ gcc 1.globalfifo_test.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo ./a.out &
[1] 4618
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[ 2251.111389] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo '123'> /dev/globalfifo"
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[ 2307.890107] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[ 2307.890115] [character_devices_wq_signal] [globalfifo_write] count: 4. start.
[ 2307.890116] [character_devices_wq_signal] [globalfifo_write] written 4 bytes, current_len: 4.
[ 2307.890116] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible before.
[ 2307.890117] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible after.
[ 2307.890118] [character_devices_wq_signal] [globalfifo_release] release.
[ 2307.890118] [character_devices_wq_signal] [globalfifo_fasync] remove.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ cat /dev/globalfifo &
[2] 4628
123
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[ 2340.689569] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[ 2340.689578] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[ 2340.689580] [character_devices_wq_signal] [globalfifo_read] read 4 bytes, current_len: 0.
[ 2340.689581] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible before.
[ 2340.689581] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible after.
[ 2340.689584] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[ 2340.689585] [character_devices_wq_signal] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo 'aaaaa123'> /dev/globalfifo"
aaaaa123
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[ 2376.072448] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[ 2376.072457] [character_devices_wq_signal] [globalfifo_write] count: 9. start.
[ 2376.072458] [character_devices_wq_signal] [globalfifo_write] written 9 bytes, current_len: 9.
[ 2376.072459] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible before.
[ 2376.072469] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible after.
[ 2376.072473] [character_devices_wq_signal] [globalfifo_release] release.
[ 2376.072473] [character_devices_wq_signal] [globalfifo_fasync] remove.
[ 2376.072498] [character_devices_wq_signal] [globalfifo_read] schedule after.
[ 2376.072500] [character_devices_wq_signal] [globalfifo_read] signal_pending before.
[ 2376.072501] [character_devices_wq_signal] [globalfifo_read] signal_pending after.
[ 2376.072502] [character_devices_wq_signal] [globalfifo_read] read 9 bytes, current_len: 0.
[ 2376.072503] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible before.
[ 2376.072503] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible after.
[ 2376.072511] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[ 2376.072512] [character_devices_wq_signal] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ cat /dev/globalfifo 
^C
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[ 2494.800349] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[ 2494.800358] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[ 2494.800359] [character_devices_wq_signal] [globalfifo_read] schedule before.
[ 2497.810107] [character_devices_wq_signal] [globalfifo_read] schedule after.
[ 2497.810111] [character_devices_wq_signal] [globalfifo_read] signal_pending before.
[ 2497.810112] [character_devices_wq_signal] [globalfifo_read] signal_pending.
[ 2497.810188] [character_devices_wq_signal] [globalfifo_release] release.
[ 2497.810189] [character_devices_wq_signal] [globalfifo_fasync] remove.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 

```

add .fasync, ok Sent signal

```c

static int globalfifo_fasync(int fd, struct file *filp, int mode) //**
{
	struct globalfifo_dev *dev = filp->private_data;

	printk(mode ? TAG "[%s] add.\n": TAG "[%s] remove.\n", __func__);
	fasync_helper(fd, filp, mode, &dev->async_queue);

	return 0;
}

static int globalfifo_release(struct inode *inode, struct file *filp)
{
	printk(TAG "[%s] release.\n", __func__);
	//globalfifo_fasync(-1, filp, 0); //mode:0-> remove FASYNC from f_flags, 1 is add it.

	return 0;
}

static struct file_operations globalfifo_fops = {
	.owner = THIS_MODULE,
	.open = globalfifo_open,
	.read = globalfifo_read,
	.write = globalfifo_write,
	.release = globalfifo_release,
	//.poll = globalfifo_poll, /**/
	.llseek = globalfifo_llseek,
	.unlocked_ioctl = globalfifo_ioctl,
	.fasync = globalfifo_fasync, //**

};
```
log: 
```
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  Building modules, stage 2.
  MODPOST 1 modules
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo insmod Character-devices_wq_signal.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ cat /proc/devices |grep char
250 character_devices_wq_signal-globalfifo_name2_n
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo mknod /dev/globalfifo c 250 0
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ ls /dev/golbalfifo -l
crw-r--r-- 1 root root 250, 0 May 26 17:04 /dev/globalfifo
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[   58.465515] [character_devices_wq_signal] character_devices_wq_signal_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ gcc 1.globalfifo_test.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo ./a.out &
[3] 3429
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo 123 > /dev/globalfifo"
Have caught a signal from globalfifo, sig N.O. 29
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[  210.001809] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  210.001814] [character_devices_wq_signal] [globalfifo_fasync] add.
[  227.681381] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  227.681389] [character_devices_wq_signal] [globalfifo_write] count: 4. start.
[  227.681391] [character_devices_wq_signal] [globalfifo_write] written 4 bytes, current_len: 4.
[  227.681391] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible before.
[  227.681392] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible after.
[  227.681407] [character_devices_wq_signal] [globalfifo_write] Sent kill SIGIO ... ...
[  227.681410] [character_devices_wq_signal] [globalfifo_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ cat /dev/globalfifo &
[4] 3446
123
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char
[  260.967238] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  260.967247] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[  260.967250] [character_devices_wq_signal] [globalfifo_read] read 4 bytes, current_len: 0.
[  260.967251] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible before.
[  260.967252] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible after.
[  260.967255] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[  260.967255] [character_devices_wq_signal] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo 123aaa > /dev/globalfifo" 
123aaa
Have caught a signal from globalfifo, sig N.O. 29
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c |grep char[  334.439273] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  334.439280] [character_devices_wq_signal] [globalfifo_write] count: 7. start.
[  334.439281] [character_devices_wq_signal] [globalfifo_write] written 7 bytes, current_len: 7.
[  334.439282] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible before.
[  334.439292] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible after.
[  334.439302] [character_devices_wq_signal] [globalfifo_write] Sent kill SIGIO ... ...
[  334.439304] [character_devices_wq_signal] [globalfifo_read] schedule after.
[  334.439304] [character_devices_wq_signal] [globalfifo_release] release.
[  334.439307] [character_devices_wq_signal] [globalfifo_read] signal_pending before.
[  334.439308] [character_devices_wq_signal] [globalfifo_read] signal_pending after.
[  334.439309] [character_devices_wq_signal] [globalfifo_read] read 7 bytes, current_len: 0.
[  334.439310] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible before.
[  334.439310] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible after.
[  334.439318] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[  334.439319] [character_devices_wq_signal] [globalfifo_read] schedule before.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 

```


version ok:

```c

static int globalfifo_fasync(int fd, struct file *filp, int mode) //**
{
	struct globalfifo_dev *dev = filp->private_data;

	printk(mode ? TAG "[%s] add.\n": TAG "[%s] remove.\n", __func__);
	fasync_helper(fd, filp, mode, &dev->async_queue);

	return 0;
}

static int globalfifo_release(struct inode *inode, struct file *filp)
{
	printk(TAG "[%s] release.\n", __func__);
	globalfifo_fasync(-1, filp, 0); //mode:0-> remove FASYNC from f_flags, 1 is add it.

	return 0;
}

static struct file_operations globalfifo_fops = {
	.owner = THIS_MODULE,
	.open = globalfifo_open,
	.read = globalfifo_read,
	.write = globalfifo_write,
	.release = globalfifo_release,
	.poll = globalfifo_poll, /**/
	.llseek = globalfifo_llseek,
	.unlocked_ioctl = globalfifo_ioctl,
	.fasync = globalfifo_fasync, //**

};
```

```
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo mknod /dev/globalfifo c 250 0
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg |grep char
[  111.268341] [character_devices_wq_signal] character_devices_wq_signal_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ gcc 1.globalfifo_test.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ ./a.out &
[1] 3659
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ Open fail, fd: -1
^C
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo ./a.out &
[2] 3660
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c|grep char
[  111.268341] [character_devices_wq_signal] character_devices_wq_signal_init sucess
[  179.834312] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  179.834317] [character_devices_wq_signal] [globalfifo_fasync] add.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo 123 > /dev/globalfifo"
Have caught a signal from globalfifo, sig N.O. 29
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c|grep char
[  246.880734] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  246.880743] [character_devices_wq_signal] [globalfifo_write] count: 4. start.
[  246.880744] [character_devices_wq_signal] [globalfifo_write] written 4 bytes, current_len: 4.
[  246.880745] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible before.
[  246.880745] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible after.
[  246.880756] [character_devices_wq_signal] [globalfifo_write] Sent kill SIGIO ... ...
[  246.880758] [character_devices_wq_signal] [globalfifo_release] release.
[  246.880759] [character_devices_wq_signal] [globalfifo_fasync] remove.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo 123aa > /dev/globalfifo"
Have caught a signal from globalfifo, sig N.O. 29
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c|grep char
[  275.730097] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  275.730104] [character_devices_wq_signal] [globalfifo_write] count: 6. start.
[  275.730106] [character_devices_wq_signal] [globalfifo_write] written 6 bytes, current_len: 10.
[  275.730106] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible before.
[  275.730107] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible after.
[  275.730118] [character_devices_wq_signal] [globalfifo_write] Sent kill SIGIO ... ...
[  275.730119] [character_devices_wq_signal] [globalfifo_release] release.
[  275.730120] [character_devices_wq_signal] [globalfifo_fasync] remove.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ cat /dev/globalfifo &
[3] 3687
123
123aa
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c|grep char
[  300.848793] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  300.848802] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[  300.848805] [character_devices_wq_signal] [globalfifo_read] read 10 bytes, current_len: 0.
[  300.848806] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible before.
[  300.848806] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible after.
[  300.848809] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[  300.848809] [character_devices_wq_signal] [globalfifo_read] schedule before.

```



add 1.globalfifo_test.c log:

```
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ gcc 1.globalfifo_test.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo ./a.out &
[4] 3747
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ [userspace-signal] 1. set fd owner
[userspace-signal] 2. change to FASYNC
[userspace-signal] 3. add singnal function
[userspace-signal] while.
^C
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ gcc 1.globalfifo_test.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo ./a.out &
[5] 3757
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ [userspace-signal] 
1. set fd owner
[userspace-signal] 2. change to FASYNC
[userspace-signal] 3. add singnal function
[userspace-signal] while.
^C
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ gcc 1.globalfifo_test.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo ./a.out &
[6] 3765
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ [userspace-signal] 1. set fd owner
[userspace-signal] 2. change to FASYNC
[userspace-signal] 3. add singnal function
[userspace-signal] while.

wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c|grep char
[  683.504770] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  683.504804] [character_devices_wq_signal] [globalfifo_fasync] add.
[  711.658417] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  711.658453] [character_devices_wq_signal] [globalfifo_fasync] add.
[  731.560147] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  731.560181] [character_devices_wq_signal] [globalfifo_fasync] add.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo 123aa > /dev/globalfifo"
123aa
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
Have caught a signal from globalfifo, sig N.O. 29
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c|grep char
[  770.970863] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  770.970871] [character_devices_wq_signal] [globalfifo_write] count: 6. start.
[  770.970872] [character_devices_wq_signal] [globalfifo_write] written 6 bytes, current_len: 6.
[  770.970872] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible before.
[  770.970883] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible after.
[  770.970895] [character_devices_wq_signal] [globalfifo_read] schedule after.
[  770.970897] [character_devices_wq_signal] [globalfifo_read] signal_pending before.
[  770.970898] [character_devices_wq_signal] [globalfifo_read] signal_pending after.
[  770.970904] [character_devices_wq_signal] [globalfifo_write] Sent kill SIGIO ... ...
[  770.970906] [character_devices_wq_signal] [globalfifo_read] read 6 bytes, current_len: 0.
[  770.970907] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible before.
[  770.970907] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible after.
[  770.970919] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[  770.970919] [character_devices_wq_signal] [globalfifo_read] schedule before.
[  770.970926] [character_devices_wq_signal] [globalfifo_release] release.
[  770.970927] [character_devices_wq_signal] [globalfifo_fasync] remove.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
```
```
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ gcc 1.globalfifo_test.c 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo ./a.out &
[7] 3785
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
[userspace-signal] 3. add singnal function
[userspace-signal] 1. set fd owner
[userspace-signal] 2. change to FASYNC
[userspace-signal] while.

wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo 123a4444 > /dev/globalfifo"
123a4444
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
[userspace-signal] 312.Have caught a signal from globalfifo, sig N.O. 29
Have caught a signal from globalfifo, sig N.O. 29
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo dmesg -c|grep char
[  824.082820] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  824.082874] [character_devices_wq_signal] [globalfifo_fasync] add.
[  837.549963] [character_devices_wq_signal] [globalfifo_open] container_of private_data.
[  837.549971] [character_devices_wq_signal] [globalfifo_write] count: 9. start.
[  837.549972] [character_devices_wq_signal] [globalfifo_write] written 9 bytes, current_len: 9.
[  837.549972] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible before.
[  837.549982] [character_devices_wq_signal] [globalfifo_write] wake_up_interruptible after.
[  837.549995] [character_devices_wq_signal] [globalfifo_read] schedule after.
[  837.549997] [character_devices_wq_signal] [globalfifo_read] signal_pending before.
[  837.549998] [character_devices_wq_signal] [globalfifo_read] signal_pending after.
[  837.550006] [character_devices_wq_signal] [globalfifo_write] Sent kill SIGIO ... ...
[  837.550007] [character_devices_wq_signal] [globalfifo_read] read 9 bytes, current_len: 0.
[  837.550008] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible before.
[  837.550009] [character_devices_wq_signal] [globalfifo_read] wake_up_interruptible after.
[  837.550016] [character_devices_wq_signal] [globalfifo_read] count: 65536. start.
[  837.550017] [character_devices_wq_signal] [globalfifo_read] schedule before.
[  837.550021] [character_devices_wq_signal] [globalfifo_release] release.
[  837.550022] [character_devices_wq_signal] [globalfifo_fasync] remove.
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ sudo sh -c "echo 123a4444 > /dev/globalfifo"
[userspace-signal] 312.Have caught a signal from globalfifo, sig N.O. 29
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
123a4444
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
[userspace-signal] 123.Have caught a signal from globalfifo, sig N.O. 29
Have caught a signal from globalfifo, sig N.O. 29
wu-being@ubuntu:~/code/linux_driver_study/song09--AsyncNotify_AsyncIO/1.signal$ 

```
