
```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template/Character-devices.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template/Character-devices.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template/Character-devices.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ dmesg |grep character_devices
[341071.563297] [character_devices_tmp] character_devices_tmp_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ cat /proc/devices 
Character devices:
...
230 globalmem_name1
...

wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ cat /proc/devices 
Character devices:
...
230 globalmem_name1
231 globalmem_name1



```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ ls /dev/ -l |grep globalmem
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ ls /dev/ -l |grep device
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/1.Character-devices-Template$ 
```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo mknod /dev/glabal c 230 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ ls /dev -l |grep glabal
crw-r--r--  1 root root    230,   0 May 17 00:10 glabal
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo mknod /dev/glabal-1 c 230 1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ ls /dev -l |grep glabal
crw-r--r--  1 root root    230,   0 May 17 00:10 glabal
crw-r--r--  1 root root    230,   1 May 17 00:10 glabal-1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo mknod /dev/glabal1-1 c 231 1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ ls /dev -l |grep glabal
crw-r--r--  1 root root    230,   0 May 17 00:10 glabal
crw-r--r--  1 root root    230,   1 May 17 00:10 glabal-1
crw-r--r--  1 root root    231,   1 May 17 00:11 glabal1-1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 


wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo mknod /dev/glabal1-1 c 231 0
mknod: ‘/dev/glabal1-1’: File exists
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo mknod /dev/glabal1-0 c 231 0
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ ls /dev -l |grep glabal
crw-r--r--  1 root root    230,   0 May 17 00:10 glabal
crw-r--r--  1 root root    230,   1 May 17 00:10 glabal-1
crw-r--r--  1 root root    231,   0 May 17 00:12 glabal1-0
crw-r--r--  1 root root    231,   1 May 17 00:11 glabal1-1
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 

```

xs
