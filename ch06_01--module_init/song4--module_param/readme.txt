wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--module_param/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--module_param/module_param.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--module_param/module_param.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--module_param/module_param.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ sudo insmod module_param.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ ls /sys/module/module_param/parameters/ -l
total 0
-r--r--r-- 1 root root 4096 May 12 03:15 book_name
-r--r--r-- 1 root root 4096 May 12 03:15 book_num
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ cat /sys/module/module_param/parameters/book_name 
dissecting Linux Device Driver
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ cat /sys/module/module_param/parameters/book_num 
4000
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ tail -n2  /var/log/kern.log
May 12 03:14:51 ubuntu kernel: [137063.729953] book_name: dissecting Linux Device Driver
May 12 03:14:51 ubuntu kernel: [137063.729954] book_num : 4000



wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ sudo rmmod module_param 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ sudo insmod module_param.ko book_name="GOOD book" book_num=500
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ tail -n  /var/log/kern.log
tail: /var/log/kern.log: invalid number of lines
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ tail -n2  /var/log/kern.log
May 12 03:18:20 ubuntu kernel: [137273.057119] book_name: GOOD
May 12 03:18:20 ubuntu kernel: [137273.057120] book_num : 500
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ cat /sys/module/module_param/parameters/book_name 
GOOD
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ cat /sys/module/module_param/parameters/book_num 
500
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ sudo rmmod module_param 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ sudo insmod module_param.ko book_name="GOOD_book" book_num=500
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ tail -n2  /var/log/kern.log
May 12 03:19:38 ubuntu kernel: [137350.696628] book_name: GOOD_book
May 12 03:19:38 ubuntu kernel: [137350.696629] book_num : 500
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--module_param$ 

