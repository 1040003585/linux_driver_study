
```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  LD      /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/built-in.o
  CC [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices.ko 
insmod: ERROR: could not insert module Character-devices.ko: File exists
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ mv Character-devices.ko Character-devices-2.ko
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices-2.ko 
insmod: ERROR: could not insert module Character-devices-2.ko: File exists
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo rmmod Character_devices 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices-2.ko 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices
[341071.563297] [character_devices_tmp] character_devices_tmp_init sucess
[341761.134411] [character_devices_tmp] character_devices_tmp_exit sucess
[341763.697369] [character_devices] character_devices_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices$ cat /proc/devices 
Character devices:
...
230 globalmem_name1
231 globalmem_name1

```




issue:
```c
	globalmem_devp = kzalloc(sizeof(struct globalmem_dev), GFP_KERNEL);
	if (globalmem_devp) {  // !!!!!!
		ret = -ENOMEM;
		printk(TAG "character_devices_init kzalloc fail: %d.\n", ret);

		goto fail_malloc;
	}
```
will:
```

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices.ko 
insmod: ERROR: could not insert module Character-devices.ko: Cannot allocate memory
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices

May 17 05:45:30 ubuntu kernel: [363538.939931] [character_devices] character_devices_init kzalloc fail: -12.
May 17 05:45:54 ubuntu kernel: [363562.591488] [character_devices] character_devices_init kzalloc fail: -12.
May 17 05:46:36 ubuntu kernel: [363605.235671] [character_devices] character_devices_init kzalloc fail: -12.
```

if:
```c
/*
	globalmem_devp = kzalloc(sizeof(struct globalmem_dev), GFP_KERNEL);
	if (globalmem_devp) {
		ret = -ENOMEM;
		printk(TAG "character_devices_init kzalloc fail: %d.\n", ret);

		goto fail_malloc;
	}
*/
```
will:
```
May 17 05:47:04 ubuntu kernel: [363633.202491] BUG: unable to handle kernel NULL pointer dereference at   (null)
May 17 05:47:04 ubuntu kernel: [363633.202495] IP: [<c117c83c>] cdev_init+0x2c/0x80
May 17 05:47:04 ubuntu kernel: [363633.203722] *pdpt = 000000002622c001 *pde = 0000000000000000 
May 17 05:47:04 ubuntu kernel: [363633.203725] Oops: 0002 [#1] SMP 
May 17 05:47:04 ubuntu kernel: [363633.203730] Modules linked in: Character_devices(OF+) Character_devices_test(OF) main_module(POF) hid_generic usbhid hid psmouse mptspi mptscsih ahci pcnet32 vmw_pvscsi mptbase libahci mii vmxnet3 floppy [last unloaded: Character_devices]
May 17 05:47:04 ubuntu kernel: [363633.203758] CPU: 5 PID: 13094 Comm: insmod Tainted: PF          O 3.13.0-32-generic #57-Ubuntu
May 17 05:47:04 ubuntu kernel: [363633.203760] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/31/2013
May 17 05:47:04 ubuntu kernel: [363633.203762] task: f6830cf0 ti: e619a000 task.ti: e619a000
May 17 05:47:04 ubuntu kernel: [363633.203764] EIP: 0060:[<c117c83c>] EFLAGS: 00010246 CPU: 5
May 17 05:47:04 ubuntu kernel: [363633.203766] EIP is at cdev_init+0x2c/0x80
May 17 05:47:04 ubuntu kernel: [363633.203767] EAX: 00000000 EBX: 00000000 ECX: 0000000f EDX: 0000003c
May 17 05:47:04 ubuntu kernel: [363633.203768] ESI: f8496000 EDI: 00000000 EBP: e619bde4 ESP: e619bdd8
May 17 05:47:04 ubuntu kernel: [363633.203770]  DS: 007b ES: 007b FS: 00d8 GS: 00e0 SS: 0068
May 17 05:47:04 ubuntu kernel: [363633.203771] CR0: 80050033 CR2: 00000000 CR3: 362ca000 CR4: 001406f0
May 17 05:47:04 ubuntu kernel: [363633.204011] Stack:
May 17 05:47:04 ubuntu kernel: [363633.204014]  00000000 f8499000 000015a9 e619bdfc f8499021 00000001 00000000 0e700000
May 17 05:47:04 ubuntu kernel: [363633.204033]  00000000 e619be78 c1002122 00000000 00000000 80000000 00000000 00000000
May 17 05:47:04 ubuntu kernel: [363633.204036]  00000001 00000001 0002632e 00000000 00000000 00000000 f8499000 00001000
May 17 05:47:04 ubuntu kernel: [363633.204040] Call Trace:
May 17 05:47:04 ubuntu kernel: [363633.204046]  [<f8499000>] ? 0xf8498fff
May 17 05:47:04 ubuntu kernel: [363633.204051]  [<f8499021>] character_devices_init+0x21/0x1000 [Character_devices]
May 17 05:47:04 ubuntu kernel: [363633.204247]  [<c1002122>] do_one_initcall+0xd2/0x190
May 17 05:47:04 ubuntu kernel: [363633.204252]  [<f8499000>] ? 0xf8498fff
May 17 05:47:04 ubuntu kernel: [363633.204268]  [<c104c87f>] ? set_memory_nx+0x5f/0x70
May 17 05:47:04 ubuntu kernel: [363633.204631]  [<c164caaa>] ? set_section_ro_nx+0x54/0x59
May 17 05:47:04 ubuntu kernel: [363633.204651]  [<c10c4061>] load_module+0x1121/0x18e0
May 17 05:47:04 ubuntu kernel: [363633.204655]  [<c10c4985>] SyS_finit_module+0x75/0xc0
May 17 05:47:04 ubuntu kernel: [363633.204814]  [<c1139a2b>] ? vm_mmap_pgoff+0x7b/0xa0
May 17 05:47:04 ubuntu kernel: [363633.204834]  [<c165efcd>] sysenter_do_call+0x12/0x28
May 17 05:47:04 ubuntu kernel: [363633.204835] Code: 89 e5 57 56 53 3e 8d 74 26 00 a8 01 89 d6 89 c3 89 c7 ba 3c 00 00 00 75 46 f7 c7 02 00 00 00 75 4e 89 d1 31 c0 c1 e9 02 f6 c2 02 <f3> ab 74 09 31 c0 83 c7 02 66 89 47 fe 83 e2 01 74 03 c6 07 00
May 17 05:47:04 ubuntu kernel: [363633.204863] EIP: [<c117c83c>] cdev_init+0x2c/0x80 SS:ESP 0068:e619bdd8
May 17 05:47:04 ubuntu kernel: [363633.204866] CR2: 0000000000000000
May 17 05:47:04 ubuntu kernel: [363633.205031] ---[ end trace f514a7c3f644d531 ]---
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices$ 

```

