
# Linux 驱动的软件架构

Linux 设备驱动非常重视软件的可用性和跨平台能力。

**1. Linux 设备和驱动的分离**

把设备端的信息从驱动里剥离出来，让驱动以某种标准化的方法拿到这些信息。即Linux的总线、设备和驱动模型，总线负责匹配设备和驱动，驱动以标准的途径拿到板级信息。
![Linux 设备和驱动的分离](https://img-blog.csdnimg.cn/3a6bbf3e1e404150822dcccfcd0c0b85.png  =500x)

**2. Linux 驱动的分层**

如输入子系统，提炼一个Input的核心层，把Linux 接口和整个input事件的汇报机制都实现在这里。
![Linux 驱动的分层](https://img-blog.csdnimg.cn/a21ee2ca3d7c4eb38db2f035e0f510b1.png  =500x)

**3. Linux 设备驱动的主机、外设驱动分离**

主机控制器驱动不关心外设，外设驱动也不关心主机，只是通过核心层的通用API进行数据传输。如果有m个主机控制器、n个外设，分离的结果就是m+n 个驱动，不分离就是m*n个驱动。
![Linux 设备驱动的主机、外设驱动分离](https://img-blog.csdnimg.cn/c5640a3b0dbe4044a6629aa6a00d0441.png  =700x)


**附PPT**： https://www.renrendoc.com/paper/175198950.html

**相关代码**：[Softwave-Architecture](https://github.com/1040003585/linux_driver_study/tree/main/song12--Softwave-Architecture)


**我的博客原文**：[Linux 驱动的软件架构](https://blog.csdn.net/u014134180/article/details/124899401)