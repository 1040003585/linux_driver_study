
```

 make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/xxx_driver.o
  CC [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/task.o
  LD [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/xxx_charger.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/xxx_charger.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work/xxx_charger.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ sudo insmod xxx_charger.ko 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ dmesg |grep work
[  431.777901] [work_device_p] work_device_p_init sucess
[ 3627.928834] [work_driver] xxx_driver_init.
[ 3627.928865] [work_driver] xxx_driver_probe.
[ 3629.932329] [work_driver] usb_charger_work.10
[ 3630.932479] [work_driver] usb_charger_work.10
[ 3631.932841] [work_driver] usb_charger_work.10
[ 3632.933324] [work_driver] usb_charger_work.10
[ 3632.937415] [work_driver] work_charging_monitor.
[ 3633.933962] [work_driver] usb_charger_work.10
[ 3634.934340] [work_driver] usb_charger_work.10
[ 3635.934717] [work_driver] usb_charger_work.10
[ 3636.935143] [work_driver] usb_charger_work.10
[ 3637.935308] [work_driver] usb_charger_work.10
[ 3637.947308] [work_driver] work_charging_monitor.
[ 3638.935535] [work_driver] usb_charger_work.10
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$


wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ ls /sys/devices/platform/work_device+driver_p/ -l
total 0
lrwxrwxrwx 1 root root    0 Jun 11 13:39 driver -> ../../../bus/platform/drivers/work_device+driver_p
-r--r--r-- 1 root root 4096 Jun 11 12:46 modalias
drwxr-xr-x 2 root root    0 Jun 11 12:46 power
lrwxrwxrwx 1 root root    0 Jun 11 12:46 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 Jun 11 12:45 uevent
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ ls /sys/bus/platform/drivers/ -l

wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ ls /sys/bus/platform/drivers/work_device+driver_p/ -l
total 0
--w------- 1 root root 4096 Jun 11 13:40 bind
lrwxrwxrwx 1 root root    0 Jun 11 13:40 module -> ../../../../module/xxx_charger
--w------- 1 root root 4096 Jun 11 13:38 uevent
--w------- 1 root root 4096 Jun 11 13:40 unbind
lrwxrwxrwx 1 root root    0 Jun 11 13:40 work_device+driver_p -> ../../../../devices/platform/work_device+driver_p
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ 



wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/3.xxx_charger_work$ dmesg |grep work
...
[ 3802.999690] [work_driver] usb_charger_work.10
[ 3803.272127] [work_driver] work_charging_monitor.
[ 3804.000165] [work_driver] usb_charger_work.10
[ 3805.000718] [work_driver] usb_charger_work.10
[ 3806.000728] [work_driver] usb_charger_work.10
[ 3807.001386] [work_driver] usb_charger_work.10
[ 3808.112850] [work_driver] usb_charger_work.10
[ 3808.315457] [work_driver] work_charging_monitor.
[ 3809.110066] [work_driver] usb_charger_work.10
[ 3810.110711] [work_driver] usb_charger_work.10
[ 3810.285439] [work_driver] xxx_driver_suspend.
[ 3812.971576] [work_driver] xxx_driver_resume.
[ 3815.975748] [work_driver] usb_charger_work.10
[ 3816.976091] [work_driver] usb_charger_work.10
[ 3817.976549] [work_driver] usb_charger_work.10
[ 3817.976551] [work_driver] work_charging_monitor.
[ 3818.976691] [work_driver] usb_charger_work.10
[ 3819.977086] [work_driver] usb_charger_work.10
[ 3820.977757] [work_driver] usb_charger_work.10
[ 3821.978179] [work_driver] usb_charger_work.10
[ 3822.978404] [work_driver] usb_charger_work.10
[ 3822.986404] [work_driver] work_charging_monitor.
[ 3823.978875] [work_driver] usb_charger_work.10
[ 3824.979279] [work_driver] usb_charger_work.10
[ 3825.979485] [work_driver] usb_charger_work.10
[ 3826.979216] [work_driver] usb_charger_work.10
[ 3827.979118] [work_driver] usb_charger_work.10
[ 3827.995170] [work_driver] work_charging_monitor.
[ 3828.978988] [work_driver] usb_charger_work.10
[ 3829.979118] [work_driver] usb_charger_work.10
[ 3830.979008] [work_driver] usb_charger_work.10
[ 3831.978599] [work_driver] usb_charger_work.10
[ 3832.978666] [work_driver] usb_charger_work.10
[ 3833.002667] [work_driver] work_charging_monitor.

```
