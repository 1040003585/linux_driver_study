
```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ make -C /usr/src/linux-headers-3.13.0-32-generic/ M=/home/wu-being/code/linux_driver_study/song06--Character-devices/Character-devices-Test/
make: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/Character-devices-Test/Character-devices-test.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/code/linux_driver_study/song06--Character-devices/Character-devices-Test/Character-devices-test.mod.o
  LD [M]  /home/wu-being/code/linux_driver_study/song06--Character-devices/Character-devices-Test/Character-devices-test.ko
make: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'


```

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo insmod Character-devices-test.ko insmod: ERROR: could not insert module Character-devices-test.ko: Device or resource busy
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo insmod Character-devices-test.ko ^C
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo dmesg -c|grep character_devices
[342090.740202] [character_devices] character_devices_init *chrdev_region fail: -16.
[342094.556558] [character_devices] character_devices_init *chrdev_region fail: -16.
[342239.103147] [character_devices_test] character_devices_test_init *chrdev_region fail: -16.
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 


wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ sudo rmmod Character-devices
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/2.Character-devices$ 


wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo insmod Character-devices-test.ko 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ sudo dmesg -c|grep character_devices
[342497.025293] [character_devices] character_devices_exit sucess
[342509.273300] [character_devices_test] character_devices_test_init sucess
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices/Character-devices-Test$ 

```

