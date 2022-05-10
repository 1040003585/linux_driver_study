wu-being@ubuntu:~/code/linux_driver_study$ 
wu-being@ubuntu:~/code/linux_driver_study$ ls
ch06_01--hello_world  README.md
wu-being@ubuntu:~/code/linux_driver_study$ mkdir ch06_02--misc_register
wu-being@ubuntu:~/code/linux_driver_study$ ls
ch06_01--hello_world  ch06_02--misc_register  README.md
wu-being@ubuntu:~/code/linux_driver_study$ cd ch06_02--misc_register/
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ ls
Makefile  misc_register.c  readme.txt
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ ls /dev/
agpgart          hidraw0             null      ram8      tty    tty27  tty46  tty8       ttyS25   vcs4
autofs           hpet                parport0  ram9      tty0   tty28  tty47  tty9       ttyS26   vcs5
block            input               port      random    tty1   tty29  tty48  ttyprintk  ttyS27   vcs6
bsg              kmsg                ppp       rfkill    tty10  tty3   tty49  ttyS0      ttyS28   vcs7
btrfs-control    log                 psaux     rtc       tty11  tty30  tty5   ttyS1      ttyS29   vcsa
bus              loop0               ptmx      rtc0      tty12  tty31  tty50  ttyS10     ttyS3    vcsa1
cdrom            loop1               pts       sda       tty13  tty32  tty51  ttyS11     ttyS30   vcsa2
char             loop2               ram0      sda1      tty14  tty33  tty52  ttyS12     ttyS31   vcsa3
console          loop3               ram1      sda2      tty15  tty34  tty53  ttyS13     ttyS4    vcsa4
core             loop4               ram10     sda5      tty16  tty35  tty54  ttyS14     ttyS5    vcsa5
cpu              loop5               ram11     sg0       tty17  tty36  tty55  ttyS15     ttyS6    vcsa6
cpu_dma_latency  loop6               ram12     sg1       tty18  tty37  tty56  ttyS16     ttyS7    vcsa7
cuse             loop7               ram13     sg2       tty19  tty38  tty57  ttyS17     ttyS8    vga_arbiter
disk             loop-control        ram14     shm       tty2   tty39  tty58  ttyS18     ttyS9    vhci
dri              lp0                 ram15     snapshot  tty20  tty4   tty59  ttyS19     uhid     vhost-net
ecryptfs         mapper              ram2      snd       tty21  tty40  tty6   ttyS2      uinput   vmci
fb0              mcelog              ram3      sr0       tty22  tty41  tty60  ttyS20     urandom  zero
fd               mem                 ram4      sr1       tty23  tty42  tty61  ttyS21     vcs
fd0              net                 ram5      stderr    tty24  tty43  tty62  ttyS22     vcs1
full             network_latency     ram6      stdin     tty25  tty44  tty63  ttyS23     vcs2
fuse             network_throughput  ram7      stdout    tty26  tty45  tty7   ttyS24     vcs3
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ ls /dev/ -l
total 0
crw-rw----  1 root video    10, 175 May 10 10:02 agpgart
crw-------  1 root root     10, 235 May 10 10:02 autofs
drwxr-xr-x  2 root root         660 May 10 10:02 block
drwxr-xr-x  2 root root         100 May 10 10:02 bsg
crw-------  1 root root     10, 234 May 10 10:02 btrfs-control
drwxr-xr-x  3 root root          60 May 10 10:02 bus
lrwxrwxrwx  1 root root           3 May 10 10:02 cdrom -> sr0
drwxr-xr-x  2 root root        3540 May 10 11:17 char
crw-------  1 root root      5,   1 May 10 10:02 console
lrwxrwxrwx  1 root root          11 May 10 10:02 core -> /proc/kcore
drwxr-xr-x  2 root root          60 May 10 10:02 cpu
crw-------  1 root root     10,  60 May 10 10:02 cpu_dma_latency
crw-------  1 root root     10, 203 May 10 10:02 cuse
drwxr-xr-x  5 root root         100 May 10 10:02 disk
drwxr-xr-x  2 root root          80 May 10 10:02 dri
crw-------  1 root root     10,  61 May 10 10:02 ecryptfs
crw-rw----  1 root video    29,   0 May 10 10:02 fb0
lrwxrwxrwx  1 root root          13 May 10 10:02 fd -> /proc/self/fd
brw-rw----  1 root floppy    2,   0 May 10 10:02 fd0
crw-rw-rw-  1 root root      1,   7 May 10 10:02 full
crw-rw-rw-  1 root root     10, 229 May 10 10:02 fuse
crw-------  1 root root    251,   0 May 10 10:02 hidraw0
crw-------  1 root root     10, 228 May 10 10:02 hpet
drwxr-xr-x  4 root root         220 May 10 10:02 input
crw-r--r--  1 root root      1,  11 May 10 10:02 kmsg
srw-rw-rw-  1 root root           0 May 10 10:02 log
brw-rw----  1 root disk      7,   0 May 10 10:02 loop0
brw-rw----  1 root disk      7,   1 May 10 10:02 loop1
brw-rw----  1 root disk      7,   2 May 10 10:02 loop2
brw-rw----  1 root disk      7,   3 May 10 10:02 loop3
brw-rw----  1 root disk      7,   4 May 10 10:02 loop4
brw-rw----  1 root disk      7,   5 May 10 10:02 loop5
brw-rw----  1 root disk      7,   6 May 10 10:02 loop6
brw-rw----  1 root disk      7,   7 May 10 10:02 loop7
crw-------  1 root root     10, 237 May 10 10:02 loop-control
crw-rw----  1 root lp        6,   0 May 10 10:02 lp0
drwxr-xr-x  2 root root          60 May 10 10:02 mapper
crw-------  1 root root     10, 227 May 10 10:02 mcelog
crw-r-----  1 root kmem      1,   1 May 10 10:02 mem
drwxr-xr-x  2 root root          60 May 10 10:02 net
crw-------  1 root root     10,  59 May 10 10:02 network_latency
crw-------  1 root root     10,  58 May 10 10:02 network_throughput
crw-rw-rw-  1 root root      1,   3 May 10 10:02 null
crw-rw-r--  1 root lp       99,   0 May 10 10:02 parport0
crw-r-----  1 root kmem      1,   4 May 10 10:02 port
crw-------  1 root root    108,   0 May 10 10:02 ppp
crw-------  1 root root     10,   1 May 10 10:02 psaux
crw-rw-rw-  1 root tty       5,   2 May 10 11:44 ptmx
drwxr-xr-x  2 root root           0 May 10 10:02 pts
brw-rw----  1 root disk      1,   0 May 10 10:02 ram0
brw-rw----  1 root disk      1,   1 May 10 10:02 ram1
brw-rw----  1 root disk      1,  10 May 10 10:02 ram10
brw-rw----  1 root disk      1,  11 May 10 10:02 ram11
brw-rw----  1 root disk      1,  12 May 10 10:02 ram12
brw-rw----  1 root disk      1,  13 May 10 10:02 ram13
brw-rw----  1 root disk      1,  14 May 10 10:02 ram14
brw-rw----  1 root disk      1,  15 May 10 10:02 ram15
brw-rw----  1 root disk      1,   2 May 10 10:02 ram2
brw-rw----  1 root disk      1,   3 May 10 10:02 ram3
brw-rw----  1 root disk      1,   4 May 10 10:02 ram4
brw-rw----  1 root disk      1,   5 May 10 10:02 ram5
brw-rw----  1 root disk      1,   6 May 10 10:02 ram6
brw-rw----  1 root disk      1,   7 May 10 10:02 ram7
brw-rw----  1 root disk      1,   8 May 10 10:02 ram8
brw-rw----  1 root disk      1,   9 May 10 10:02 ram9
crw-rw-rw-  1 root root      1,   8 May 10 10:02 random
crw-rw-r--+ 1 root root     10,  62 May 10 10:02 rfkill
lrwxrwxrwx  1 root root           4 May 10 10:02 rtc -> rtc0
crw-------  1 root root    254,   0 May 10 10:02 rtc0
brw-rw----  1 root disk      8,   0 May 10 10:02 sda
brw-rw----  1 root disk      8,   1 May 10 10:02 sda1
brw-rw----  1 root disk      8,   2 May 10 10:02 sda2
brw-rw----  1 root disk      8,   5 May 10 10:02 sda5
crw-rw----+ 1 root cdrom    21,   0 May 10 10:02 sg0
crw-rw----+ 1 root cdrom    21,   1 May 10 10:02 sg1
crw-rw----  1 root disk     21,   2 May 10 10:02 sg2
lrwxrwxrwx  1 root root           8 May 10 10:02 shm -> /run/shm
crw-------  1 root root     10, 231 May 10 10:02 snapshot
drwxr-xr-x  3 root root         200 May 10 10:02 snd
brw-rw----+ 1 root cdrom    11,   0 May 10 10:02 sr0
brw-rw----+ 1 root cdrom    11,   1 May 10 10:02 sr1
lrwxrwxrwx  1 root root          15 May 10 10:02 stderr -> /proc/self/fd/2
lrwxrwxrwx  1 root root          15 May 10 10:02 stdin -> /proc/self/fd/0
lrwxrwxrwx  1 root root          15 May 10 10:02 stdout -> /proc/self/fd/1
crw-rw-rw-  1 root tty       5,   0 May 10 11:22 tty
crw--w----  1 root tty       4,   0 May 10 10:02 tty0
crw-rw----  1 root tty       4,   1 May 10 10:02 tty1
crw--w----  1 root tty       4,  10 May 10 10:02 tty10
crw--w----  1 root tty       4,  11 May 10 10:02 tty11
crw--w----  1 root tty       4,  12 May 10 10:02 tty12
crw--w----  1 root tty       4,  13 May 10 10:02 tty13
crw--w----  1 root tty       4,  14 May 10 10:02 tty14
crw--w----  1 root tty       4,  15 May 10 10:02 tty15
crw--w----  1 root tty       4,  16 May 10 10:02 tty16
crw--w----  1 root tty       4,  17 May 10 10:02 tty17
crw--w----  1 root tty       4,  18 May 10 10:02 tty18
crw--w----  1 root tty       4,  19 May 10 10:02 tty19
crw-rw----  1 root tty       4,   2 May 10 10:02 tty2
crw--w----  1 root tty       4,  20 May 10 10:02 tty20
crw--w----  1 root tty       4,  21 May 10 10:02 tty21
crw--w----  1 root tty       4,  22 May 10 10:02 tty22
crw--w----  1 root tty       4,  23 May 10 10:02 tty23
crw--w----  1 root tty       4,  24 May 10 10:02 tty24
crw--w----  1 root tty       4,  25 May 10 10:02 tty25
crw--w----  1 root tty       4,  26 May 10 10:02 tty26
crw--w----  1 root tty       4,  27 May 10 10:02 tty27
crw--w----  1 root tty       4,  28 May 10 10:02 tty28
crw--w----  1 root tty       4,  29 May 10 10:02 tty29
crw-rw----  1 root tty       4,   3 May 10 10:02 tty3
crw--w----  1 root tty       4,  30 May 10 10:02 tty30
crw--w----  1 root tty       4,  31 May 10 10:02 tty31
crw--w----  1 root tty       4,  32 May 10 10:02 tty32
crw--w----  1 root tty       4,  33 May 10 10:02 tty33
crw--w----  1 root tty       4,  34 May 10 10:02 tty34
crw--w----  1 root tty       4,  35 May 10 10:02 tty35
crw--w----  1 root tty       4,  36 May 10 10:02 tty36
crw--w----  1 root tty       4,  37 May 10 10:02 tty37
crw--w----  1 root tty       4,  38 May 10 10:02 tty38
crw--w----  1 root tty       4,  39 May 10 10:02 tty39
crw-rw----  1 root tty       4,   4 May 10 10:02 tty4
crw--w----  1 root tty       4,  40 May 10 10:02 tty40
crw--w----  1 root tty       4,  41 May 10 10:02 tty41
crw--w----  1 root tty       4,  42 May 10 10:02 tty42
crw--w----  1 root tty       4,  43 May 10 10:02 tty43
crw--w----  1 root tty       4,  44 May 10 10:02 tty44
crw--w----  1 root tty       4,  45 May 10 10:02 tty45
crw--w----  1 root tty       4,  46 May 10 10:02 tty46
crw--w----  1 root tty       4,  47 May 10 10:02 tty47
crw--w----  1 root tty       4,  48 May 10 10:02 tty48
crw--w----  1 root tty       4,  49 May 10 10:02 tty49
crw-rw----  1 root tty       4,   5 May 10 10:02 tty5
crw--w----  1 root tty       4,  50 May 10 10:02 tty50
crw--w----  1 root tty       4,  51 May 10 10:02 tty51
crw--w----  1 root tty       4,  52 May 10 10:02 tty52
crw--w----  1 root tty       4,  53 May 10 10:02 tty53
crw--w----  1 root tty       4,  54 May 10 10:02 tty54
crw--w----  1 root tty       4,  55 May 10 10:02 tty55
crw--w----  1 root tty       4,  56 May 10 10:02 tty56
crw--w----  1 root tty       4,  57 May 10 10:02 tty57
crw--w----  1 root tty       4,  58 May 10 10:02 tty58
crw--w----  1 root tty       4,  59 May 10 10:02 tty59
crw-rw----  1 root tty       4,   6 May 10 10:02 tty6
crw--w----  1 root tty       4,  60 May 10 10:02 tty60
crw--w----  1 root tty       4,  61 May 10 10:02 tty61
crw--w----  1 root tty       4,  62 May 10 10:02 tty62
crw--w----  1 root tty       4,  63 May 10 10:02 tty63
crw--w----  1 root tty       4,   7 May 10 10:02 tty7
crw--w----  1 root tty       4,   8 May 10 10:02 tty8
crw--w----  1 root tty       4,   9 May 10 10:02 tty9
crw-------  1 root root      5,   3 May 10 10:02 ttyprintk
crw-rw----  1 root dialout   4,  64 May 10 11:44 ttyS0
crw-rw----  1 root dialout   4,  65 May 10 10:02 ttyS1
crw-rw----  1 root dialout   4,  74 May 10 10:02 ttyS10
crw-rw----  1 root dialout   4,  75 May 10 10:02 ttyS11
crw-rw----  1 root dialout   4,  76 May 10 10:02 ttyS12
crw-rw----  1 root dialout   4,  77 May 10 10:02 ttyS13
crw-rw----  1 root dialout   4,  78 May 10 10:02 ttyS14
crw-rw----  1 root dialout   4,  79 May 10 10:02 ttyS15
crw-rw----  1 root dialout   4,  80 May 10 10:02 ttyS16
crw-rw----  1 root dialout   4,  81 May 10 10:02 ttyS17
crw-rw----  1 root dialout   4,  82 May 10 10:02 ttyS18
crw-rw----  1 root dialout   4,  83 May 10 10:02 ttyS19
crw-rw----  1 root dialout   4,  66 May 10 10:02 ttyS2
crw-rw----  1 root dialout   4,  84 May 10 10:02 ttyS20
crw-rw----  1 root dialout   4,  85 May 10 10:02 ttyS21
crw-rw----  1 root dialout   4,  86 May 10 10:02 ttyS22
crw-rw----  1 root dialout   4,  87 May 10 10:02 ttyS23
crw-rw----  1 root dialout   4,  88 May 10 10:02 ttyS24
crw-rw----  1 root dialout   4,  89 May 10 10:02 ttyS25
crw-rw----  1 root dialout   4,  90 May 10 10:02 ttyS26
crw-rw----  1 root dialout   4,  91 May 10 10:02 ttyS27
crw-rw----  1 root dialout   4,  92 May 10 10:02 ttyS28
crw-rw----  1 root dialout   4,  93 May 10 10:02 ttyS29
crw-rw----  1 root dialout   4,  67 May 10 10:02 ttyS3
crw-rw----  1 root dialout   4,  94 May 10 10:02 ttyS30
crw-rw----  1 root dialout   4,  95 May 10 10:02 ttyS31
crw-rw----  1 root dialout   4,  68 May 10 10:02 ttyS4
crw-rw----  1 root dialout   4,  69 May 10 10:02 ttyS5
crw-rw----  1 root dialout   4,  70 May 10 10:02 ttyS6
crw-rw----  1 root dialout   4,  71 May 10 10:02 ttyS7
crw-rw----  1 root dialout   4,  72 May 10 10:02 ttyS8
crw-rw----  1 root dialout   4,  73 May 10 10:02 ttyS9
crw-------  1 root root     10, 239 May 10 10:02 uhid
crw-------  1 root root     10, 223 May 10 10:02 uinput
crw-rw-rw-  1 root root      1,   9 May 10 10:02 urandom
crw-rw----  1 root tty       7,   0 May 10 10:02 vcs
crw-rw----  1 root tty       7,   1 May 10 10:02 vcs1
crw-rw----  1 root tty       7,   2 May 10 10:02 vcs2
crw-rw----  1 root tty       7,   3 May 10 10:02 vcs3
crw-rw----  1 root tty       7,   4 May 10 10:02 vcs4
crw-rw----  1 root tty       7,   5 May 10 10:02 vcs5
crw-rw----  1 root tty       7,   6 May 10 10:02 vcs6
crw-rw----  1 root tty       7,   7 May 10 10:02 vcs7
crw-rw----  1 root tty       7, 128 May 10 10:02 vcsa
crw-rw----  1 root tty       7, 129 May 10 10:02 vcsa1
crw-rw----  1 root tty       7, 130 May 10 10:02 vcsa2
crw-rw----  1 root tty       7, 131 May 10 10:02 vcsa3
crw-rw----  1 root tty       7, 132 May 10 10:02 vcsa4
crw-rw----  1 root tty       7, 133 May 10 10:02 vcsa5
crw-rw----  1 root tty       7, 134 May 10 10:02 vcsa6
crw-rw----  1 root tty       7, 135 May 10 10:02 vcsa7
crw-------  1 root root     10,  63 May 10 10:02 vga_arbiter
crw-------  1 root root     10, 137 May 10 10:02 vhci
crw-------  1 root root     10, 238 May 10 10:02 vhost-net
crw-------  1 root root     10,  57 May 10 10:02 vmci
crw-rw-rw-  1 root root      1,   5 May 10 10:02 zero
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ cat /proc/devices 
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  4 ttyS
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  5 ttyprintk
  6 lp
  7 vcs
 10 misc
 13 input
 21 sg
 29 fb
 99 ppdev
