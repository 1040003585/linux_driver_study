
build error:
```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.o
/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.c: In function ‘misc_platform_device_init’:
/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.c:18:2: error: implicit declaration of function ‘platform_device_alloc’ [-Werror=implicit-function-declaration]
  pdev = platform_device_alloc("misc_platform_device-name", -1);
  ^
/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.c:18:7: warning: assignment makes pointer from integer without a cast [enabled by default]
  pdev = platform_device_alloc("misc_platform_device-name", -1);
       ^
/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.c:22:2: error: implicit declaration of function ‘platform_device_add’ [-Werror=implicit-function-declaration]
  ret = platform_device_add(pdev);
  ^
/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.c:24:3: error: implicit declaration of function ‘platform_device_put’ [-Werror=implicit-function-declaration]
   platform_device_put(pdev);
   ^
/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.c: In function ‘misc_platform_device_exit’:
/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.c:34:2: error: implicit declaration of function ‘platform_device_unregister’ [-Werror=implicit-function-declaration]
  platform_device_unregister(pdev);
  ^
cc1: some warnings being treated as errors
make[1]: *** [/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.o] Error 1
make: *** [_module_/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device] Error 2
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 

```

add :

```c
#include <linux/platform_device.h>
```

insmod error:

```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ sudo insmod misc-platform_device.ko 
insmod: ERROR: could not insert module misc-platform_device.ko: Unknown symbol in module
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
```

add :

```c

MODULE_LICENSE("GPL");
```

build pass:
```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device/misc-platform_device.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
```


```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ sudo insmod misc-platform_device.ko 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
```


test log:

