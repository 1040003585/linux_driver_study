
```
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work/work.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work/work.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work/work.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ sudo dmesg -c|grep work
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ sudo insmod work.ko 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ sudo dmesg -c|grep work
[64501.020978] [work] work_init.
[64503.024781] [work] work_usb.
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ sudo dmesg -c|grep work
[64504.024979] [work] work_usb.
[64505.025368] [work] work_usb.
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ sudo rmmod work 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ sudo dmesg -c|grep work
[64506.026164] [work] work_usb.
[64507.026441] [work] work_usb.
[64508.026904] [work] work_usb.
[64509.027313] [work] work_usb.
[64510.027338] [work] work_usb.
[64510.739615] [work] work_exit.
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ 

wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ make clean 
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work              clean 
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CLEAN   /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work/.tmp_versions
  CLEAN   /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work/Module.symvers
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/1.work$ 

```
