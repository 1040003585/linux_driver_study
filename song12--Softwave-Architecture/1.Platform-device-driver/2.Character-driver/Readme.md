```
 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/.../1.Platform-device-driver/2.Character-driver              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/.../1.Platform-device-driver/2.Character-driver/character-driver_p.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/.../1.Platform-device-driver/2.Character-driver/character-driver_p.mod.o
  LD [M]  /home/wu-being/.../1.Platform-device-driver/2.Character-driver/character-driver_p.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ sudo insmod character-driver_p.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ ls /sys/bus/platform/drivers/
88pm860x-regulator/        floppy/                    mdio-gpio/                 simple-framebuffer/        uart-sccnxp/
alarmtimer/                i8042/                     msic_gpio/                 sram/                      vesa-framebuffer/
byt_gpio/                  intel_msic/                ohci-platform/             stmpe-gpio/                virtio-mmio/
character_device+driver_p/ ipmi/                      palmas-gpio/               syscon/                    xgene-rtc/
charger-manager/           lp8788-aldo/               pmic_gpio/                 tc3589x-gpio/              xhci-hcd/
clk-lpt/                   lp8788-buck/               rc5t583-gpio/              timb-gpio/                 
efi-framebuffer/           lp8788-dldo/               reg-dummy/                 tps6586x-gpio/             
ehci-platform/             lp_gpio/                   serial8250/                tps65910-gpio/             
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ ls /sys/bus/platform/drivers/character_device+driver_p/ -l
total 0
--w------- 1 root root 4096 May 21 22:42 bind
lrwxrwxrwx 1 root root    0 May 21 22:42 character_device+driver_p -> ../../../../devices/platform/character_device+driver_p
lrwxrwxrwx 1 root root    0 May 21 22:42 module -> ../../../../module/character_driver_p
--w------- 1 root root 4096 May 21 22:41 uevent
--w------- 1 root root 4096 May 21 22:42 unbind
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ ls /sys/bus/platform/devices/character_device+driver_p -l
lrwxrwxrwx 1 root root 0 May 21 22:36 /sys/bus/platform/devices/character_device+driver_p -> ../../../devices/platform/character_device+driver_p
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ ls /sys/bus/platform/devices/character_device+driver_p/
driver/    modalias   power/     subsystem/ uevent     
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ ls /sys/bus/platform/devices/character_device+driver_p/ -l
total 0
lrwxrwxrwx 1 root root    0 May 21 22:42 driver -> ../../../bus/platform/drivers/character_device+driver_p
-r--r--r-- 1 root root 4096 May 21 22:36 modalias
drwxr-xr-x 2 root root    0 May 21 22:36 power
lrwxrwxrwx 1 root root    0 May 21 22:36 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 May 21 22:36 uevent
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 


```

```
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ dmesg |grep character
[ 5193.013128] character_device_p: module verification failed: signature and/or  required key missing - tainting kernel
[ 5193.013626] [character_device_p] character_device_p_init sucess
[ 5515.562513] [character_driver_p] character_driver_p_probe sucess
[ 5515.562542] [character_driver_p] character_driver_p_init sucess
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 

 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ tail /var/log/kern.log -n 5
May 21 21:11:47 ubuntu kernel: [  135.525588] type=1400 audit(1653138707.726:74): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/usr/lib/telepathy/telepathy-*" pid=2957 comm="apparmor_parser"
May 21 22:36:03 ubuntu kernel: [ 5193.013128] character_device_p: module verification failed: signature and/or  required key missing - tainting kernel
May 21 22:36:03 ubuntu kernel: [ 5193.013626] [character_device_p] character_device_p_init sucess
May 21 22:41:25 ubuntu kernel: [ 5515.562513] [character_driver_p] character_driver_p_probe sucess
May 21 22:41:25 ubuntu kernel: [ 5515.562542] [character_driver_p] character_driver_p_init sucess
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 


wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ lsmod 
Module                  Size  Used by
character_driver_p     12702  0 
character_device_p     12442  0 


wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ tail /var/log/kern.log -n 50 |grep char
May 21 22:36:03 ubuntu kernel: [ 5193.013128] character_device_p: module verification failed: signature and/or  required key missing - tainting kernel
May 21 22:36:03 ubuntu kernel: [ 5193.013626] [character_device_p] character_device_p_init sucess
May 21 22:41:25 ubuntu kernel: [ 5515.562513] [character_driver_p] character_driver_p_probe sucess
May 21 22:41:25 ubuntu kernel: [ 5515.562542] [character_driver_p] character_driver_p_init sucess
May 21 22:49:10 ubuntu kernel: [ 5980.299326] [character_driver_p] character_driver_p_remove sucess
May 21 22:49:10 ubuntu kernel: [ 5980.299352] [character_driver_p] character_driver_p_exit sucess
May 21 22:49:15 ubuntu kernel: [ 5985.559888] Device 'character_device+driver_p' does not have a release() function, it is broken and must be fixed.
May 21 22:49:15 ubuntu kernel: [ 5985.559891] Modules linked in: character_device_p(OF-) hid_generic usbhid hid psmouse ahci mptspi pcnet32 mptscsih libahci mii mptbase vmw_pvscsi floppy vmxnet3 [last unloaded: character_driver_p]
May 21 22:49:15 ubuntu kernel: [ 5985.559949]  [<f893700e>] character_device_p_exit+0xe/0x1000 [character_device_p]
May 21 22:49:15 ubuntu kernel: [ 5985.559968] [character_device_p] character_device_p_exit sucess
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 

```

