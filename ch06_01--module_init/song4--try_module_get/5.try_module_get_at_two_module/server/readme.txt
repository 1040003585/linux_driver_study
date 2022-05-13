wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server/try_module_get_server.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server/try_module_get_server.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server/try_module_get_server.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ sudo insmod try_module_get_server.ko 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ ls /dev/ |grep try_module_get
try_module_get_at_device
try_module_get_client
try_module_get_server
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ dmesg |grep try_module_get_server
[ 2307.850465] [try_module_get_server]try_module_get at client: 1
[ 2307.850535] [try_module_get_server]try_module_get_server_init sucess 
[ 2307.850536] [try_module_get_server]try_module_get_server_init do something ... 
[ 2307.850537] [try_module_get_server]module_put:misc_client->fops.onwer
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ dmesg |grep try_module_get
[ 1599.493393] [try_module_get_client]try_module_get_client_init sucess
[ 1908.818581] [try_module_get_client]try_module_get_client_exit sucess
[ 1924.077324] [try_module_get_client]try_module_get_client_init sucess
[ 2307.850465] [try_module_get_server]try_module_get at client: 1
[ 2307.850535] [try_module_get_server]try_module_get_server_init sucess 
[ 2307.850536] [try_module_get_server]try_module_get_server_init do something ... 
[ 2307.850537] [try_module_get_server]module_put:misc_client->fops.onwer
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/5.try_module_get_at_two_module/server$ 

