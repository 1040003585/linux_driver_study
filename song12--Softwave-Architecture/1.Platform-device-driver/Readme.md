
# platform 设备驱动

Soc 集成了一些独立外设的控制器和挂在SoC内存空间的外设等不依赖与PCI/USB/I2C/SPI等设备总线，Linux 发明了一种虚拟总线，称为platform 总线。

对应的设备叫做platform_device，对应的驱动叫做platform_driver。

platform_device 并不是字符设备、块设备和网络设备等并列概念，而是linux 提供的附加手段，比如Soc 内部集成的I2C、RTC、LCD、看门狗等控制器都归纳为platform_device，他们本身就是字符设备。