108 ppp
116 alsa
128 ptm
136 pts
180 usb
189 usb_device
216 rfcomm
226 drm
251 hidraw
252 bsg
253 watchdog
254 rtc

Block devices:
  1 ramdisk
  2 fd
259 blkext
  7 loop
  8 sd
  9 md
 11 sr
 65 sd
 66 sd
 67 sd
 68 sd
 69 sd
 70 sd
 71 sd
128 sd
129 sd
130 sd
131 sd
132 sd
133 sd
134 sd
135 sd
252 device-mapper
253 virtblk
254 mdp
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ ls /dev/ -l |grep misc
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/ch06_02--misc_register/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/ch06_02--misc_register/misc_register.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/ch06_02--misc_register/misc_register.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/ch06_02--misc_register/misc_register.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ ls 
built-in.o  misc_register.c   misc_register.mod.c  misc_register.o  Module.symvers
Makefile    misc_register.ko  misc_register.mod.o  modules.order    readme.txt
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ ls -ltr
total 48
-rw-rw-r-- 1 wu-being wu-being    25 May 10 11:33 Makefile
-rw-rw-r-- 1 wu-being wu-being 15859 May 10 11:52 readme.txt
-rw-rw-r-- 1 wu-being wu-being     8 May 10 11:52 built-in.o
-rw-rw-r-- 1 wu-being wu-being     0 May 10 11:53 Module.symvers
-rw-rw-r-- 1 wu-being wu-being   681 May 10 11:54 misc_register.c
-rw-rw-r-- 1 wu-being wu-being  2272 May 10 11:54 misc_register.o
-rw-rw-r-- 1 wu-being wu-being    86 May 10 11:54 modules.order
-rw-rw-r-- 1 wu-being wu-being   870 May 10 11:54 misc_register.mod.c
-rw-rw-r-- 1 wu-being wu-being  1968 May 10 11:54 misc_register.mod.o
-rw-rw-r-- 1 wu-being wu-being  3158 May 10 11:54 misc_register.ko
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 


wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ sudo insmod misc_register.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ lsmod |grep misc
misc_register          12510  0 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ ls /dev/ -l |grep misc
crw-------  1 root root     10,  56 May 10 11:56 misc_register
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 
wu-being@ubuntu:~/code/linux_driver_study/ch06_02--misc_register$ 



