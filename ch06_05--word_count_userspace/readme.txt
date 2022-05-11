wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ ls
Makefile  readme.txt  userspace.c  word_count_userspace.c
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_05--word_count_userspace/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  LD      /home/wu-being/code/linux_driver_study/ch06_05--word_count_userspace/built-in.o
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_05--word_count_userspace/word_count_userspace.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_05--word_count_userspace/word_count_userspace.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_05--word_count_userspace/word_count_userspace.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ ls -ltr
total 40
-rw-rw-r-- 1 wu-being wu-being   32 May 11 02:49 Makefile
-rw-rw-r-- 1 wu-being wu-being    0 May 11 02:50 userspace.c
-rw-rw-r-- 1 wu-being wu-being    0 May 11 02:50 readme.txt
-rw-rw-r-- 1 wu-being wu-being 2573 May 11 02:52 word_count_userspace.c
-rw-rw-r-- 1 wu-being wu-being    8 May 11 02:54 built-in.o
-rw-rw-r-- 1 wu-being wu-being 4268 May 11 02:54 word_count_userspace.o
-rw-rw-r-- 1 wu-being wu-being  100 May 11 02:54 modules.order
-rw-rw-r-- 1 wu-being wu-being 1037 May 11 02:54 word_count_userspace.mod.c
-rw-rw-r-- 1 wu-being wu-being    0 May 11 02:54 Module.symvers
-rw-rw-r-- 1 wu-being wu-being 2168 May 11 02:54 word_count_userspace.mod.o
-rw-rw-r-- 1 wu-being wu-being 5085 May 11 02:54 word_count_userspace.ko
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ sudo insmod word_count_userspace.ko 
[sudo] password for wu-being: 
Sorry, try again.
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ ls /dev/ |grep word_count_userspace
word_count_userspace



wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ gcc userspace.c -o userspace
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ ./userspace 
[word_count_userspace] Can't open file.
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ sudo ./userspace
[word_count_userspace] Get word byte display: 0, 0, 0, 0.
[word_count_userspace] Word count: 0
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ sudo ./userspace "hello wu"
[word_count_userspace] Sting: hello wu
[word_count_userspace] Get word byte display: 0, 0, 0, 2.
[word_count_userspace] Word count: 2
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_05--word_count_userspace$ 



