
# Linux Devices Classification

Linux Devices include Character devices and Block devices, Network devices.


## Character devices 

The  "10 misc" devices is from "ch06_02--misc_register" to "ch06_05--word_count_userspace".

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

## Block devices

```
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices$ cat /proc/devices 
...
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
wu-being@ubuntu:~/code/linux_driver_study/song06--Character-devices$ 

```
