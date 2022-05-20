

```c
static struct platform_driver misc_platform_driver = {
	.driver = {
		.name  = "misc_platform_driver-name",
		//.name  = "misc_platform_device+driver-name",
		.owner = THIS_MODULE,
	},
	.probe = misc_platform_driver_probe,
	.remove = misc_platform_driver_remove,
};

```
log: 

```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver/misc-platform_driver.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver/misc-platform_driver.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver/misc-platform_driver.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ sudo insmod misc-platform_driver.ko 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ lsmod |grep misc
misc_platform_driver    12578  0 
misc_platform_device    12499  0 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 


wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /dev/ -l |grep misc
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 


```
```

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/drivers/misc_platform_driver-name/
bind  module  uevent  unbind
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/drivers/misc_platform_driver-name/ -l
total 0
--w------- 1 root root 4096 May 20 16:47 bind
lrwxrwxrwx 1 root root    0 May 20 16:47 module -> ../../../../module/misc_platform_driver
--w------- 1 root root 4096 May 20 16:43 uevent
--w------- 1 root root 4096 May 20 16:47 unbind


wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 


wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/module/misc_platform_d
misc_platform_device/ misc_platform_driver/ 

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/module/misc_platform_device/
coresize    holders/    initsize    initstate   notes/      refcnt      sections/   srcversion  taint       uevent      
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/module/misc_platform_device/


wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/drivers/
88pm860x-regulator/        floppy/                    lp_gpio/                   rc5t583-gpio/              tc3589x-gpio/              xgene-rtc/
alarmtimer/                i8042/                     mdio-gpio/                 reg-dummy/                 timb-gpio/                 xhci-hcd/
byt_gpio/                  intel_msic/                misc_platform_driver-name/ serial8250/                tps6586x-gpio/             
charger-manager/           ipmi/                      msic_gpio/                 simple-framebuffer/        tps65910-gpio/             
clk-lpt/                   lp8788-aldo/               ohci-platform/             sram/                      uart-sccnxp/               
efi-framebuffer/           lp8788-buck/               palmas-gpio/               stmpe-gpio/                vesa-framebuffer/          
ehci-platform/             lp8788-dldo/               pmic_gpio/                 syscon/                    virtio-mmio/               
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/devices/
alarmtimer/                       floppy.0/                         misc_platform_device+driver-name/ reg-dummy/
eisa.0/                           i8042/                            pcspkr/                           serial8250/
Fixed MDIO bus.0/                 microcode/                        platform-framebuffer.0/           
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/devices/



```




```c
static struct platform_driver misc_platform_driver = {
	.driver = {
		//.name  = "misc_platform_driver-name",
		.name  = "misc_platform_device+driver-name",
		.owner = THIS_MODULE,
	},
	.probe = misc_platform_driver_probe,
	.remove = misc_platform_driver_remove,
};

```
log: 

```

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver/misc-platform_driver.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver/misc-platform_driver.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver/misc-platform_driver.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ sudo insmod misc-platform_driver.ko 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 


```
```

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/drivers/misc_platform_device+driver-name/ -l
total 0
--w------- 1 root root 4096 May 20 17:04 bind
lrwxrwxrwx 1 root root    0 May 20 17:04 misc_platform_device+driver-name -> ../../../../devices/platform/misc_platform_device+driver-name
lrwxrwxrwx 1 root root    0 May 20 17:04 module -> ../../../../module/misc_platform_driver
--w------- 1 root root 4096 May 20 17:03 uevent
--w------- 1 root root 4096 May 20 17:04 unbind
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ sudo rmmod misc_platform_driver 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ sudo rmmod misc_platform_device 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ sudo dmesg -c |grep misc_platform
[56653.893153] [misc_platform_driver] misc_platform_driver_probe sucess
[56765.199836] [misc_platform_driver] misc_platform_driver_remove sucess
[56773.580216] [misc_platform_device] misc_platform_device_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 


```
```

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ sudo insmod misc-platform_driver.ko 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/
devices/           drivers/           drivers_autoprobe  drivers_probe      uevent             
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/drivers/
88pm860x-regulator/               ipmi/                             pmic_gpio/                        tps6586x-gpio/
alarmtimer/                       lp8788-aldo/                      rc5t583-gpio/                     tps65910-gpio/
byt_gpio/                         lp8788-buck/                      reg-dummy/                        uart-sccnxp/
charger-manager/                  lp8788-dldo/                      serial8250/                       vesa-framebuffer/
clk-lpt/                          lp_gpio/                          simple-framebuffer/               virtio-mmio/
efi-framebuffer/                  mdio-gpio/                        sram/                             xgene-rtc/
ehci-platform/                    misc_platform_device+driver-name/ stmpe-gpio/                       xhci-hcd/
floppy/                           msic_gpio/                        syscon/                           
i8042/                            ohci-platform/                    tc3589x-gpio/                     
intel_msic/                       palmas-gpio/                      timb-gpio/                        
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/devices/
alarmtimer/             Fixed MDIO bus.0/       i8042/                  pcspkr/                 reg-dummy/              
eisa.0/                 floppy.0/               microcode/              platform-framebuffer.0/ serial8250/             
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/drivers/misc_platform_device+driver-name/
bind    module/ uevent  unbind  
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/bus/platform/drivers/misc_platform_device+driver-name/ -l
total 0
--w------- 1 root root 4096 May 20 17:08 bind
lrwxrwxrwx 1 root root    0 May 20 17:09 misc_platform_device+driver-name -> ../../../../devices/platform/misc_platform_device+driver-name
lrwxrwxrwx 1 root root    0 May 20 17:08 module -> ../../../../module/misc_platform_driver
--w------- 1 root root 4096 May 20 17:07 uevent
--w------- 1 root root 4096 May 20 17:08 unbind
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 


```
```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /dev/ |grep misc
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ sudo insmod ../2.misc-platform_device/misc-platform_device.ko 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /sys/devices/platform/misc_platform_device+driver-name/ -l
total 0
lrwxrwxrwx 1 root root    0 May 20 17:08 driver -> ../../../bus/platform/drivers/misc_platform_device+driver-name
-r--r--r-- 1 root root 4096 May 20 17:18 modalias
drwxr-xr-x 2 root root    0 May 20 17:18 power
lrwxrwxrwx 1 root root    0 May 20 17:18 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 May 20 17:08 uevent
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ ls /dev/ |grep misc
misc_platform_driver_NAME
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ sudo dmesg  |grep misc_platform
[56975.899434] [misc_platform_driver] misc_platform_driver_probe sucess
[56975.899449] [misc_platform_device] misc_platform_device_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/1.misc-platform_driver$ 



```


