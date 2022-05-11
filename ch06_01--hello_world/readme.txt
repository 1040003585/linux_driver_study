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
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ echo ""readme.md
readme.md
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ echo "" >readme.md
wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ gedit readme.md 




wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ lsmod 
Module                  Size  Used by
hello_world            12460  0 
file_operations        12727  0 
misc_register          12510  0 
word_count             12458  0 


wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ cat /proc/modules 
hello_world 12460 0 - Live 0x00000000 (POF)
file_operations 12727 0 - Live 0x00000000 (OF)
misc_register 12510 0 - Live 0x00000000 (POF)
word_count 12458 0 - Live 0x00000000 (POF)
...


wu-being@ubuntu:/sys/module/hello_world$ tree -a
.
├── coresize
├── holders
├── initsize
├── initstate
├── notes
│   └── .note.gnu.build-id
├── refcnt
├── sections
│   ├── .gnu.linkonce.this_module
│   ├── __mcount_loc
│   ├── .note.gnu.build-id
│   ├── .rodata.str1.1
│   ├── .strtab
│   ├── .symtab
│   └── .text
├── srcversion
├── taint
└── uevent

3 directories, 15 files
wu-being@ubuntu:/sys/module/hello_world$ ls -l
total 0
-r--r--r-- 1 root root 4096 May 10 23:17 coresize
drwxr-xr-x 2 root root    0 May 10 23:17 holders
-r--r--r-- 1 root root 4096 May 10 23:19 initsize
-r--r--r-- 1 root root 4096 May 10 23:19 initstate
drwxr-xr-x 2 root root    0 May 10 23:19 notes
-r--r--r-- 1 root root 4096 May 10 23:17 refcnt
drwxr-xr-x 2 root root    0 May 10 23:19 sections
-r--r--r-- 1 root root 4096 May 10 23:19 srcversion
-r--r--r-- 1 root root 4096 May 10 23:19 taint
--w------- 1 root root 4096 May 10 23:17 uevent
wu-being@ubuntu:/sys/module/hello_world$ ls holders/
wu-being@ubuntu:/sys/module/hello_world$ cat coresize 
12460
wu-being@ubuntu:/sys/module/hello_world$ cat initsize 
0
wu-being@ubuntu:/sys/module/hello_world$ cat initstate 
live
wu-being@ubuntu:/sys/module/hello_world$ cat refcnt 
0
wu-being@ubuntu:/sys/module/hello_world$ cat srcversion 
D0135CE62CFDBE5D1E8A3D2
wu-being@ubuntu:/sys/module/hello_world$ cat taint 
POF
wu-being@ubuntu:/sys/module/hello_world$ cat uevent 
cat: uevent: Permission denied
wu-being@ubuntu:/sys/module/hello_world$ 



wu-being@ubuntu:/sys/module/hello_world$ ls sections/ -la
total 0
drwxr-xr-x 2 root root    0 May 10 23:19 .
drwxr-xr-x 5 root root    0 May 10 23:17 ..
-r--r--r-- 1 root root 4096 May 10 23:20 .gnu.linkonce.this_module
-r--r--r-- 1 root root 4096 May 10 23:20 __mcount_loc
-r--r--r-- 1 root root 4096 May 10 23:20 .note.gnu.build-id
-r--r--r-- 1 root root 4096 May 10 23:20 .rodata.str1.1
-r--r--r-- 1 root root 4096 May 10 23:20 .strtab
-r--r--r-- 1 root root 4096 May 10 23:20 .symtab
-r--r--r-- 1 root root 4096 May 10 23:20 .text

