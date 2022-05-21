```
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/.../1.Character-device              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/.../1.Character-device/character-device_p.o
  Building modules, stage 2.
  MODPOST 1 modules
WARNING: modpost: Found 1 section mismatch(es).
To see full details build your kernel with:
'make CONFIG_DEBUG_SECTION_MISMATCH=y'
  CC      /home/wu-being/.../1.Character-device/character-device_p.mod.o
  LD [M]  /home/wu-being/.../1.Character-device/character-device_p.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ 

wu-being@ubuntu:~/.../1.Character-device$ sudo insmod character-device_p.ko 

wu-being@ubuntu:~/.../1.Character-device$ dmesg |grep character
[95945.796343] character_device_p: module verification failed: signature and/or  required key missing - tainting kernel
[95945.796945] [character_device_p] character_device_p_probe sucess
[95945.796961] [character_device_p] character_device_p_init sucess
[95945.797351] Modules linked in: character_device_p(OF) hid_generic usbhid hid psmouse mptspi mptscsih ahci pcnet32 mptbase libahci mii vmw_pvscsi floppy vmxnet3
wu-being@ubuntu:~/.../1.Character-device$ 

```

```
wu-being@ubuntu:~/.../1.Character-device$ cat /var/log/kern.log

...
May 21 20:13:10 ubuntu kernel: [95945.796343] character_device_p: module verification failed: signature and/or  required key missing - tainting kernel
May 21 20:13:10 ubuntu kernel: [95945.796945] [character_device_p] character_device_p_probe sucess
May 21 20:13:10 ubuntu kernel: [95945.796961] [character_device_p] character_device_p_init sucess
May 21 20:13:10 ubuntu kernel: [95945.797330] BUG: unable to handle kernel paging request at f8a2a014
May 21 20:13:10 ubuntu kernel: [95945.797333] IP: [<c14092a1>] dev_uevent+0x51/0x2e0
May 21 20:13:10 ubuntu kernel: [95945.797346] *pdpt = 0000000001a96001 *pde = 0000000036a08067 *pte = 0000000000000000 
May 21 20:13:10 ubuntu kernel: [95945.797348] Oops: 0000 [#1] SMP 
May 21 20:13:10 ubuntu kernel: [95945.797351] Modules linked in: character_device_p(OF) hid_generic usbhid hid psmouse mptspi mptscsih ahci pcnet32 mptbase libahci mii vmw_pvscsi floppy vmxnet3
May 21 20:13:10 ubuntu kernel: [95945.797358] CPU: 1 PID: 10519 Comm: systemd-udevd Tainted: GF          O 3.13.0-32-generic #57-Ubuntu
May 21 20:13:10 ubuntu kernel: [95945.797359] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/31/2013
May 21 20:13:10 ubuntu kernel: [95945.797360] task: e83619e0 ti: edb58000 task.ti: edb58000
May 21 20:13:10 ubuntu kernel: [95945.797361] EIP: 0060:[<c14092a1>] EFLAGS: 00010286 CPU: 1
May 21 20:13:10 ubuntu kernel: [95945.797362] EIP is at dev_uevent+0x51/0x2e0
May 21 20:13:10 ubuntu kernel: [95945.797363] EAX: f8a2a014 EBX: f8a26014 ECX: e8241000 EDX: f8a26014
May 21 20:13:10 ubuntu kernel: [95945.797364] ESI: e8241000 EDI: f8a2600c EBP: edb59ecc ESP: edb59e98
May 21 20:13:10 ubuntu kernel: [95945.797364]  DS: 007b ES: 007b FS: 00d8 GS: 00e0 SS: 0068
May 21 20:13:10 ubuntu kernel: [95945.797365] CR0: 80050033 CR2: f8a2a014 CR3: 2819b000 CR4: 001406f0
May 21 20:13:10 ubuntu kernel: [95945.797384] Stack:
May 21 20:13:10 ubuntu kernel: [95945.797385]  edb59ecc c116368a e9ed3430 edb59ebc c1149b8f c1408344 00000888 c1408344
May 21 20:13:10 ubuntu kernel: [95945.797387]  000080d0 e8241000 f75e0140 e8241000 c16af038 edb59ef4 c140835c e8c2b254
May 21 20:13:10 ubuntu kernel: [95945.797389]  edb59f24 c114bc21 c16af038 e8246000 c197212c c14082e0 c1407d20 edb59f04
May 21 20:13:10 ubuntu kernel: [95945.797391] Call Trace:
May 21 20:13:10 ubuntu kernel: [95945.797398]  [<c116368a>] ? kmem_cache_alloc_trace+0x17a/0x190
May 21 20:13:10 ubuntu kernel: [95945.797402]  [<c1149b8f>] ? __vma_link_rb+0x9f/0xc0
May 21 20:13:10 ubuntu kernel: [95945.797404]  [<c1408344>] ? uevent_show+0x64/0xe0
May 21 20:13:10 ubuntu kernel: [95945.797405]  [<c1408344>] ? uevent_show+0x64/0xe0
May 21 20:13:10 ubuntu kernel: [95945.797406]  [<c140835c>] uevent_show+0x7c/0xe0
May 21 20:13:10 ubuntu kernel: [95945.797407]  [<c114bc21>] ? mmap_region+0x121/0x530
May 21 20:13:10 ubuntu kernel: [95945.797409]  [<c14082e0>] ? dev_driver_string+0x40/0x40
May 21 20:13:10 ubuntu kernel: [95945.797410]  [<c1407d20>] ? dev_uevent_name+0x30/0x30
May 21 20:13:10 ubuntu kernel: [95945.797411]  [<c1407d38>] dev_attr_show+0x18/0x40
May 21 20:13:10 ubuntu kernel: [95945.797415]  [<c11dad15>] sysfs_seq_show+0xe5/0x1c0
May 21 20:13:10 ubuntu kernel: [95945.797418]  [<c119846e>] seq_read+0xce/0x370
May 21 20:13:10 ubuntu kernel: [95945.797420]  [<c1139a2b>] ? vm_mmap_pgoff+0x7b/0xa0
May 21 20:13:10 ubuntu kernel: [95945.797421]  [<c11983a0>] ? seq_hlist_next_percpu+0x90/0x90
May 21 20:13:10 ubuntu kernel: [95945.797424]  [<c1179238>] vfs_read+0x78/0x140
May 21 20:13:10 ubuntu kernel: [95945.797425]  [<c11799a9>] SyS_read+0x49/0x90
May 21 20:13:10 ubuntu kernel: [95945.797437]  [<c165efcd>] sysenter_do_call+0x12/0x28
May 21 20:13:10 ubuntu kernel: [95945.797438] Code: 01 00 00 8b 43 28 85 c0 74 1a 8b 00 85 c0 74 14 89 44 24 08 c7 44 24 04 0b f8 8a c1 89 34 24 e8 f6 a0 ee ff 8b 43 48 85 c0 74 16 <8b> 00 c7 44 24 04 16 f8 8a c1 89 34 24 89 44 24 08 e8 d9 a0 ee
May 21 20:13:10 ubuntu kernel: [95945.797449] EIP: [<c14092a1>] dev_uevent+0x51/0x2e0 SS:ESP 0068:edb59e98
May 21 20:13:10 ubuntu kernel: [95945.797451] CR2: 00000000f8a2a014
May 21 20:13:10 ubuntu kernel: [95945.797453] ---[ end trace 36ea36da9a0b289e ]---
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ 


wu-being@ubuntu:~/.../1.Character-device$ sudo rmmod character-device_p.ko 
ka si ....~!!!!!!!!!!!!!!!

```
up issue :

