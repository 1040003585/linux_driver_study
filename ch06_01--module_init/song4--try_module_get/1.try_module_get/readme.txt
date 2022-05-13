wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get/try_module_get.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get/try_module_get.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get/try_module_get.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ sudo insmod try_module_get.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ dmesg |grep try_module_get
[ 4653.616593] try_module_get: module license 'unspecified' taints kernel.
[ 4653.617051] try_module_get_init sucess
[ 4653.617052] try_module_get: 1
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ sudo rmmod try_module_get
rmmod: ERROR: Module try_module_get is in use
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/try_module_get$ 

