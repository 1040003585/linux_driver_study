wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/main_module$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  LD      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module/built-in.o
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module/sub_module.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module/sub_module.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module/sub_module.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/main_module$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/main_module$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/main_module$ 

wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ sudo insmod sub_module.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ lsmod |grep module
sub_module             12398  0 
main_module            12399  0 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ dmesg |grep module
[   14.044754] brd: module loaded
[   14.045883] loop: module loaded
[ 7441.540885] main_module: module license 'unspecified' taints kernel.
[ 7441.541051] main_module: module verification failed: signature and/or  required key missing - tainting kernel
[ 7441.541968] main_module_init sucess
[ 7644.223891] sub_module_init sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--request_module/1.main-sub-module/sub_module$ 

