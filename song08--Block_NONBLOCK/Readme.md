

# 阻塞和非阻塞I/O

**阻塞操作**是指在执行设备操作时，若不能获得资源，则挂起进程直到满足可操作的条件后再进行操作。被挂起的进程进人睡眠状态，被从调度器的运荷队列移走，直到等待的条件被满足。

**非阻塞操作**的进程在不能进行设备操作时，并不挂起，它要么放弃，要么不停地查询，直至可以进行操作为止。

在阻塞访问时，不能获取资源的进程将进人休眠，它将 CPU 资源“礼让”给其他进程。因为阻塞的进程会进入休眠状态，所以必须确保有个地方能够唤醒休眠的进程，否则，进程就真的“寿终正寝”了。
唤醒进程的地方最大可能发生在中断里面，因为在硬件资源获得的同时往往伴随着一个中断。而非阻塞的进程则不断尝试，直到可以进行 IO 。

![阻塞和非阻塞I/O](https://img-blog.csdnimg.cn/740a7e41b5d345a4b7603cdd84e9222c.png)


## 1. 等待队列

Linux 驱动程序中，可以使用**等待队列（Wait Queue）**来实现阻塞进程的唤醒。
它以队列为基础数据结构，与进程调度机制紧密结合，可以用来同步对系统资源的访问，信号量在内核中也依赖等待队列来实现。

**例子**：`drivers/power/supply/mediatek/charger/mtk_charger.c` *（code来源Github）*
```c
void _wake_up_charger(struct charger_manager *info)
{
	unsigned long flags;

	if (info == NULL)
		return;

	spin_lock_irqsave(&info->slock, flags);
	if (!info->charger_wakelock.active)
		__pm_stay_awake(&info->charger_wakelock);
	spin_unlock_irqrestore(&info->slock, flags);
	info->charger_thread_timeout = true;
	wake_up(&info->wait_que);
}
...

static int charger_routine_thread(void *arg)
{
	struct charger_manager *info = arg;
	unsigned long flags;
	bool is_charger_on;
	int bat_current, chg_current;

	while (1) {
		wait_event(info->wait_que,
			(info->charger_thread_timeout == true));

		mutex_lock(&info->charger_lock);
		spin_lock_irqsave(&info->slock, flags);
		if (!info->charger_wakelock.active)
			__pm_stay_awake(&info->charger_wakelock);
		spin_unlock_irqrestore(&info->slock, flags);

		info->charger_thread_timeout = false;
	...
	
static int mtk_charger_probe(struct platform_device *pdev)
{
	init_waitqueue_head(&info->wait_que);
```

wait_event()和 wait_event_interruptible(), 前者不能被信号唤醒，后者可以。

wake_up()和 wake_up_interruptible() 操作会唤醒以 queue 作为等待队列头部的队列中所有的进程。 

1. wake_up() 应该与 wait_event()或 wait_event_timeout() 成对使用；
2. wake_up_interruptible()则应与 wait_event_interruptible()或 wait_event_interruptible_timeout() 成对使用。 

- wake_up() 可唤醒处于 TASK_INTERRUPTIBLE 和 TASK_UNINTERRUPTIBLE 的进程;
- wake_up_interruptible()只能唤醒处于 TASK_INTERRUPTIBLE 的进程。


**在等待队列上睡眠**
```c
sleep_on(wait_queue_head_t * q ); 
interruptible_sleep_on(wait_queue_head_t * q); 
```

`sleep_on()`函数的作用就是将目前进程的状态置成 TASK UNINTERRUPTIBLE ，并定义一个等待队列元素，之后把它挂到等待队列头部 q 指向的双向链表，直到资源可获得， q 队列指向链接的进程被唤醒。 

`interruptible_sleep_on()`与 sleep_on()函数类似，其作用是将目前进程的状态置成 TASK INTERRUPTIBLE ，并定义一个等待队列元素，之后把它附属到 q 指向的队列，直到资源可获得（ q 指引的等待队列被唤醒）或者进程收到信号。 
 
- sleep_on()函数应该与 wake_up()成对使用；
- interruptible_sleep_on()应该与wake_up_interruptible()成对使用。
 
代码清单8.3演示了一个在设备驱动中使用等待队列的模版，在进行写 I / o 操作的时候，判断设备是否可写，如果不可写且为阻塞 I / O ，则进程睡眠并挂起到等待队列。代码洁单83在设各吸动山估田竺烛 RI 万 l

## 2. 轮询操作