following ref :`https://blog.csdn.net/gatieme/article/details/75108154`
```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo rmmod Character_devices
rmmod: ERROR: Module Character_devices is in use
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo rmmod -f Character-devices
rmmod: ERROR: ../libkmod/libkmod-module.c:769 kmod_module_remove_module() could not remove 'Character_devices': Device or resource busy
rmmod: ERROR: could not remove module Character-devices: Device or resource busy
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ lsmod 
Module                  Size  Used by
Character_devices      12708  1 
Character_devices_test    16755  0 
main_module            12399  0 
...
```


ok:

```c
	if (!globalmem_devp) {
```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices.ko wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices[ 3223.111677] [character_devices] character_devices_init kzalloc fail: -12.
[ 3508.047858] [character_devices] character_devices_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/test-globalmem$ lsmod
Module                  Size  Used by
Character_devices      12708  0 
test                   12796  0 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/test-globalmem$ cat /proc/devices 
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  4 ttyS
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  5 ttyprintk
  7 vcs
 10 misc
 13 input
 21 sg
 29 fb
108 ppp
128 ptm
136 pts
180 usb
189 usb_device
231 globalmem_name1
251 globalmem
252 bsg
253 watchdog
254 rtc

Block devices:
  1 ramdisk
  2 fd
259 blkext
  7 loop
  8 sd
  9 md
 11 sr
 65 sd
 66 sd
 67 sd
 68 sd
 69 sd
 70 sd
 71 sd
128 sd
129 sd
130 sd
131 sd
132 sd
133 sd
134 sd
135 sd
252 device-mapper
253 virtblk
254 mdp
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/test-globalmem$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/test-globalmem$ 

