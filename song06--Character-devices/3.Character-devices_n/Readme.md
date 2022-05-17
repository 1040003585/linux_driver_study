
without container_of:

```c
static int globalmem_open(struct inode *inode, struct file *filp)
{
    struct globalmem_dev *dev = container_of(inode->i_cdev, struct globalmem_dev, cdev);
    filp->private_data = dev;
    return 0;
}

```

log:
```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  LD      /home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/built-in.o
  CC [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/Character-devices_n.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/Character-devices_n.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/Character-devices_n.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo dmesg -c|grep character_devices
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo insmod Character-devices_n.ko wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ lsmod |grep Char
Character_devices_n    12900  0 
Character_devices      12900  0 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /proc/devices |grep global
249 globalmem_name2_n
250 globalmem_name2
251 globalmem
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ ls /dev -l |grep global
crw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0
brw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0-b
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
crw-r--r--  1 root root    250,   2 May 18 00:47 globaltest250-2
crw-r--r--  1 root root    555,   1 May 18 00:49 globaltest555_1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo mknod /dev/globaltest_n249_0 c 249 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo mknod /dev/globaltest_n249_1 c 249 1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo mknod /dev/globaltest_n249_2 c 249 2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ ls /dev -l |grep global
crw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0
brw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0-b
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
crw-r--r--  1 root root    250,   2 May 18 00:47 globaltest250-2
crw-r--r--  1 root root    555,   1 May 18 00:49 globaltest555_1
crw-r--r--  1 root root    249,   0 May 18 01:46 globaltest_n249_0
crw-r--r--  1 root root    249,   1 May 18 01:46 globaltest_n249_1
crw-r--r--  1 root root    249,   2 May 18 01:46 globaltest_n249_2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo sh -c "echo 'hello wu 249 0' > /dev/globaltest_n249_0"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo sh -c "echo 'hello wu 249 1' > /dev/globaltest_n249_1"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo sh -c "echo 'hello wu 249 2' > /dev/globaltest_n249_2"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /dev/globaltest_n249_0
hello wu 249 2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /dev/globaltest_n249_1
hello wu 249 2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /dev/globaltest_n249_2
hello wu 249 2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo dmesg -c|grep character_devices
[15421.874733] [character_devices] character_devices_init sucess
[15631.136133] [character_devices] [globalmem_open] init flip private_data.
[15631.136143] [character_devices] [globalmem_write] written count: 15, p:0.
[15631.136145] [character_devices] [globalmem_write] written 15 bytes from 0.
[15631.136146] [character_devices] [globalmem_release] release.
[15639.162248] [character_devices] [globalmem_open] init flip private_data.
[15639.162257] [character_devices] [globalmem_write] written count: 15, p:0.
[15639.162258] [character_devices] [globalmem_write] written 15 bytes from 0.
[15639.162260] [character_devices] [globalmem_release] release.
[15644.604646] [character_devices] [globalmem_open] init flip private_data.
[15644.604656] [character_devices] [globalmem_write] written count: 15, p:0.
[15644.604657] [character_devices] [globalmem_write] written 15 bytes from 0.
[15644.604659] [character_devices] [globalmem_release] release.
[15657.324718] [character_devices] [globalmem_open] init flip private_data.
[15657.324730] [character_devices] [globalmem_read] read count: 65536, p:0.
[15657.324733] [character_devices] [globalmem_read] read 4096 bytes from 0.
[15657.324747] [character_devices] [globalmem_read] read count: 65536, p:4096.
[15657.324750] [character_devices] [globalmem_release] release.
[15665.738954] [character_devices] [globalmem_open] init flip private_data.
[15665.738966] [character_devices] [globalmem_read] read count: 65536, p:0.
[15665.738969] [character_devices] [globalmem_read] read 4096 bytes from 0.
[15665.738983] [character_devices] [globalmem_read] read count: 65536, p:4096.
[15665.738986] [character_devices] [globalmem_release] release.
[15668.421897] [character_devices] [globalmem_open] init flip private_data.
[15668.421908] [character_devices] [globalmem_read] read count: 65536, p:0.
[15668.421911] [character_devices] [globalmem_read] read 4096 bytes from 0.
[15668.421928] [character_devices] [globalmem_read] read count: 65536, p:4096.
[15668.421932] [character_devices] [globalmem_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 

```


with container_of:

