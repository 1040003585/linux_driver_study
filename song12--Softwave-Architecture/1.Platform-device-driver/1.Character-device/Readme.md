```
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ make
make -C /usr/src/linux-headers-3.13.0-32-generic         M=/home/wu-being/.../1.Character-device              modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-32-generic'
  CC [M]  /home/wu-being/.../1.Character-device/character-device_p.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/wu-being/.../1.Character-device/character-device_p.mod.o
  LD [M]  /home/wu-being/.../1.Character-device/character-device_p.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-32-generic'
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ sudo insmod character-device_p.ko 
[sudo] password for wu-being: 
wu-being@ubuntu:~/.../1.Character-device$ 
wu-being@ubuntu:~/.../1.Character-device$ 

```

```
wu-being@ubuntu:~/.../1.Character-device$ ls /sys/bus/platform/drivers/
88pm860x-regulator/ ehci-platform/      lp8788-buck/        palmas-gpio/        sram/               tps65910-gpio/
alarmtimer/         floppy/             lp8788-dldo/        pmic_gpio/          stmpe-gpio/         uart-sccnxp/
byt_gpio/           i8042/              lp_gpio/            rc5t583-gpio/       syscon/             vesa-framebuffer/
charger-manager/    intel_msic/         mdio-gpio/          reg-dummy/          tc3589x-gpio/       virtio-mmio/
clk-lpt/            ipmi/               msic_gpio/          serial8250/         timb-gpio/          xgene-rtc/
efi-framebuffer/    lp8788-aldo/        ohci-platform/      simple-framebuffer/ tps6586x-gpio/      xhci-hcd/
wu-being@ubuntu:~/.../1.Character-device$ ls /sys/bus/platform/devices/
alarmtimer/                Fixed MDIO bus.0/          microcode/                 reg-dummy/                 
character_device+driver_p/ floppy.0/                  pcspkr/                    serial8250/                
eisa.0/                    i8042/                     platform-framebuffer.0/    
wu-being@ubuntu:~/.../1.Character-device$ ls /sys/bus/platform/devices/character_device+driver_p/ -l
total 0
-r--r--r-- 1 root root 4096 May 21 22:36 modalias
drwxr-xr-x 2 root root    0 May 21 22:36 power
lrwxrwxrwx 1 root root    0 May 21 22:36 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 May 21 22:36 uevent
wu-being@ubuntu:~/.../1.Character-device$ ls /sys/devices/
breakpoint/  LNXSYSTM:00/ platform/    pnp1/        software/    tracepoint/  
isa/         pci0000:00/  pnp0/        rapidio/     system/      virtual/     
wu-being@ubuntu:~/.../1.Character-device$ ls /sys/devices/platform/character_device+driver_p/ -l
total 0
-r--r--r-- 1 root root 4096 May 21 22:36 modalias
drwxr-xr-x 2 root root    0 May 21 22:36 power
lrwxrwxrwx 1 root root    0 May 21 22:36 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 May 21 22:36 uevent
wu-being@ubuntu:~/.../1.Character-device$ 


```