```

issue:

without open function
```c

static ssize_t globalmem_open(struct inode *inode, struct file *flip)
{
	printk(TAG "[%s] init flip->private_data.\n", __func__);

	flip->private_data = globalmem_devp;
	return 0;
}
static struct file_operations globalmem_fops = {
	.open = globalmem_open,
```
log:

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo mknod /dev/globaltest c 231 0
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep global
crw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 


wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu' > /dev/globaltest"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest 
cat: /dev/globaltest: Bad address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices
[ 9331.366499] [character_devices] [globalmem_write] written count: 9
[ 9335.778665] [character_devices] [globalmem_read] read count: 65536
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo rmmod Character-devices.ko 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices
[ 9584.826784] [character_devices] character_devices_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep global
crw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu' > /dev/globaltest"
sh: 1: cannot create /dev/globaltest: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest 
cat: /dev/globaltest: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

```
with open function :

```c

static ssize_t globalmem_open(struct inode *inode, struct file *flip)
{
	printk(TAG "[%s] init flip->private_data.\n", __func__);

	flip->private_data = globalmem_devp;
	return 0;
}
static struct file_operations globalmem_fops = {
	.open = globalmem_open,
```

log: 
```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 


wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices.ko 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /proc/devices 
Character devices:
...
250 globalmem_name2
251 globalmem


wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep globalcrw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ mknod /dev/globaltest250_0 c 250 0mknod: ‘/dev/globaltest250_0’: Permission denied
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo mknod /dev/globaltest250_0 c 250 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep globalcrw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:10 globaltest250_0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu' > /dev/globaltest250_0"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest250_0 
hello wu
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices[ 9782.048084] [character_devices] character_devices_init sucess
[ 9849.468048] [character_devices] [globalmem_open] init flip->private_data.
[ 9849.468057] [character_devices] [globalmem_write] written count: 9
[ 9849.468058] [character_devices] [globalmem_write] written 9 bytes from 0.
[ 9857.004249] [character_devices] [globalmem_open] init flip->private_data.
[ 9857.004261] [character_devices] [globalmem_read] read count: 65536
[ 9857.004264] [character_devices] [globalmem_read] read 4096 bytes from 0.
[ 9857.004279] [character_devices] [globalmem_read] read count: 65536
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu ...' > /dev/globaltest250_0"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest250_0 hello wu ...
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices[10316.672037] [character_devices] [globalmem_open] init flip->private_data.
[10316.672047] [character_devices] [globalmem_write] written count: 13
[10316.672048] [character_devices] [globalmem_write] written 13 bytes from 0.
[10320.526118] [character_devices] [globalmem_open] init flip->private_data.
[10320.526132] [character_devices] [globalmem_read] read count: 65536
[10320.526136] [character_devices] [globalmem_read] read 4096 bytes from 0.
[10320.526153] [character_devices] [globalmem_read] read count: 65536
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo rmmod Character-devices.ko wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices.ko wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices[10941.115635] [character_devices] character_devices_exit sucess
[10952.243219] [character_devices] character_devices_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep globalcrw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:10 globaltest250_0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /proc/devices |grep global250 globalmem_name2
251 globalmem
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu .' > /dev/globaltest250_0"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest250_0 hello wu .
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices[10991.229064] [character_devices] [globalmem_open] init flip->private_data.
[10991.229073] [character_devices] [globalmem_write] written count: 11, p:0.
[10991.229075] [character_devices] [globalmem_write] written 11 bytes from 0.
[10998.877816] [character_devices] [globalmem_open] init flip->private_data.
[10998.877828] [character_devices] [globalmem_read] read count: 65536, p:0.
[10998.877831] [character_devices] [globalmem_read] read 4096 bytes from 0.
[10998.877846] [character_devices] [globalmem_read] read count: 65536, p:4096.
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

```


```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo mknod /dev/globaltest250_1 c 250 1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep global
crw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:10 globaltest250_0
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu 250 1' > /dev/globaltest250_1"
sh: 1: cannot create /dev/globaltest250_1: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu 250 1' > /dev/globaltest250_1"
sh: 1: cannot create /dev/globaltest250_1: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu 250 0' > /dev/globaltest250_0"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest250_0 hello wu 250 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices[11818.419446] [character_devices] [globalmem_open] init flip->private_data.
[11818.419458] [character_devices] [globalmem_read] read count: 65536, p:0.
[11818.419461] [character_devices] [globalmem_read] read 4096 bytes from 0.
[11818.419475] [character_devices] [globalmem_read] read count: 65536, p:4096.
[11950.388583] [character_devices] [globalmem_open] init flip->private_data.
[11950.388592] [character_devices] [globalmem_write] written count: 15, p:0.
[11950.388593] [character_devices] [globalmem_write] written 15 bytes from 0.
[11993.383681] [character_devices] [globalmem_open] init flip->private_data.
[11993.383693] [character_devices] [globalmem_read] read count: 65536, p:0.
[11993.383696] [character_devices] [globalmem_read] read 4096 bytes from 0.
[11993.383713] [character_devices] [globalmem_read] read count: 65536, p:4096.
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo mknod /dev/globaltest250_1 c 250 1
mknod: ‘/dev/globaltest250_1’: File exists
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo mknod /dev/globaltest250-2 c 250 2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_deviceswu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep global
crw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:10 globaltest250_0
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
crw-r--r--  1 root root    250,   2 May 18 00:47 globaltest250-2
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu 250 1' > /dev/globaltest250-2"
sh: 1: cannot create /dev/globaltest250-2: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 


wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo mknod /dev/globaltest555_1 c 555 1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep global
crw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:10 globaltest250_0
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
crw-r--r--  1 root root    250,   2 May 18 00:47 globaltest250-2
crw-r--r--  1 root root    555,   1 May 18 00:49 globaltest555_1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu 555 1' > /dev/globaltest555_1"
sh: 1: cannot create /dev/globaltest555_1: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest555_1
cat: /dev/globaltest555_1: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo rm -f /dev/globaltest250_0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep globalcrw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
crw-r--r--  1 root root    250,   2 May 18 00:47 globaltest250-2
crw-r--r--  1 root root    555,   1 May 18 00:49 globaltest555_1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo mknod /dev/globaltest250_0 c 250 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep globalcrw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
crw-r--r--  1 root root    250,   2 May 18 00:47 globaltest250-2
crw-r--r--  1 root root    555,   1 May 18 00:49 globaltest555_1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo mknod /dev/globaltest250_0-b b 250 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ ls /dev -l |grep globalcrw-r--r--  1 root root    231,   0 May 17 23:59 globaltest
crw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0
brw-r--r--  1 root root    250,   0 May 18 00:54 globaltest250_0-b
crw-r--r--  1 root root    250,   1 May 18 00:44 globaltest250_1
crw-r--r--  1 root root    250,   2 May 18 00:47 globaltest250-2
crw-r--r--  1 root root    555,   1 May 18 00:49 globaltest555_1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu 250 0' > /dev/globaltest250_0"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest250_0
hello wu 250 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu 250 0' > /dev/globaltest250_0-b"
sh: 1: cannot create /dev/globaltest250_0-b: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest250_0-b cat: /dev/globaltest250_0-b: No such device or address
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/2.Character-devices/Character-devices.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices.ko 
insmod: ERROR: could not insert module Character-devices.ko: File exists
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo rmmod Character_devices 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo insmod Character-devices.ko 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /proc/devices 
250 globalmem_name2
...
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo sh -c "echo 'hello wu 250 0' > /dev/globaltest250_0"
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ cat /dev/globaltest250_0hello wu 250 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo dmesg -c|grep character_devices
[14580.913718] [character_devices] character_devices_exit sucess
[14584.494848] [character_devices] character_devices_init sucess
[14604.301115] [character_devices] [globalmem_open] init flip private_data.
[14604.301125] [character_devices] [globalmem_write] written count: 15, p:0.
[14604.301126] [character_devices] [globalmem_write] written 15 bytes from 0.
[14604.301128] [character_devices] [globalmem_release] release.
[14610.441174] [character_devices] [globalmem_open] init flip private_data.
[14610.441189] [character_devices] [globalmem_read] read count: 65536, p:0.
[14610.441192] [character_devices] [globalmem_read] read 4096 bytes from 0.
[14610.441209] [character_devices] [globalmem_read] read count: 65536, p:4096.
[14610.441213] [character_devices] [globalmem_release] release.
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 

```



