
# bug 1

```c
globalmem_setup_cdev(globalmem_devp, i);

```
log:

```
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ sudo dmesg -c|grep character_devices
[178307.733214] [character_devices_n_with_mutext] character_devices_n_with_mutext_init sucess
[178470.040358]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040405]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040444]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040480]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040527]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040563]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040600]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040635]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040670]  [<fbd79336>] character_devices_n_with_mutext_exit+0x23/0xced [Character_devices_n_with_mutex]
[178470.040680] [character_devices_n_with_mutext] character_devices_n_with_mutext_exit sucess
[178545.743518] [character_devices_n_with_mutext] character_devices_n_with_mutext_init sucess

...
May 19 08:27:26 ubuntu kernel: [180129.521728] ------------[ cut here ]------------
May 19 08:27:26 ubuntu kernel: [180129.521730] WARNING: CPU: 1 PID: 30294 at /build/buildd/linux-3.13.0/lib/kobject.c:649 kobject_put+0x51/0x60()
May 19 08:27:26 ubuntu kernel: [180129.521730] kobject: '(null)' (e39692f4): is not initialized, yet kobject_put() is being called.
May 19 08:27:26 ubuntu kernel: [180129.521731] Modules linked in: Character_devices_n_with_mutex(OF-) test(OF) psmouse mptspi ahci mptscsih libahci mptbase pcnet32 mii floppy vmw_pvscsi vmxnet3 [last unloaded: Character_devices_n_with_mutex]
May 19 08:27:26 ubuntu kernel: [180129.521735] CPU: 1 PID: 30294 Comm: rmmod Tainted: GF     D W  O 3.13.0-32-generic #57-Ubuntu
May 19 08:27:26 ubuntu kernel: [180129.521736] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/31/2013
May 19 08:27:26 ubuntu kernel: [180129.521737]  00000000 00000000 e8d0deb8 c1650cd3 e8d0def8 e8d0dee8 c10567ee c186a288
May 19 08:27:26 ubuntu kernel: [180129.521739]  e8d0df14 00007656 c186a2d8 00000289 c12f2291 c12f2291 e39692f4 00000800
May 19 08:27:26 ubuntu kernel: [180129.521741]  00000000 e8d0df00 c1056843 00000009 e8d0def8 c186a288 e8d0df14 e8d0df20
May 19 08:27:26 ubuntu kernel: [180129.521744] Call Trace:
May 19 08:27:26 ubuntu kernel: [180129.521745]  [<c1650cd3>] dump_stack+0x41/0x52
May 19 08:27:26 ubuntu kernel: [180129.521747]  [<c10567ee>] warn_slowpath_common+0x7e/0xa0
May 19 08:27:26 ubuntu kernel: [180129.521748]  [<c12f2291>] ? kobject_put+0x51/0x60
May 19 08:27:26 ubuntu kernel: [180129.521749]  [<c12f2291>] ? kobject_put+0x51/0x60
May 19 08:27:26 ubuntu kernel: [180129.521751]  [<c1056843>] warn_slowpath_fmt+0x33/0x40
May 19 08:27:26 ubuntu kernel: [180129.521752]  [<c12f2291>] kobject_put+0x51/0x60
May 19 08:27:26 ubuntu kernel: [180129.521754]  [<c117c7d2>] cdev_del+0x22/0x30
May 19 08:27:26 ubuntu kernel: [180129.521755]  [<f84972ec>] character_devices_n_with_mutext_exit+0x19/0xd2d [Character_devices_n_with_mutex]
May 19 08:27:26 ubuntu kernel: [180129.521757]  [<c10c21e8>] SyS_delete_module+0x148/0x1e0
May 19 08:27:26 ubuntu kernel: [180129.521758]  [<c117a75d>] ? ____fput+0xd/0x10
May 19 08:27:26 ubuntu kernel: [180129.521760]  [<c107239e>] ? task_work_run+0x7e/0xb0
May 19 08:27:26 ubuntu kernel: [180129.521761]  [<c165efcd>] sysenter_do_call+0x12/0x28
May 19 08:27:26 ubuntu kernel: [180129.521762] ---[ end trace dc2feca310df7569 ]---
May 19 08:27:26 ubuntu kernel: [180129.521764] [character_devices_n_with_mutext] character_devices_n_with_mutext_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 


```

