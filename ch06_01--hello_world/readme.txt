wu-being@ubuntu:~/code/linux_driver_study$ mkdir ch06_01--hello_world
wu-being@ubuntu:~/code/linux_driver_study$ cd ch06_01--hello_world/
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ echo "" > hello_world.c
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ echo "obj-m := hello_world.o" > Makefile
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ ls
hello_world.c  Makefile
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ gedit hello_world.c 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ pwd
/home/wu-being/code/linux_driver_study/ch06_01--hello_world
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--hello_world/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  LD      /home/wu-being/code/linux_driver_study/ch06_01--hello_world/built-in.o
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--hello_world/hello_world.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--hello_world/hello_world.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--hello_world/hello_world.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ ls
built-in.o  hello_world.c  hello_world.c~  hello_world.ko  hello_world.mod.c  hello_world.mod.o  hello_world.o  Makefile  modules.order  Module.symvers
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ insmod hello_world.ko 
insmod: ERROR: could not insert module hello_world.ko: Operation not permitted
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ sudo insmod hello_world.ko 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ lsmod |grep hello
hello_world            12460  0 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ dmesg |grep hello
[ 4921.385027] hello_world_init sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ rmmod hello_world 
rmmod: ERROR: ../libkmod/libkmod-module.c:769 kmod_module_remove_module() could not remove 'hello_world': Operation not permitted
rmmod: ERROR: could not remove module hello_world: Operation not permitted
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ sudo rmmod hello_world 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ dmesg |grep hello
[ 4921.385027] hello_world_init sucess
[ 4982.434300] hello_world_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ cat /var/log/syslog |grep hello
Feb 26 04:08:44 ubuntu kernel: [ 4921.385027] hello_world_init sucess
Feb 26 04:09:45 ubuntu kernel: [ 4982.434300] hello_world_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ cat /var/log/syslog |grep hello |tail -n 2
Feb 26 04:08:44 ubuntu kernel: [ 4921.385027] hello_world_init sucess
Feb 26 04:09:45 ubuntu kernel: [ 4982.434300] hello_world_exit sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ echo "" >readme.md
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ gedit readme.md 


