```
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device/work_device_p.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device/work_device_p.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device/work_device_p.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ sudo insmod work_device_p.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ ls /sys/bus/platform/drivers/
88pm860x-regulator  clk-lpt          i8042        lp8788-buck  msic_gpio      rc5t583-gpio        sram          timb-gpio      vesa-framebuffer
alarmtimer          efi-framebuffer  intel_msic   lp8788-dldo  ohci-platform  reg-dummy           stmpe-gpio    tps6586x-gpio  virtio-mmio
byt_gpio            ehci-platform    ipmi         lp_gpio      palmas-gpio    serial8250          syscon        tps65910-gpio  xgene-rtc
charger-manager     floppy           lp8788-aldo  mdio-gpio    pmic_gpio      simple-framebuffer  tc3589x-gpio  uart-sccnxp    xhci-hcd
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ ls /sys/bus/platform/devices/
alarmtimer  eisa.0  Fixed MDIO bus.0  floppy.0  i8042  microcode  pcspkr  platform-framebuffer.0  reg-dummy  serial8250  work_device+driver_p
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ ls /sys/bus/platform/devices/ -ltotal 0
lrwxrwxrwx 1 root root 0 Jun 11 12:38 alarmtimer -> ../../../devices/platform/alarmtimer
lrwxrwxrwx 1 root root 0 Jun 11 12:38 eisa.0 -> ../../../devices/platform/eisa.0
lrwxrwxrwx 1 root root 0 Jun 11 12:38 Fixed MDIO bus.0 -> ../../../devices/platform/Fixed MDIO bus.0
lrwxrwxrwx 1 root root 0 Jun 11 12:38 floppy.0 -> ../../../devices/platform/floppy.0
lrwxrwxrwx 1 root root 0 Jun 11 12:38 i8042 -> ../../../devices/platform/i8042
lrwxrwxrwx 1 root root 0 Jun 11 12:38 microcode -> ../../../devices/platform/microcode
lrwxrwxrwx 1 root root 0 Jun 11 12:38 pcspkr -> ../../../devices/platform/pcspkr
lrwxrwxrwx 1 root root 0 Jun 11 12:38 platform-framebuffer.0 -> ../../../devices/platform/platform-framebuffer.0
lrwxrwxrwx 1 root root 0 Jun 11 12:38 reg-dummy -> ../../../devices/platform/reg-dummy
lrwxrwxrwx 1 root root 0 Jun 11 12:38 serial8250 -> ../../../devices/platform/serial8250
lrwxrwxrwx 1 root root 0 Jun 11 12:45 work_device+driver_p -> ../../../devices/platform/work_device+driver_p
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ ls /sys/devices/platform/ -l
total 0
drwxr-xr-x 3 root root    0 Jun 11 12:38 alarmtimer
drwxr-xr-x 3 root root    0 Jun 11 12:38 eisa.0
drwxr-xr-x 4 root root    0 Jun 11 12:38 Fixed MDIO bus.0
drwxr-xr-x 4 root root    0 Jun 11 12:38 floppy.0
drwxr-xr-x 5 root root    0 Jun 11 12:38 i8042
drwxr-xr-x 3 root root    0 Jun 11 12:38 microcode
drwxr-xr-x 3 root root    0 Jun 11 12:38 pcspkr
drwxr-xr-x 3 root root    0 Jun 11 12:38 platform-framebuffer.0
drwxr-xr-x 2 root root    0 Jun 11 12:46 power
drwxr-xr-x 4 root root    0 Jun 11 12:38 reg-dummy
drwxr-xr-x 4 root root    0 Jun 11 12:38 serial8250
-rw-r--r-- 1 root root 4096 Jun 11 12:38 uevent
drwxr-xr-x 3 root root    0 Jun 11 12:45 work_device+driver_p
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ ls /sys/devices/platform/work_device+driver_p/ -l
total 0
-r--r--r-- 1 root root 4096 Jun 11 12:46 modalias
drwxr-xr-x 2 root root    0 Jun 11 12:46 power
lrwxrwxrwx 1 root root    0 Jun 11 12:46 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 Jun 11 12:45 uevent
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ 

wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ make clean 
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device              clean 
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CLEAN   /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device/.tmp_versions
  CLEAN   /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device/Module.symvers
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/device$ 

```