```c
static int globalmem_open(struct inode *inode, struct file *filp)
{
    struct globalmem_dev *dev = container_of(inode->i_cdev, struct globalmem_dev, cdev);
    filp->private_data = dev;
    return 0;
}

```

log:
```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/Character-devices_n.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/Character-devices_n.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/3.Character-devices_n/Character-devices_n.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo rmmod Character_devices_n 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo insmod Character-devices_n.ko 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ lsmod |grep Char
Character_devices_n    12900  0 
Character_devices      12900  0 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ ls /dev -l |grep global
crw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0
brw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0-b
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
crw-r--r--  1 root root    250,   2 May 18 00:47 globaltest250-2
crw-r--r--  1 root root    555,   1 May 18 00:49 globaltest555_1
crw-r--r--  1 root root    249,   0 May 18 01:46 globaltest_n249_0
crw-r--r--  1 root root    249,   1 May 18 01:46 globaltest_n249_1
crw-r--r--  1 root root    249,   2 May 18 01:46 globaltest_n249_2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /proc/devices |grep global 
248 globalmem_name2_n
249 globalmem_name2_n
250 globalmem_name2
251 globalmem
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo mknod /dev/globaltest_n248_0 c 248 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo mknod /dev/globaltest_n248_1 c 248 1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo mknod /dev/globaltest_n248_2 c 248 2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo mknod /dev/globaltest_n249_0 c 249 0
mknod: ‘/dev/globaltest_n249_0’: File exists
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo sh -c "echo 'hello wu 249 0' > /dev/globaltest_n249_0"
sh: 1: cannot create /dev/globaltest_n249_0: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo sh -c "echo 'hello wu 248 0' > /dev/globaltest_n248_0"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo sh -c "echo 'hello wu 248 1' > /dev/globaltest_n248_1"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo sh -c "echo 'hello wu 248 2.' > /dev/globaltest_n248_2"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /dev/globaltest_n249_0
cat: /dev/globaltest_n249_0: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /dev/globaltest_n248_0
hello wu 248 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /dev/globaltest_n248_1
hello wu 248 1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ cat /dev/globaltest_n248_2
hello wu 248 2.
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ sudo dmesg -c|grep character_devices[16081.246788] [character_devices] character_devices_exit sucess
[16093.213490] [character_devices] character_devices_init sucess
[16304.188195] [character_devices] [globalmem_open] container_of private_data.
[16304.188204] [character_devices] [globalmem_write] written count: 15, p:0.
[16304.188206] [character_devices] [globalmem_write] written 15 bytes from 0.
[16304.188208] [character_devices] [globalmem_release] release.
[16312.058517] [character_devices] [globalmem_open] container_of private_data.
[16312.058527] [character_devices] [globalmem_write] written count: 15, p:0.
[16312.058529] [character_devices] [globalmem_write] written 15 bytes from 0.
[16312.058530] [character_devices] [globalmem_release] release.
[16320.166877] [character_devices] [globalmem_open] container_of private_data.
[16320.166888] [character_devices] [globalmem_write] written count: 16, p:0.
[16320.166889] [character_devices] [globalmem_write] written 16 bytes from 0.
[16320.166891] [character_devices] [globalmem_release] release.
[16423.892810] [character_devices] [globalmem_open] container_of private_data.
[16423.892823] [character_devices] [globalmem_read] read count: 65536, p:0.
[16423.892826] [character_devices] [globalmem_read] read 4096 bytes from 0.
[16423.892856] [character_devices] [globalmem_read] read count: 65536, p:4096.
[16423.892860] [character_devices] [globalmem_release] release.
[16425.491272] [character_devices] [globalmem_open] container_of private_data.
[16425.491284] [character_devices] [globalmem_read] read count: 65536, p:0.
[16425.491287] [character_devices] [globalmem_read] read 4096 bytes from 0.
[16425.491301] [character_devices] [globalmem_read] read count: 65536, p:4096.
[16425.491304] [character_devices] [globalmem_release] release.
[16426.375934] [character_devices] [globalmem_open] container_of private_data.
[16426.375946] [character_devices] [globalmem_read] read count: 65536, p:0.
[16426.375949] [character_devices] [globalmem_read] read 4096 bytes from 0.
[16426.375962] [character_devices] [globalmem_read] read count: 65536, p:4096.
[16426.375966] [character_devices] [globalmem_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/3.Character-devices_n$ 


```
