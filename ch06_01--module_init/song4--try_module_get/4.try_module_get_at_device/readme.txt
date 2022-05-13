wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
 wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device/try_module_get_at_device.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device/try_module_get_at_device.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device/try_module_get_at_device.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 

wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ sudo insmod try_module_get_at_device.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ ls /dev/ -l |grep try
crw-------  1 root root     10,  57 May 12 09:27 try_module_get_at_device
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ dmesg |grep try_module_get_at_device
[  202.406032] try_module_get_at_device: module license 'unspecified' taints kernel.
[  202.406051] try_module_get_at_device: module verification failed: signature and/or  required key missing - tainting kernel
[  202.406501] [try_module_get_at_device]try_module_get: 1
[  202.406571] [try_module_get_at_device]try_module_get_at_device_init sucess
[  202.406571] [try_module_get_at_device]module_put:misc.fops->owner
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ sudo rmmod try_module_get_at_device 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ dmesg |grep try_module_get_at_device
[  202.406032] try_module_get_at_device: module license 'unspecified' taints kernel.
[  202.406051] try_module_get_at_device: module verification failed: signature and/or  required key missing - tainting kernel
[  202.406501] [try_module_get_at_device]try_module_get: 1
[  202.406571] [try_module_get_at_device]try_module_get_at_device_init sucess
[  202.406571] [try_module_get_at_device]module_put:misc.fops->owner
[  325.774562] [try_module_get_at_device]try_module_get_at_device_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/4.try_module_get_at_device$ 

