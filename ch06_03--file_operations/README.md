wu-being@ubuntu:~/code/linux_driver_study$ ls
ch06_01--hello_world  ch06_02--misc_register  ch06_03--file_operations  README.md
wu-being@ubuntu:~/code/linux_driver_study$ cd ch06_03--file_operations/
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ ls
file_operations.c  Makefile  readme.txt
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_03--file_operations/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_03--file_operations/file_operations.o
  Building modules, stage 2.
  MODPOST 1 modules
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_03--file_operations/file_operations.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ ls -ltr
total 36
-rw-rw-r-- 1 wu-being wu-being   27 May 10 12:29 Makefile
-rw-rw-r-- 1 wu-being wu-being    8 May 10 12:57 built-in.o
-rw-rw-r-- 1 wu-being wu-being    0 May 10 12:57 readme.txt
-rw-rw-r-- 1 wu-being wu-being    0 May 10 13:05 Module.symvers
-rw-rw-r-- 1 wu-being wu-being  980 May 10 13:06 file_operations.mod.c
-rw-rw-r-- 1 wu-being wu-being 2096 May 10 13:06 file_operations.mod.o
-rw-rw-r-- 1 wu-being wu-being 1606 May 10 13:06 file_operations.c
-rw-rw-r-- 1 wu-being wu-being 3320 May 10 13:06 file_operations.o
-rw-rw-r-- 1 wu-being wu-being   90 May 10 13:06 modules.order
-rw-rw-r-- 1 wu-being wu-being 4168 May 10 13:06 file_operations.ko
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo insmod file_operations.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ lsmod |grep file
file_operations        12665  0 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ ls /dev/ -l |grep file
crw-------  1 root root     10,  55 May 10 13:07 file_operations
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ ls /dev/ -l |grep misc
crw-------  1 root root     10,  56 May 10 12:40 misc_register
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ dmesg |grep file_operations
[ 8144.221348] [file_operations]file_operations_init sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ cat /var/log/syslog |grep file_operations
Binary file (standard input) matches
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo echo 'hello wu' > /dev/file_operations
bash: /dev/file_operations: Permission denied
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ dmesg |grep file_operations
[ 9449.238281] [file_operations]file_operations_init sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo cat /dev/file_operations
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ dmesg |grep file_operations
[ 9449.238281] [file_operations]file_operations_init sucess
[ 9559.336104] [file_operations] [file_operations_read] can not read data!!! count: 65536
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo cat /dev/file_operations
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo cat /dev/file_operations
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo echo 'hello wu' > /dev/file_operations
bash: /dev/file_operations: Permission denied
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ dmesg |grep file_operations
[ 9449.238281] [file_operations]file_operations_init sucess
[ 9559.336104] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9580.360098] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9580.859585] [file_operations] [file_operations_read] can not read data!!! count: 65536
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo sh -c "echo 'hello wu' > /dev/file_operations"
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ dmesg |grep file_operations
[ 9449.238281] [file_operations]file_operations_init sucess
[ 9559.336104] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9580.360098] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9580.859585] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9614.710844] [file_operations] [file_operations_write] written count: 9
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo cat /dev/file_operations
hello wu
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ dmesg |grep file_operations
[ 9449.238281] [file_operations]file_operations_init sucess
[ 9559.336104] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9580.360098] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9580.859585] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9614.710844] [file_operations] [file_operations_write] written count: 9
[ 9633.460935] [file_operations] [file_operations_read] read written_count: 9
[ 9633.460937] [file_operations] [file_operations_read] count: 65536
[ 9633.460974] [file_operations] [file_operations_read] can not read data!!! count: 65536
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo sh -c "echo 'hello wu...' > /dev/file_operations"
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ sudo cat /dev/file_operations
hello wu...
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ dmesg |grep file_operations
[ 9449.238281] [file_operations]file_operations_init sucess
[ 9559.336104] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9580.360098] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9580.859585] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9614.710844] [file_operations] [file_operations_write] written count: 9
[ 9633.460935] [file_operations] [file_operations_read] read written_count: 9
[ 9633.460937] [file_operations] [file_operations_read] count: 65536
[ 9633.460974] [file_operations] [file_operations_read] can not read data!!! count: 65536
[ 9867.833718] [file_operations] [file_operations_write] written count: 12
[ 9870.215981] [file_operations] [file_operations_read] read written_count: 12
[ 9870.215985] [file_operations] [file_operations_read] count: 65536
[ 9870.216003] [file_operations] [file_operations_read] can not read data!!! count: 65536
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_03--file_operations$ 