```

wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ tail /var/log/kern.log -n 37
May 21 21:11:47 ubuntu kernel: [  135.525588] type=1400 audit(1653138707.726:74): apparmor="STATUS" operation="profile_replace" profile="unconfined" name="/usr/lib/telepathy/telepathy-*" pid=2957 comm="apparmor_parser"
May 21 22:36:03 ubuntu kernel: [ 5193.013128] character_device_p: module verification failed: signature and/or  required key missing - tainting kernel
May 21 22:36:03 ubuntu kernel: [ 5193.013626] [character_device_p] character_device_p_init sucess
May 21 22:41:25 ubuntu kernel: [ 5515.562513] [character_driver_p] character_driver_p_probe sucess
May 21 22:41:25 ubuntu kernel: [ 5515.562542] [character_driver_p] character_driver_p_init sucess
May 21 22:49:10 ubuntu kernel: [ 5980.299326] [character_driver_p] character_driver_p_remove sucess
May 21 22:49:10 ubuntu kernel: [ 5980.299352] [character_driver_p] character_driver_p_exit sucess
May 21 22:49:15 ubuntu kernel: [ 5985.559870] ------------[ cut here ]------------
May 21 22:49:15 ubuntu kernel: [ 5985.559887] WARNING: CPU: 5 PID: 4559 at /build/buildd/linux-3.13.0/drivers/base/core.c:251 device_release+0x86/0x90()
May 21 22:49:15 ubuntu kernel: [ 5985.559888] Device 'character_device+driver_p' does not have a release() function, it is broken and must be fixed.
May 21 22:49:15 ubuntu kernel: [ 5985.559891] Modules linked in: character_device_p(OF-) hid_generic usbhid hid psmouse ahci mptspi pcnet32 mptscsih libahci mii mptbase vmw_pvscsi floppy vmxnet3 [last unloaded: character_driver_p]
May 21 22:49:15 ubuntu kernel: [ 5985.559904] CPU: 5 PID: 4559 Comm: rmmod Tainted: GF          O 3.13.0-32-generic #57-Ubuntu
May 21 22:49:15 ubuntu kernel: [ 5985.559905] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 07/31/2013
May 21 22:49:15 ubuntu kernel: [ 5985.559906]  00000000 00000000 e396fe64 c1650cd3 e396fea4 e396fe94 c10567ee c187b74c
May 21 22:49:15 ubuntu kernel: [ 5985.559909]  e396fec0 000011cf c187b6ec 000000fb c1407566 c1407566 f8939014 f893900c
May 21 22:49:15 ubuntu kernel: [ 5985.559911]  eda616c0 e396feac c1056843 00000009 e396fea4 c187b74c e396fec0 e396fed0
May 21 22:49:15 ubuntu kernel: [ 5985.559914] Call Trace:
May 21 22:49:15 ubuntu kernel: [ 5985.559920]  [<c1650cd3>] dump_stack+0x41/0x52
May 21 22:49:15 ubuntu kernel: [ 5985.559927]  [<c10567ee>] warn_slowpath_common+0x7e/0xa0
May 21 22:49:15 ubuntu kernel: [ 5985.559928]  [<c1407566>] ? device_release+0x86/0x90
May 21 22:49:15 ubuntu kernel: [ 5985.559930]  [<c1407566>] ? device_release+0x86/0x90
May 21 22:49:15 ubuntu kernel: [ 5985.559932]  [<c1056843>] warn_slowpath_fmt+0x33/0x40
May 21 22:49:15 ubuntu kernel: [ 5985.559933]  [<c1407566>] device_release+0x86/0x90
May 21 22:49:15 ubuntu kernel: [ 5985.559939]  [<c12f239f>] kobject_cleanup+0x6f/0x1a0
May 21 22:49:15 ubuntu kernel: [ 5985.559940]  [<c12f22df>] ? kobj_kset_leave+0x3f/0x50
May 21 22:49:15 ubuntu kernel: [ 5985.559942]  [<c12f2265>] kobject_put+0x25/0x60
May 21 22:49:15 ubuntu kernel: [ 5985.559944]  [<c140d1a8>] ? platform_device_del+0x18/0x90
May 21 22:49:15 ubuntu kernel: [ 5985.559945]  [<c14077a4>] put_device+0x14/0x20
May 21 22:49:15 ubuntu kernel: [ 5985.559947]  [<c140d23c>] platform_device_unregister+0x1c/0x20
May 21 22:49:15 ubuntu kernel: [ 5985.559949]  [<f893700e>] character_device_p_exit+0xe/0x1000 [character_device_p]
May 21 22:49:15 ubuntu kernel: [ 5985.559950]  [<f8937000>] ? 0xf8936fff
May 21 22:49:15 ubuntu kernel: [ 5985.559954]  [<c10c21e8>] SyS_delete_module+0x148/0x1e0
May 21 22:49:15 ubuntu kernel: [ 5985.559959]  [<c117a75d>] ? ____fput+0xd/0x10
May 21 22:49:15 ubuntu kernel: [ 5985.559963]  [<c107239e>] ? task_work_run+0x7e/0xb0
May 21 22:49:15 ubuntu kernel: [ 5985.559966]  [<c165efcd>] sysenter_do_call+0x12/0x28
May 21 22:49:15 ubuntu kernel: [ 5985.559967] ---[ end trace dd3d09301a9bc7cd ]---
May 21 22:49:15 ubuntu kernel: [ 5985.559968] [character_device_p] character_device_p_exit sucess
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 

```

