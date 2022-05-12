wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL/EXPORT_SYMBOL.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL/EXPORT_SYMBOL.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL/EXPORT_SYMBOL.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ cat Module.symvers 
0x79fbc5a6	book_name	/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL/EXPORT_SYMBOL	EXPORT_SYMBOL_GPL
0x13db98c9	sub_integar	/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL/EXPORT_SYMBOL	EXPORT_SYMBOL_GPL
0xe1626dee	add_integar	/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL/EXPORT_SYMBOL	EXPORT_SYMBOL
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL$ 


wu-being@ubuntu:~$ 
wu-being@ubuntu:~$ grep integar /proc/kallsyms 
00000000 r __kstrtab_sub_integar	[EXPORT_SYMBOL]
00000000 r __kcrctab_sub_integar	[EXPORT_SYMBOL]
00000000 r __kstrtab_add_integar	[EXPORT_SYMBOL]
00000000 r __kcrctab_add_integar	[EXPORT_SYMBOL]
00000000 T add_integar	[EXPORT_SYMBOL]
00000000 r __ksymtab_add_integar	[EXPORT_SYMBOL]
00000000 t sub_integar	[EXPORT_SYMBOL]
00000000 r __ksymtab_sub_integar	[EXPORT_SYMBOL]
wu-being@ubuntu:~$ 
wu-being@ubuntu:~$ 


wu-being@ubuntu:~$ 
wu-being@ubuntu:~$ 
wu-being@ubuntu:~$ grep book_name /proc/kallsyms 
00000000 d book_name	[EXPORT_SYMBOL]
00000000 r __kstrtab_book_name	[EXPORT_SYMBOL]
00000000 r __kcrctab_book_name	[EXPORT_SYMBOL]
00000000 r __ksymtab_book_name	[EXPORT_SYMBOL]
wu-being@ubuntu:~$ 

