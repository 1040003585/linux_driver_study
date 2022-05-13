wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2/try_module_get2.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2/try_module_get2.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2/try_module_get2.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ sudo insmod try_module_get2.ko 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ sudo rmmod try_module_get2.ko 
rmmod: ERROR: Module try_module_get2 is in use
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/3.try_module_get2$ 