```

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/
block/      bus/        class/      dev/        devices/    firmware/   fs/         hypervisor/ kernel/     module/     power/      

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/devices/
breakpoint/  LNXSYSTM:00/ platform/    pnp1/        software/    tracepoint/  
isa/         pci0000:00/  pnp0/        rapidio/     system/      virtual/   
  
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/dev/
block/ char/  


```
```

wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/devices/platform/ -l
total 0
drwxr-xr-x 3 root root    0 May 20 01:19 alarmtimer
drwxr-xr-x 3 root root    0 May 20 01:19 eisa.0
drwxr-xr-x 4 root root    0 May 20 01:19 Fixed MDIO bus.0
drwxr-xr-x 4 root root    0 May 20 01:19 floppy.0
drwxr-xr-x 5 root root    0 May 20 01:19 i8042
drwxr-xr-x 3 root root    0 May 20 01:19 microcode
drwxr-xr-x 3 root root    0 May 20 14:58 misc_platform_device-name
drwxr-xr-x 3 root root    0 May 20 01:19 pcspkr
drwxr-xr-x 3 root root    0 May 20 01:19 platform-framebuffer.0
drwxr-xr-x 2 root root    0 May 20 14:53 power
drwxr-xr-x 4 root root    0 May 20 01:19 reg-dummy
drwxr-xr-x 4 root root    0 May 20 01:19 serial8250
-rw-r--r-- 1 root root 4096 May 20 01:19 uevent
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/devices/platform/misc_platform_device-name/ -l
total 0
-r--r--r-- 1 root root 4096 May 20 15:02 modalias
drwxr-xr-x 2 root root    0 May 20 15:02 power
lrwxrwxrwx 1 root root    0 May 20 15:02 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 May 20 14:58 uevent
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 


```
```


wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/bus/platform/
devices/           drivers/           drivers_autoprobe  drivers_probe      uevent             
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/bus/platform/drivers
drivers/           drivers_autoprobe  drivers_probe      
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/bus/platform/drivers/
88pm860x-regulator/ ehci-platform/      lp8788-buck/        palmas-gpio/        sram/               tps65910-gpio/      
alarmtimer/         floppy/             lp8788-dldo/        pmic_gpio/          stmpe-gpio/         uart-sccnxp/        
byt_gpio/           i8042/              lp_gpio/            rc5t583-gpio/       syscon/             vesa-framebuffer/   
charger-manager/    intel_msic/         mdio-gpio/          reg-dummy/          tc3589x-gpio/       virtio-mmio/        
clk-lpt/            ipmi/               msic_gpio/          serial8250/         timb-gpio/          xgene-rtc/          
efi-framebuffer/    lp8788-aldo/        ohci-platform/      simple-framebuffer/ tps6586x-gpio/      xhci-hcd/           
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/bus/platform/devices/
alarmtimer/                floppy.0/                  misc_platform_device-name/ reg-dummy/                 
eisa.0/                    i8042/                     pcspkr/                    serial8250/                
Fixed MDIO bus.0/          microcode/                 platform-framebuffer.0/    

```
```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/bus/platform/drivers -l
total 0
drwxr-xr-x 2 root root 0 May 20 14:50 88pm860x-regulator
drwxr-xr-x 2 root root 0 May 20 14:50 alarmtimer
drwxr-xr-x 2 root root 0 May 20 14:50 byt_gpio
drwxr-xr-x 2 root root 0 May 20 14:50 charger-manager
drwxr-xr-x 2 root root 0 May 20 14:50 clk-lpt
drwxr-xr-x 2 root root 0 May 20 14:50 efi-framebuffer
drwxr-xr-x 2 root root 0 May 20 14:50 ehci-platform
drwxr-xr-x 2 root root 0 May 20 01:19 floppy
drwxr-xr-x 2 root root 0 May 20 14:50 i8042
drwxr-xr-x 2 root root 0 May 20 14:50 intel_msic
drwxr-xr-x 2 root root 0 May 20 14:50 ipmi
drwxr-xr-x 2 root root 0 May 20 14:50 lp8788-aldo
drwxr-xr-x 2 root root 0 May 20 14:50 lp8788-buck
drwxr-xr-x 2 root root 0 May 20 14:50 lp8788-dldo
drwxr-xr-x 2 root root 0 May 20 14:50 lp_gpio
drwxr-xr-x 2 root root 0 May 20 14:50 mdio-gpio
drwxr-xr-x 2 root root 0 May 20 14:50 msic_gpio
drwxr-xr-x 2 root root 0 May 20 14:50 ohci-platform
drwxr-xr-x 2 root root 0 May 20 14:50 palmas-gpio
drwxr-xr-x 2 root root 0 May 20 14:50 pmic_gpio
drwxr-xr-x 2 root root 0 May 20 14:50 rc5t583-gpio
drwxr-xr-x 2 root root 0 May 20 14:50 reg-dummy
drwxr-xr-x 2 root root 0 May 20 14:50 serial8250
drwxr-xr-x 2 root root 0 May 20 14:50 simple-framebuffer
drwxr-xr-x 2 root root 0 May 20 14:50 sram
drwxr-xr-x 2 root root 0 May 20 14:50 stmpe-gpio
drwxr-xr-x 2 root root 0 May 20 14:50 syscon
drwxr-xr-x 2 root root 0 May 20 14:50 tc3589x-gpio
drwxr-xr-x 2 root root 0 May 20 14:50 timb-gpio
drwxr-xr-x 2 root root 0 May 20 14:50 tps6586x-gpio
drwxr-xr-x 2 root root 0 May 20 14:50 tps65910-gpio
drwxr-xr-x 2 root root 0 May 20 14:50 uart-sccnxp
drwxr-xr-x 2 root root 0 May 20 14:50 vesa-framebuffer
drwxr-xr-x 2 root root 0 May 20 14:50 virtio-mmio
drwxr-xr-x 2 root root 0 May 20 14:50 xgene-rtc
drwxr-xr-x 2 root root 0 May 20 14:50 xhci-hcd


```
```
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/bus/platform/devices/ -l 
total 0
lrwxrwxrwx 1 root root 0 May 20 01:19 alarmtimer -> ../../../devices/platform/alarmtimer
lrwxrwxrwx 1 root root 0 May 20 01:19 eisa.0 -> ../../../devices/platform/eisa.0
lrwxrwxrwx 1 root root 0 May 20 01:19 Fixed MDIO bus.0 -> ../../../devices/platform/Fixed MDIO bus.0
lrwxrwxrwx 1 root root 0 May 20 01:19 floppy.0 -> ../../../devices/platform/floppy.0
lrwxrwxrwx 1 root root 0 May 20 01:19 i8042 -> ../../../devices/platform/i8042
lrwxrwxrwx 1 root root 0 May 20 01:19 microcode -> ../../../devices/platform/microcode
lrwxrwxrwx 1 root root 0 May 20 15:03 misc_platform_device-name -> ../../../devices/platform/misc_platform_device-name
lrwxrwxrwx 1 root root 0 May 20 01:19 pcspkr -> ../../../devices/platform/pcspkr
lrwxrwxrwx 1 root root 0 May 20 01:19 platform-framebuffer.0 -> ../../../devices/platform/platform-framebuffer.0
lrwxrwxrwx 1 root root 0 May 20 01:19 reg-dummy -> ../../../devices/platform/reg-dummy
lrwxrwxrwx 1 root root 0 May 20 01:19 serial8250 -> ../../../devices/platform/serial8250
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 


wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/bus/platform/devices/ -l |grep misc
lrwxrwxrwx 1 root root 0 May 20 15:03 misc_platform_device-name -> ../../../devices/platform/misc_platform_device-name


wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ ls /sys/bus/platform/drivers/ -l |grep misc
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 
wu-being@ubuntu:~/code/linux_driver_study/song12--Softwave-Architecture/2.Layered-thinking/6.misc-device-driver/2.misc-platform_device$ 


```


