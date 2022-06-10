
# timer_list

timer_list 定时器的到期时间往往是在目前 jifies 的基础上添加一个时延，若为 Hz 、则表示延迟1s。
在定时器处理函数中，在完成相应的工作后，往往会延后 expires 并将定时器再次添加到内核定时器链表中，以便定时器能再次被触发。

```c
struct timer_list {
	/*
	 * All fields that change during normal runtime grouped to the
	 * same cacheline
	 */
	struct hlist_node	entry;
	unsigned long		expires;
	void			(*function)(struct timer_list *);
	u32			flags;

#ifdef CONFIG_LOCKDEP
	struct lockdep_map	lockdep_map;
#endif

};
```

如下是个例子模板：

```c

/*second设备结构体*/
struct xxx_dev {
  struct cdev cdev;				 /*cdev结构体*/
  ...
  struct timer_list xxx_timer;   /*设备要使用的定时器*/
};

//xxx驱动中某open 函数
int xxx_open(...)  {

  struct xxx_dev *dev = filp->private_data; 
  ...
  /*初始化定时器*/ 
  init_timer(&dev->xxx_timer); 
  dev->xxx_timer.function = &xxx_do_timer; 
  dev->xxx_timer.data = (unsigned long)dev; 
  dev->xxx_timer.expires = jiffies + delay;

  /*添加（注册）定时器*/ 
  add_timer(&dev->xxx_timer);
  ... 
  return 0; 
}

//驱动中某release 函数
int xxx_release(...) {
  ...
  del_timer(&second_devp->s_timer);
  ... 
}

//定时器处理函数
static void xxx_do_timer(unsigned long arg)  {

  struct xxx_device *dev = (struct xxx_device *)(arg);
  ...
  //调度定时器再执行
  dev->xxx_timer.expires = jiffies + delay;
  add_timer(&dev->xxx_timer);
  
  // or mod_timer
  //mod_timer(&dev->xxx_timer, jiffies + delay)
}
```

另外，
del_timer_sync 是del_timer 的同步版，表示等待定时器处理完才删除，不能用于中断上下文。