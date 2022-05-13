>在 Linux 2.6 内核中，可使用 request_module(const char *fmt,…)函数加载内核模块，驱动开发人员可通过调用request_module(module_name);
如：request_module("fb%d", fbidx);来加载其他内核模块。fbidx是%d的参数。是子设备号。

在什么时候使用这个函数呢？

> 驱动设备子系统中，以一个主设备管理所有的次设备的f_ops操作函数接口及其实现。当应用程序需要使用某个显示屏显示数据，就会打开对应的次设备的设备节点，但是这时候设备节点没有加载进入内核，打开会失败。
\
驱动设备文件打开的过程是根据主设备号调用驱动的open函数接口，往往设备子系统分别同类型的不同设备使用的是次设备号，次设备号作为描述设备的结构链表的下标索引出对应的结构体，具体的操作就就是在这里开始的。

>每个次设备都有自己的一个设备节点，但是没有被加载进入内核，所以request_module("fb%d", fbidx);在调用主设备号之后，使用次设备之前，根据次设备号加载对应的设备节点。

例子：
```c
static int
fb_open(struct inode *inode, struct file *file)
__acquires(&info->lock)
__releases(&info->lock)
{
	int fbidx = iminor(inode);
	struct fb_info *info;
	int res = 0;
 
	if (fbidx >= FB_MAX)
		return -ENODEV;
	info = registered_fb[fbidx];//加载设备节点到内核
	if (!info)
		request_module("fb%d", fbidx);
	info = registered_fb[fbidx];
	if (!info)
		return -ENODEV;
	mutex_lock(&info->lock);
	if (!try_module_get(info->fbops->owner)) {
		res = -ENODEV;
		goto out;
	}
	file->private_data = info;
	if (info->fbops->fb_open) {
		res = info->fbops->fb_open(info,1);
		if (res)
			module_put(info->fbops->owner);
	}
#ifdef CONFIG_FB_DEFERRED_IO
	if (info->fbdefio)
		fb_deferred_io_open(info, inode, file);
#endif
out:
	mutex_unlock(&info->lock);
	return res;
```

————————————————
版权声明：本文为CSDN博主「pangyinglong」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/pangyinglong/article/details/98893789