wu-being@ubuntu:/sys/module/hello_world$ cat sections/*
0x00000000
wu-being@ubuntu:/sys/module/hello_world$ cat sections/.text 
0x00000000
wu-being@ubuntu:/sys/module/hello_world$ cat sections/.symtab 
0x00000000
wu-being@ubuntu:/sys/module/hello_world$ cat sections/.note.gnu.build-id 
0x00000000
wu-being@ubuntu:/sys/module/hello_world$ cat sections/__mcount_loc 
0x00000000
wu-being@ubuntu:/sys/module/hello_world$ ls sections/ -l
total 0
-r--r--r-- 1 root root 4096 May 10 23:20 __mcount_loc
wu-being@ubuntu:/sys/module/hello_world$ 



wu-being@ubuntu:/sys/module/hello_world$ cat /lib/modules/3.13.0-32-generic/modules.dep
kernel/arch/x86/kernel/cpu/mcheck/mce-inject.ko:
kernel/arch/x86/kernel/msr.ko:
kernel/arch/x86/kernel/cpuid.ko:
kernel/arch/x86/kernel/apm.ko:
kernel/arch/x86/crypto/glue_helper.ko:
kernel/arch/x86/crypto/aes-i586.ko:
kernel/arch/x86/crypto/twofish-i586.ko: kernel/crypto/twofish_common.ko
kernel/arch/x86/crypto/salsa20-i586.ko:
kernel/arch/x86/crypto/serpent-sse2-i586.ko: kernel/crypto/xts.ko kernel/crypto/serpent_generic.ko kernel/crypto/lrw.ko kernel/crypto/gf128mul.ko kernel/arch/x86/crypto/glue_helper.ko kernel/crypto/ablk_helper.ko kernel/crypto/cryptd.ko
kernel/arch/x86/crypto/aesni-intel.ko: kernel/arch/x86/crypto/aes-i586.ko kernel/crypto/xts.ko kernel/crypto/lrw.ko kernel/crypto/gf128mul.ko kernel/crypto/ablk_helper.ko kernel/crypto/cryptd.ko
kernel/arch/x86/crypto/crc32-pclmul.ko:
kernel/arch/x86/platform/iris/iris.ko:
kernel/arch/x86/platform/scx200/scx200.ko:
kernel/arch/x86/kvm/kvm.ko:
kernel/arch/x86/kvm/kvm-intel.ko: kernel/arch/x86/kvm/kvm.ko
kernel/arch/x86/kvm/kvm-amd.ko: kernel/arch/x86/kvm/kvm.ko
kernel/mm/hwpoison-inject.ko:
kernel/fs/nfs_common/nfs_acl.ko: kernel/net/sunrpc/sunrpc.ko
kernel/fs/quota/quota_v1.ko:
kernel/fs/quota/quota_v2.ko: kernel/fs/quota/quota_tree.ko


wu-being@ubuntu:~/code/linux_driver_study/ch06_01--hello_world$ cat /proc/modules 
hello_world 12460 0 - Live 0x00000000 (POF)
file_operations 12727 0 - Live 0x00000000 (OF)
misc_register 12510 0 - Live 0x00000000 (POF)
word_count 12458 0 - Live 0x00000000 (POF)
...


wu-being@ubuntu:~/code/linux_driver_study$ modinfo ./ch06_01--hello_world/hello_world.ko 
filename:       /home/wu-being/code/linux_driver_study/./ch06_01--hello_world/hello_world.ko
srcversion:     D0135CE62CFDBE5D1E8A3D2
depends:        
vermagic:       3.13.0-32-generic SMP mod_unload modversions 686 
wu-being@ubuntu:~/code/linux_driver_study$ 
wu-being@ubuntu:~/code/linux_driver_study$ 
wu-being@ubuntu:~/code/linux_driver_study$ 
wu-being@ubuntu:~/code/linux_driver_study$ modinfo ./ch06_02--misc_register/misc_register.ko 
filename:       /home/wu-being/code/linux_driver_study/./ch06_02--misc_register/misc_register.ko
srcversion:     B8B041488B59A3A5DD4F3D0
depends:        
vermagic:       3.13.0-32-generic SMP mod_unload modversions 686 
wu-being@ubuntu:~/code/linux_driver_study$ 
wu-being@ubuntu:~/code/linux_driver_study$ 
wu-being@ubuntu:~/code/linux_driver_study$ 
wu-being@ubuntu:~/code/linux_driver_study$ modinfo ./ch06_03--file_operations/file_operations.ko 
filename:       /home/wu-being/code/linux_driver_study/./ch06_03--file_operations/file_operations.ko
license:        GPL
alias:          word count module.
description:    statistics of word count.
author:         Chengbing.Wu
srcversion:     6CBD18D6D8FB316DFC9DAC6
depends:        
vermagic:       3.13.0-32-generic SMP mod_unload modversions 686 
wu-being@ubuntu:~/code/linux_driver_study$ 
wu-being@ubuntu:~/code/linux_driver_study$ 