fixed

```
globalmem_setup_cdev(globalmem_devp + i, i);
```




# bug 2


wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ sudo sh -c "echo '+mut 250 0' > /dev/globaltest_n+mutex250_0"
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ sudo sh -c "echo '+mut 250 01' > /dev/globaltest_n+mutex250_1"
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ sudo sh -c "echo '+mut 250 012' > /dev/globaltest_n+mutex250_2"

wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ cat /dev/globaltest_n+mutex250_2

// dead lock ????? 
-->
```

BUG: unable to handle kernel NULL pointer dereference at    (null) =====> at non-first devp->mutex

```
	mutex_init(&globalmem_devp->mutex); // bug: only for first devp

	for (i = 0; i < GLOBALMEM_NUM; i++) {
		//globalmem_setup_cdev(globalmem_devp, i);
		globalmem_setup_cdev(globalmem_devp + i, i);
	}
```

```
May 20 01:04:19 ubuntu kernel: [  398.894211] [character_devices_n_with_mutext] character_devices_n_with_mutext_init sucess
May 20 01:04:26 ubuntu kernel: [  405.763491] [character_devices_n_with_mutext] character_devices_n_with_mutext_exit sucess
May 20 01:04:36 ubuntu kernel: [  415.919137] [character_devices_n_with_mutext] character_devices_n_with_mutext_init sucess
May 20 01:05:42 ubuntu kernel: [  481.997490] [character_devices_n_with_mutext] [globalmem_open] container_of private_data.
May 20 01:05:42 ubuntu kernel: [  481.997500] [character_devices_n_with_mutext] [globalmem_write] written count: 13, p:0.
May 20 01:05:42 ubuntu kernel: [  482.100569] BUG: unable to handle kernel NULL pointer dereference at   (null)
May 20 01:05:42 ubuntu kernel: [  482.100577] IP: [<c165659d>] __mutex_lock_slowpath+0xed/0x171
May 20 01:05:42 ubuntu kernel: [  482.100589] *pdpt = 00000000291c4001 *pde = 0000000000000000 
May 20 01:05:42 ubuntu kernel: [  482.100592] Oops: 0002 [#1] SMP 
May 20 01:05:42 ubuntu kernel: [  482.100594] Modules linked in: Character_devices_n_with_mutex(OF) hid_generic usbhid hid psmouse mptspi mptscsih ahci pcnet32 mptbase libahci mii floppy vmw_pvscsi vmxnet3 [last unloaded: Character_devices_n_with_mutex]
May 20 01:05:42 ubuntu kernel: [  482.100606] CPU: 0 PID: 3187 Comm: sh Tainted: GF       W  O 3.13.0-32-generic #57-Ubuntu
May 20 01:05:42 ubuntu kernel: [  482.100608] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/31/2013
May 20 01:05:42 ubuntu kernel: [  482.100609] task: e3b326d0 ti: f633a000 task.ti: f633a000
May 20 01:05:42 ubuntu kernel: [  482.100611] EIP: 0060:[<c165659d>] EFLAGS: 00010286 CPU: 0
May 20 01:05:42 ubuntu kernel: [  482.100612] EIP is at __mutex_lock_slowpath+0xed/0x171
May 20 01:05:42 ubuntu kernel: [  482.100613] EAX: 00000000 EBX: e3a730e4 ECX: e3a730ec EDX: f633bf0c
May 20 01:05:42 ubuntu kernel: [  482.100614] ESI: e3a730e8 EDI: ffffffff EBP: f633bf24 ESP: f633bf04
May 20 01:05:42 ubuntu kernel: [  482.100615]  DS: 007b ES: 007b FS: 00d8 GS: 00e0 SS: 0068
May 20 01:05:42 ubuntu kernel: [  482.100616] CR0: 80050033 CR2: a4418000 CR3: 28d3d000 CR4: 001406f0
May 20 01:05:42 ubuntu kernel: [  482.100645] Stack:
May 20 01:05:42 ubuntu kernel: [  482.100646]  e3a730ec e3b326d0 e3a730ec 00000000 c164c812 e3a730e4 e3a720a8 0000000d
May 20 01:05:42 ubuntu kernel: [  482.100649]  f633bf30 c1655aec 00000000 f633bf60 f845214b f845309c f8453489 0000000d
May 20 01:05:42 ubuntu kernel: [  482.100651]  00000000 f6407480 e3a730e4 b87aa320 e8edbcc0 0000000d f84520f0 f633bf88
May 20 01:05:42 ubuntu kernel: [  482.100654] Call Trace:
May 20 01:05:42 ubuntu kernel: [  482.100657]  [<c164c812>] ? printk+0x50/0x52
May 20 01:05:42 ubuntu kernel: [  482.100659]  [<c1655aec>] mutex_lock+0x1c/0x28
May 20 01:05:42 ubuntu kernel: [  482.100662]  [<f845214b>] globalmem_write+0x5b/0xe0 [Character_devices_n_with_mutex]
May 20 01:05:42 ubuntu kernel: [  482.100664]  [<f84520f0>] ? globalmem_ioctl+0x90/0x90 [Character_devices_n_with_mutex]
May 20 01:05:42 ubuntu kernel: [  482.100668]  [<c1179395>] vfs_write+0x95/0x1b0
May 20 01:05:42 ubuntu kernel: [  482.100670]  [<c1179a39>] SyS_write+0x49/0x90
May 20 01:05:42 ubuntu kernel: [  482.100672]  [<c165efcd>] sysenter_do_call+0x12/0x28
May 20 01:05:42 ubuntu kernel: [  482.100673] Code: 8b 03 85 c0 78 09 31 c0 87 03 83 f8 01 74 6b 8d 43 08 bf ff ff ff ff 89 c1 89 45 e0 8b 43 0c 8d 55 e8 89 53 0c 89 4d e8 89 45 ec <89> 10 8b 45 e4 89 45 f0 eb 1d 90 8b 45 e4 c7 00 02 00 00 00 89
May 20 01:05:42 ubuntu kernel: [  482.100688] EIP: [<c165659d>] __mutex_lock_slowpath+0xed/0x171 SS:ESP 0068:f633bf04
May 20 01:05:42 ubuntu kernel: [  482.100690] CR2: 0000000000000000
May 20 01:05:42 ubuntu kernel: [  482.100692] ---[ end trace 968125b8ff3e4d3e ]---
May 20 01:05:42 ubuntu kernel: [  482.100776] [character_devices_n_with_mutext] [globalmem_release] release.
May 20 01:05:47 ubuntu kernel: [  486.734384] [character_devices_n_with_mutext] [globalmem_open] container_of private_data.
May 20 01:05:47 ubuntu kernel: [  486.734396] [character_devices_n_with_mutext] [globalmem_read] read count: 65536, p:0.
May 20 01:06:12 ubuntu kernel: [  512.435595] BUG: soft lockup - CPU#5 stuck for 23s! [cat:3188]
May 20 01:06:12 ubuntu kernel: [  512.435599] Modules linked in: Character_devices_n_with_mutex(OF) hid_generic usbhid hid psmouse mptspi mptscsih ahci pcnet32 mptbase libahci mii floppy vmw_pvscsi vmxnet3 [last unloaded: Character_devices_n_with_mutex]
May 20 01:06:12 ubuntu kernel: [  512.435612] CPU: 5 PID: 3188 Comm: cat Tainted: GF     D W  O 3.13.0-32-generic #57-Ubuntu
May 20 01:06:12 ubuntu kernel: [  512.435613] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/31/2013
May 20 01:06:12 ubuntu kernel: [  512.435615] task: e3b36780 ti: e84e8000 task.ti: e84e8000
May 20 01:06:12 ubuntu kernel: [  512.435616] EIP: 0060:[<c16579a7>] EFLAGS: 00000202 CPU: 5
May 20 01:06:12 ubuntu kernel: [  512.435622] EIP is at _raw_spin_lock+0x37/0x50
May 20 01:06:12 ubuntu kernel: [  512.435623] EAX: 000001b1 EBX: 00000002 ECX: e3a730e8 EDX: 00000000
May 20 01:06:12 ubuntu kernel: [  512.435624] ESI: 00000002 EDI: e3a730f8 EBP: e84e9f00 ESP: e84e9ef8
May 20 01:06:12 ubuntu kernel: [  512.435625]  DS: 007b ES: 007b FS: 00d8 GS: 00e0 SS: 0068
May 20 01:06:12 ubuntu kernel: [  512.435626] CR0: 80050033 CR2: 0804c6d0 CR3: 2390e000 CR4: 001406f0
May 20 01:06:12 ubuntu kernel: [  512.435655] Stack:
May 20 01:06:12 ubuntu kernel: [  512.435656]  e3a730e4 e3a730e8 e84e9f28 c1656572 e84e8000 e3b36780 00000000 00000001
May 20 01:06:12 ubuntu kernel: [  512.435659]  c164c812 e3a730e4 00001000 e3a720a8 e84e9f34 c1655aec 00000000 e84e9f64
May 20 01:06:12 ubuntu kernel: [  512.435661]  f845222d f8453174 f845347a 00010000 00000000 00000014 e3a730e4 09f8c000
May 20 01:06:12 ubuntu kernel: [  512.435664] Call Trace:
May 20 01:06:12 ubuntu kernel: [  512.435668]  [<c1656572>] __mutex_lock_slowpath+0xc2/0x171
May 20 01:06:12 ubuntu kernel: [  512.435670]  [<c164c812>] ? printk+0x50/0x52
May 20 01:06:12 ubuntu kernel: [  512.435672]  [<c1655aec>] mutex_lock+0x1c/0x28
May 20 01:06:12 ubuntu kernel: [  512.435675]  [<f845222d>] globalmem_read+0x5d/0xe0 [Character_devices_n_with_mutex]
May 20 01:06:12 ubuntu kernel: [  512.435677]  [<f84521d0>] ? globalmem_write+0xe0/0xe0 [Character_devices_n_with_mutex]
May 20 01:06:12 ubuntu kernel: [  512.435680]  [<c1179238>] vfs_read+0x78/0x140
May 20 01:06:12 ubuntu kernel: [  512.435685]  [<c1125645>] ? SyS_fadvise64_64+0x1e5/0x260
May 20 01:06:12 ubuntu kernel: [  512.435687]  [<c11799a9>] SyS_read+0x49/0x90
May 20 01:06:12 ubuntu kernel: [  512.435689]  [<c165efcd>] sysenter_do_call+0x12/0x28
May 20 01:06:12 ubuntu kernel: [  512.435690] Code: ba 00 02 00 00 f0 66 0f c1 10 0f b6 c6 38 d0 75 04 5b 5e 5d c3 83 e0 fe 89 c3 0f b6 f0 b8 00 80 00 00 0f b6 11 38 d3 74 e8 f3 90 <83> e8 01 75 f2 89 c8 89 f2 8d b6 00 00 00 00 eb e1 90 8d b4 26
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 
wu-being@ubuntu:~/code/linux_driver_study/song07--Concurrency-control/1.Character-devices_n-with-mutex$ 

```