test 6.misc-device-driver not WARNING: 
```
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ cd ../../2.Layered-thinking/6.misc-device-driver/
1.misc-platform_device/ 2.misc-platform_driver/ 
wu-being@ubuntu:~/.../1.Platform-device-driver/2.Character-driver$ cd ../../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device/
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device$ ls
Makefile  misc-platform_device.c  misc-platform_device.ko  readme.md
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device$ sudo insmod misc-platform_device.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/1.misc-platform_device$ cd ../2.misc-platform_driver/
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ ls
Makefile  misc-platform_driver.c  misc-platform_driver.ko  readme.md
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ sudo insmod misc-platform_driver.ko 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ lsmod 
Module                  Size  Used by
misc_platform_driver    12578  0 
misc_platform_device    12499  0 
hid_generic            12492  0 
usbhid                 46997  0 
hid                    87604  2 hid_generic,usbhid
psmouse                91329  0 
ahci                   25579  0 
mptspi                 22158  2 
pcnet32                36539  0 
mptscsih               38998  1 mptspi
libahci                27082  1 ahci
mii                    13654  1 pcnet32
mptbase                95810  2 mptspi,mptscsih
vmw_pvscsi             22359  0 
floppy                 55416  0 
vmxnet3                48743  0 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ sudo rmmod misc_platform_driver 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ sudo rmmod misc_platform_device 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ dmesg |grep misc
[ 6622.191122] [misc_platform_device] misc_platform_device_init sucess
[ 6636.610635] [misc_platform_driver] misc_platform_driver_probe sucess
[ 6659.734198] [misc_platform_driver] misc_platform_driver_remove sucess
[ 6664.256510] [misc_platform_device] misc_platform_device_exit sucess
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ tail /var/log/kern.log -n10
May 21 22:49:15 ubuntu kernel: [ 5985.559954]  [<c10c21e8>] SyS_delete_module+0x148/0x1e0
May 21 22:49:15 ubuntu kernel: [ 5985.559959]  [<c117a75d>] ? ____fput+0xd/0x10
May 21 22:49:15 ubuntu kernel: [ 5985.559963]  [<c107239e>] ? task_work_run+0x7e/0xb0
May 21 22:49:15 ubuntu kernel: [ 5985.559966]  [<c165efcd>] sysenter_do_call+0x12/0x28
May 21 22:49:15 ubuntu kernel: [ 5985.559967] ---[ end trace dd3d09301a9bc7cd ]---
May 21 22:49:15 ubuntu kernel: [ 5985.559968] [character_device_p] character_device_p_exit sucess
May 21 22:59:52 ubuntu kernel: [ 6622.191122] [misc_platform_device] misc_platform_device_init sucess
May 21 23:00:06 ubuntu kernel: [ 6636.610635] [misc_platform_driver] misc_platform_driver_probe sucess
May 21 23:00:29 ubuntu kernel: [ 6659.734198] [misc_platform_driver] misc_platform_driver_remove sucess
May 21 23:00:34 ubuntu kernel: [ 6664.256510] [misc_platform_device] misc_platform_device_exit sucess
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ 
wu-being@ubuntu:~/.../2.Layered-thinking/6.misc-device-driver/2.misc-platform_driver$ 

```

Becase: 

The platform_device_alloc of 6.misc-device-driver misc_platform_device have platform_device_release;

```c
371  /**
372   * platform_device_alloc - create a platform device
373   * @name: base name of the device we're adding
374   * @id: instance id
375   *
376   * Create a platform device object which can have other objects attached
377   * to it, and which will have attached objects freed when it is released.
378   */
379  struct platform_device *platform_device_alloc(const char *name, int id)
380  {
381  	struct platform_object *pa;
382  
383  	pa = kzalloc(sizeof(*pa) + strlen(name) + 1, GFP_KERNEL);
384  	if (pa) {
385  		strcpy(pa->name, name);
386  		pa->pdev.name = pa->name;
387  		pa->pdev.id = id;
388  		device_initialize(&pa->pdev.dev);
389  		pa->pdev.dev.release = platform_device_release;
390  		setup_pdev_dma_masks(&pa->pdev);
391  	}
392  
393  	return pa ? &pa->pdev : NULL;
394  }
395  EXPORT_SYMBOL_GPL(platform_device_alloc);
```

