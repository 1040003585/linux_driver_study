wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ sudo insmod EXPORT_SYMBOL_another.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ tail -n2  /var/log/kern.log
May 12 03:44:20 ubuntu kernel: [138833.083263] EXPORT_SYMBOL_another_init sucess
May 12 03:44:20 ubuntu kernel: [138833.083267] EXPORT_SYMBOL_another sub_integar: 2.
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 

wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another/EXPORT_SYMBOL_another.o
  Building modules, stage 2.
  MODPOST 1 modules
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another/EXPORT_SYMBOL_another.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 



# Note:

## 1. // MODULE_LICENSE("GPL v2"); will following:

wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ sudo insmod EXPORT_SYMBOL_another.ko insmod: ERROR: could not insert module EXPORT_SYMBOL_another.ko: Unknown symbol in module
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 

## 2. The both Module.symvers of EXPORT_SYMBOL and EXPORT_SYMBOL_another much be same;



wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ tail -n 30  /var/log/kern.log
May 12 03:34:05 ubuntu kernel: [138217.951680] book_name: GOOD_book
May 12 03:34:05 ubuntu kernel: [138217.951680] book_num : 500
May 12 03:34:14 ubuntu kernel: [138226.525644] module_param_exit sucess
May 12 03:34:22 ubuntu kernel: [138234.591939] hello_world_init sucess
May 12 03:34:22 ubuntu kernel: [138234.591941] book_name: dissecting Linux Device Driver
May 12 03:34:22 ubuntu kernel: [138234.591942] book_num : 4000
May 12 03:44:20 ubuntu kernel: [138833.083263] EXPORT_SYMBOL_another_init sucess
May 12 03:44:20 ubuntu kernel: [138833.083267] EXPORT_SYMBOL_another sub_integar: 2.
May 12 03:46:32 ubuntu kernel: [138964.803819] EXPORT_SYMBOL_another_exit sucess
May 12 03:46:36 ubuntu kernel: [138968.999320] EXPORT_SYMBOL_another_init sucess
May 12 03:46:36 ubuntu kernel: [138968.999322] EXPORT_SYMBOL_another sub_integar: 2.
May 12 03:47:07 ubuntu kernel: [139000.450709] EXPORT_SYMBOL_another_exit sucess
May 12 03:49:05 ubuntu kernel: [139118.710717] EXPORT_SYMBOL_another: Unknown symbol sub_integar (err 0)
May 12 03:49:05 ubuntu kernel: [139118.711022] EXPORT_SYMBOL_another: Unknown symbol book_name (err 0)
May 12 03:49:36 ubuntu kernel: [139149.295964] EXPORT_SYMBOL_another: Unknown symbol sub_integar (err 0)
May 12 03:49:36 ubuntu kernel: [139149.295983] EXPORT_SYMBOL_another: Unknown symbol book_name (err 0)
May 12 03:49:40 ubuntu kernel: [139153.707146] EXPORT_SYMBOL_another: Unknown symbol sub_integar (err 0)
May 12 03:49:57 ubuntu kernel: [139170.128228] EXPORT_SYMBOL_another: Unknown symbol sub_integar (err 0)
May 12 03:50:00 ubuntu kernel: [139173.660523] EXPORT_SYMBOL_another: Unknown symbol sub_integar (err 0)
May 12 03:50:06 ubuntu kernel: [139179.342987] EXPORT_SYMBOL_another: Unknown symbol sub_integar (err 0)
May 12 03:50:44 ubuntu kernel: [139217.487016] EXPORT_SYMBOL_another: Unknown symbol sub_integar (err 0)
May 12 03:50:48 ubuntu kernel: [139221.115601] EXPORT_SYMBOL_another: Unknown symbol sub_integar (err 0)
May 12 03:51:16 ubuntu kernel: [139249.009740] EXPORT_SYMBOL_another_init sucess
May 12 03:51:16 ubuntu kernel: [139249.009742] EXPORT_SYMBOL_another add_integar: 2.
May 12 03:51:16 ubuntu kernel: [139249.009743] EXPORT_SYMBOL_another sub_integar: 0.
May 12 03:53:50 ubuntu kernel: [139403.817523] EXPORT_SYMBOL_another_exit sucess
May 12 03:53:54 ubuntu kernel: [139406.941638] EXPORT_SYMBOL_another_init sucess
May 12 03:53:54 ubuntu kernel: [139406.941640] EXPORT_SYMBOL_another add_integar: 2.
May 12 03:53:54 ubuntu kernel: [139406.941641] EXPORT_SYMBOL_another sub_integar: 0.
May 12 03:53:54 ubuntu kernel: [139406.941641] EXPORT_SYMBOL_another book_name  : EXPORT_SYMBOL module.
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 


https://blog.csdn.net/u014436243/article/details/102860177

wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ modinfo EXPORT_SYMBOL_another.ko
filename:       /home/wu-being/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another/EXPORT_SYMBOL_another.ko
license:        GPL v2				//##########
srcversion:     20213FCF7BDECB1B4F3557D
depends:        EXPORT_SYMBOL			//######## depends on EXPORT_SYMBOL
vermagic:       3.13.0-32-generic SMP mod_unload modversions 686 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--module_init/song4--EXPORT_SYMBOL_another$ 




