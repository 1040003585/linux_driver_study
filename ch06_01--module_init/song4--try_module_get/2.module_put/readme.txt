wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  LD      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put/built-in.o
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put/module_put.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put/module_put.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put/module_put.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 



wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ sudo insmod module_put.ko 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ dmesg |grep module_put
[  194.871594] module_put: module license 'unspecified' taints kernel.
[  194.871610] module_put: module verification failed: signature and/or  required key missing - tainting kernel
[  194.872133] module_put_init sucess
[  194.872135] module_put: 1
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ tail -n 6 /var/log/kern.log
May 12 08:31:28 ubuntu kernel: [  194.871594] module_put: module license 'unspecified' taints kernel.
May 12 08:31:28 ubuntu kernel: [  194.871596] Disabling lock debugging due to kernel taint
May 12 08:31:28 ubuntu kernel: [  194.871610] module_put: module verification failed: signature and/or  required key missing - tainting kernel
May 12 08:31:28 ubuntu kernel: [  194.872133] module_put_init sucess
May 12 08:31:28 ubuntu kernel: [  194.872134] try_module_get1: 1
May 12 08:31:28 ubuntu kernel: [  194.872135] module_put: 1
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 



wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ sudo rmmod module_put 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ tail -n 7 /var/log/kern.log
May 12 08:31:28 ubuntu kernel: [  194.871594] module_put: module license 'unspecified' taints kernel.
May 12 08:31:28 ubuntu kernel: [  194.871596] Disabling lock debugging due to kernel taint
May 12 08:31:28 ubuntu kernel: [  194.871610] module_put: module verification failed: signature and/or  required key missing - tainting kernel
May 12 08:31:28 ubuntu kernel: [  194.872133] module_put_init sucess
May 12 08:31:28 ubuntu kernel: [  194.872134] try_module_get1: 1
May 12 08:31:28 ubuntu kernel: [  194.872135] module_put: 1
May 12 08:32:53 ubuntu kernel: [  280.615862] module_put_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 



wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ sudo insmod module_put.ko 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ sudo rmmod module_put 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ tail -n 10 /var/log/kern.log
May 12 08:31:28 ubuntu kernel: [  194.871596] Disabling lock debugging due to kernel taint
May 12 08:31:28 ubuntu kernel: [  194.871610] module_put: module verification failed: signature and/or  required key missing - tainting kernel
May 12 08:31:28 ubuntu kernel: [  194.872133] module_put_init sucess
May 12 08:31:28 ubuntu kernel: [  194.872134] try_module_get1: 1
May 12 08:31:28 ubuntu kernel: [  194.872135] module_put: 1
May 12 08:32:53 ubuntu kernel: [  280.615862] module_put_exit sucess
May 12 08:33:19 ubuntu kernel: [  306.092809] module_put_init sucess
May 12 08:33:19 ubuntu kernel: [  306.092811] try_module_get1: 1
May 12 08:33:19 ubuntu kernel: [  306.092812] module_put: 1
May 12 08:33:28 ubuntu kernel: [  314.967185] module_put_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--try_module_get/2.module_put$ 

