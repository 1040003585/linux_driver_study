 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client/try_module_get_client.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client/try_module_get_client.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client/try_module_get_client.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ sudo insmod try_module_get_client.ko 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ dmesg |grep try_module_get_client
[ 1599.493393] [try_module_get_client]try_module_get_client_init sucess
[ 1908.818581] [try_module_get_client]try_module_get_client_exit sucess
[ 1924.077324] [try_module_get_client]try_module_get_client_init sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ ls /dev/ |grep try_module_get_client.
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ ls /dev/ |grep try_module
try_module_get_at_device
try_module_get_client
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/client$ 

