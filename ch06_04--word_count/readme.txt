wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ ls
Makefile  readme.txt  word_count.c
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_04--word_count/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_04--word_count/word_count.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_04--word_count/word_count.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_04--word_count/word_count.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo depmod /home/wu-being/code/linux_driver_study/ch06_04--word_count/word_count.ko 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo modprobe word_count
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ ls /dev/ -l |grep word_count
crw-------  1 root root     10,  54 May 11 02:34 word_count
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ cat /lib/modules/3.13.0-32-generic/modules.dep |grep word_count
/home/wu-being/code/linux_driver_study/ch06_04--word_count/word_count.ko:
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 



wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo dmesg -c|grep word_count
[47583.606546] [word_count] word_count_exit sucess
[47587.357414] [word_count] word_count_init sucess
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ echo 'hello wu chengbing' | sudo tee /dev/word_counthello wu chengbing
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo dmesg -c|grep word_count
[47607.030781] [word_count] [word_count_write] get  : char count: 19
[47607.030783] [word_count] [word_count_write] write: word count: 3
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo cat /dev/word_count 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo dmesg -c|grep word_count
[47629.407317] [word_count] [word_count_read] read: word count: 65536
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 



wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ echo ' hello wu chengbing' | sudo tee /dev/word_count
 hello wu chengbing
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo dmesg -c|grep word_count
[47727.221725] [word_count] [word_count_write] get  : char count: 20
[47727.221727] [word_count] [word_count_write] write: word count: 3
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ echo '  hello wu chengbing' | sudo tee /dev/word_count
  hello wu chengbing
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo dmesg -c|grep word_count
[47735.306712] [word_count] [word_count_write] get  : char count: 21
[47735.306714] [word_count] [word_count_write] write: word count: 3
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ echo '  hello   wu chengbing' | sudo tee /dev/word_count
  hello   wu chengbing
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo dmesg -c|grep word_count
[47748.184442] [word_count] [word_count_write] get  : char count: 23
[47748.184444] [word_count] [word_count_write] write: word count: 3
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ echo '  hello   wu chengbing   ' | sudo tee /dev/word_count
  hello   wu chengbing   
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo dmesg -c|grep word_count
[47754.315959] [word_count] [word_count_write] get  : char count: 26
[47754.315961] [word_count] [word_count_write] write: word count: 3
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ echo '  hello .  wu chengbing' | sudo tee /dev/word_count
  hello .  wu chengbing
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ sudo dmesg -c|grep word_count
[47762.271480] [word_count] [word_count_write] get  : char count: 24
[47762.271481] [word_count] [word_count_write] write: word count: 4
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_04--word_count$ 

