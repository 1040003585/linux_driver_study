
# misc 杂项设备

有些设备不像Input/rtc/framebuffer/tty等具体设备有归属类型可以套用框架，这些设备都叫杂项misc 设备。
在misc_init()确定了miscdevice 的主设备号固定是10，次设备号在注册misc 可自定义，也可以随意分配。

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices$ cat /proc/devices 
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  4 ttyS
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  5 ttyprintk
  7 vcs
 10 misc
 13 input
 21 sg
 29 fb
108 ppp
128 ptm
136 pts
180 usb
189 usb_device
251 hidraw
252 bsg
253 watchdog
254 rtc
...

```

本章节两个例子中，分别insmod 各自ko文件（无先后顺序），分别会注册platfrom device 和platform driver.
如果platfrom device的name 和platform driver的driver.name 通过platfrom_match 匹配一致，则会运行driver 的probe 函数，根据代码创建/dev/xxx misc设备。


**如下用各自的名字是无法匹配**

misc-platform_device

```
ls /sys/devices/platform/ -l
...
drwxr-xr-x 3 root root    0 May 20 14:58 misc_platform_device-name

ls /sys/bus/platform/devices/ -l
...
lrwxrwxrwx 1 root root 0 May 20 15:03 misc_platform_device-name -> ../../../devices/platform/misc_platform_device-name

ls /sys/devices/platform/misc_platform_device-name/ -l
...
lrwxrwxrwx 1 root root    0 May 20 15:02 subsystem -> ../../../bus/platform
```

misc-platform_driver

```
ls /sys/bus/platform/drivers/ -l
...
drwxr-xr-x 2 root root    0 May 20 16:47 misc_platform_driver-name/

ls /sys/bus/platform/drivers/misc_platform_driver-name/ -l
...
lrwxrwxrwx 1 root root    0 May 20 16:47 module -> ../../../../module/misc_platform_driver

```


**如下用相同的名字是可以匹配**

misc-platform_driver

```
ls /sys/bus/platform/drivers/ -l
...
drwxr-xr-x 2 root root    0 May 20 17:09 misc_platform_device+driver-name/   

ls /sys/bus/platform/drivers/misc_platform_device+driver-name/ -l
...
lrwxrwxrwx 1 root root    0 May 20 17:09 misc_platform_device+driver-name -> ../../../../devices/platform/misc_platform_device+driver-name
lrwxrwxrwx 1 root root    0 May 20 17:08 module -> ../../../../module/misc_platform_driver

```

misc-platform_device

```
ls /sys/devices/platform/misc_platform_device+driver-name/ -l
...
lrwxrwxrwx 1 root root    0 May 20 17:08 driver -> ../../../bus/platform/drivers/misc_platform_device+driver-name
lrwxrwxrwx 1 root root    0 May 20 17:18 subsystem -> ../../../bus/platform

ls /dev/ |grep misc
misc_platform_driver_miscdeviceNAME
```