```c
/*
static struct platform_device *character_devices_p = {
	&character_device1_p,
	//...
};
*/
static struct platform_driver character_driver_p __initdata = {
	.driver = {
		.name = "character_device+driver_p",
		.owner= THIS_MODULE,
	},
	.probe = character_device_p_probe,
	.remove = character_device_p_remove,
};
```

```
wu-being@ubuntu:~/.../1.Character-device$ ls /sys/devices/platform/character_device+driver_p/ -l
total 0
lrwxrwxrwx 1 root root    0 May 21 20:37 driver -> ../../../bus/platform/drivers/character_device+driver_p
-r--r--r-- 1 root root 4096 May 21 20:37 modalias
drwxr-xr-x 2 root root    0 May 21 20:37 power
lrwxrwxrwx 1 root root    0 May 21 20:37 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 May 21 20:37 uevent
wu-being@ubuntu:~/.../1.Character-device$ 

wu-being@ubuntu:~/.../1.Character-device$ ls /sys/bus/platform/drivers/character_device+driver_p/ -l
total 0
--w------- 1 root root 4096 May 21 20:38 bind
lrwxrwxrwx 1 root root    0 May 21 20:38 character_device+driver_p -> ../../../../devices/platform/character_device+driver_p
lrwxrwxrwx 1 root root    0 May 21 20:38 module -> ../../../../module/character_device_p
--w------- 1 root root 4096 May 21 20:37 uevent
--w------- 1 root root 4096 May 21 20:38 unbind
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ 
```

test:

```c
/*
static struct platform_device *character_devices_p __initdata= {
	&character_device1_p,
	//...
};
*/
static struct platform_driver character_driver_p  = {
	.driver = {
		.name = "character_device+driver_p",
		.owner= THIS_MODULE,
	},
	.probe = character_device_p_probe,
	.remove = character_device_p_remove,
};
```
build ok: 
```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/1.Platform-device-driver/1.Character-device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/1.Platform-device-driver/1.Character-device$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/1.Platform-device-driver/1.Character-device              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/1.Platform-device-driver/1.Character-device/character-device_p.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/1.Platform-device-driver/1.Character-device/character-device_p.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/1.Platform-device-driver/1.Character-device/character-device_p.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/1.Platform-device-driver/1.Character-device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/1.Platform-device-driver/1.Character-device$ 

```

```
log same up.  so parse to 1.Character-device and 2.Character-driver is ok
```

