# 输入设备驱动

输入设备（如按键、键盘、触摸屏、鼠标等）是**典型的字符设备**。
**工作机理** 是底层在按键、触摸等动作发送时产生一个中断（或驱动通过 Timer 定时查询），然后 CPU 通过 SPI 、 I2C 或外部存储器总线读取键值、坐标等数据，并将它们放人一个缓冲区，字符设备驱动管理该缓冲区，而驱动的 read() 接口让用户可以读取键值、坐标等数据。

显然，在这些工作中，只是中断、读键值／坐标值是与设备相关的，而输入事件的缓冲区管理以及字符设备驱动的 file operations 接口则对输入设备是通用的。
基于此，内核设计了输入子系统，由核心层处理公共的工作。

![在这里插入图片描述](https://img-blog.csdnimg.cn/fc7a87497e8146ffb069586f95523f5f.png#pic_center)

**相关code 参考**：[https://wu-being.blog.csdn.net/article/details/78394721](https://wu-being.blog.csdn.net/article/details/78394721)

**我的博客原文**：[输入设备驱动](https://blog.csdn.net/u014134180/article/details/124914859)

