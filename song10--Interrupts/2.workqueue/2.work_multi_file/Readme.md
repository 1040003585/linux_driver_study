
```
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file/work.o
  CC [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file/task.o
  LD [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file/work_task.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file/work_task.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file/work_task.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ ls
Makefile       Module.symvers  task.c  work.c  work.o        work_task.mod.c  work_task.o
modules.order  Readme.md       task.o  work.h  work_task.ko  work_task.mod.o
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ sudo insmod work_task.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ sudo rmmod work_task 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ 
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ dmesg |grep work
[ 5718.285405] [work] work_init.
[ 5720.289316] [work] work_usb.10
[ 5721.289471] [work] work_usb.10
[ 5722.289698] [work] work_usb.10
[ 5723.290366] [work] work_usb.10
[ 5724.290866] [work] work_usb.10
[ 5725.291215] [work] work_usb.10
[ 5726.291286] [work] work_usb.10
[ 5727.291787] [work] work_usb.10
[ 5728.292271] [work] work_usb.10
[ 5728.620947] [work] work_exit.
wu-being@ubuntu:~/code/linux_driver_study/song10--Interrupts/2.workqueue/2.work_multi_file$ 


```
