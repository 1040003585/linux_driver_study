@[toc]
# 中断概念和分类

中断是指 CPU 在执行程序的过程中，出现了某些突发事件急待处理， CPU 必须暂停当前程序的执行，转去处理突发事件，处理完毕后又返回原程序被中断的位置继续执行。

- 根据中断的来源，中断可分为内部中断和外部中断，内部中断的中断源来自 CPU 内部（软件中断指令、溢出、除法错误等，例如，操作系统从用户态切换到内核态需借助 CPU 内部的软件中断），外部中断的中断源来自 CPU 外部，由外设提出请求。
- 根据中断是否可以屏蔽，中断可分为可屏蔽中断与不可屏蔽中断（ NMI )，可屏蔽中断可以通过设置中断控制器寄存器等方法被屏蔽，屏蔽后，该中断不再得到响应，而不可屏蔽中断不能被屏蔽。
- 根据中断入口跳转方法的不同，中断可分为向量中断和非向量中断。采用向量中断的 CPU 通常为不同的中断分配不同的中断号，当检测到某中断号的中断到来后，就自动跳转到与该中断号对应的地址执行。不同中断号的中断有不同的入口地址。非向量中断的多个中断共享一个入口地址，进入该入口地址后，再通过软件判断中断标志来识别具体是哪个中断。

在 ARM 多核处理器里最常用的中断控制器是 GIC ( Generic Interrupt Controller )，如下图所示，它支持3种类型的中断。
![ARM 中断控制器是 GIC](https://img-blog.csdnimg.cn/50871a005ae544149939b1ba5a24e680.png)

- SGI ( Software Generated Interrupt )：软件产生的中断，可以用于多核的核间通信。一个 CPU 可以通过写 GIC 的寄存器给另外一个 CPU 产生中断。多核调度用的 IPI WAKEUP IPI_TIMER 、 IPI_RESCHEDULE 、 IPI_CALL_FUNC 、 IPI_CALL_FUNC_SINGLE 、 IPI_CPU_STOP 、 IPI_IRQ_WORK 、 IPI_COMPLETION 都是由 SGI 产生的。 
- PPI ( Private Peripheral Interrupt )：某个 CPU 私有外设的中断，这类外设的中断只能发给绑定的那个 CPU 。 
- SPI ( Shared Peripheral Interrupt )：共享外设的中断，这类外设的中断可以路由到任何一个 CPU 。

对于 SPI 类型的中断，内核可以通过如下 API 设定中断触发的 CPU 核： 
```c
extern int irq_set_affinity ( unsigned int irg , const struct cpumask * m );
```

在 ARM Linux 默认情况下，中断都是在CPU0上产生的，比如，我们可以通过如下代的把中断 irq 设定到 CPUi 上去： 
```c
irq_set_affinity ( irq , cpumask_of ( i ));
```

# Linux 中断处理程序架构

设备的中断会打断内核进程中的正常调度和运行，系统对更高春吐率的迫求势必要求中服务程序尽址短小精悍。
但是，这个良好的愿望往往与现实并不吻合。在大多数真实的系统中。当中断到来时。要完成的工作往往并不会是短小的，它可能要进行较大量的耗时处理。

下图描述了 Linux 内核的中断处理机制。为了在中断执行时间尽量短和中斯处理需完成的工作尽量大之间找到一个平衡点， Linux 将中断处理程序分解为两个半部：**顶半部（ Top Half )和底半部（ Botom Half )**。
![Linux 中断处理机制](https://img-blog.csdnimg.cn/047014287a284b0ca94032fb943c9886.png)

顶半部用于完成尽量少的比较紧急的功能，它往往只是简单地读取寄存器中的中断状态，并在清除中断标志后就进行“登记中断＂的工作。“登记中断”意味着将底半部处理程序挂到该设备的底半部执行队列中去。
这样，顶半部执行的速度就会很快，从而可以服务更多的中断请求。

现在，中断处理工作的重心就落在了底半部的头上，需用它来完成中断事件的绝大多数任务。**底半部几乎做了中断处理程序所有的事情、而且可以被新的中断打断，这也是底半部和顶半部的最大不同。**
**因为顶半部往往被设计成不可中断**。底半部相对来说并不是非常紧急的，而且相对比较耗时，不在硬件中断服务程序中执行。

尽管顶半部、底半部的结合能够改善系统的响应能力，但是，僵化地认为 Linux 设备驱动中的中断处理一定要分两个半部则是不对的。
如果中断要处理的工作本身很少，则完全可以直接在顶半部全部完成。

> 其他操作系统中对中断的处理也采用了类似于 Linux 的方法，真正的硬件中断服务程序都应该尽量短。
因此，许多操作系統都提供了中断上下文和非中断上下文相结合的机制，将中断的耗时作保留到韭中断上下文去执行。
例如，在 VxWorks 中，网络设备包接收中断到来后，中断服务程序会通过netJobAdd 函数将耗时的包接收和上传工作交给 tNetTask 任务去执行。

在Linux，可以用如下节点查看系统中断统计信息：
![系统中断统计信息 /proc/interrrupts](https://img-blog.csdnimg.cn/2af6d4e5d26b4250a5c86e636452a06f.png)

# Linux 中断编程

## 申请和释放中断

在 Linux 设备驱动中，使用中断的设备需要申请和释放对应的中断，并分别使用内核提供的 request irq 和 free_irq 函数。

**1．申请 irq**

```c
int request_irq ( unsigned int irq , irq_handler_t handler , unsigned long flags , const char * name , void * dev ); 
```
- irq 是要申请的硬件中断号。
- **handler 是向系统登记的中断处理函数（顶半部）** 是一个回调函数，中断发生时，系统调用这个函数， dev 参数将被传递给它。
- irqflags 是中断处理的属性，可以指定中断的触发方式以及处理方式。

1. 在触发方式方面，可以是 IRQF_TRIGGER_RISNG 、 IRQF_TRIGGER_FALLING 、 IRQF_TRIGGER_HIGH 、 IRQF_TRIGGER_LOW 等。
2. 在处理方式方面，若设置了 IRQF SHARED ，则表示多个设备共享中断、 dev 是要传递给中断服务程序的私有数据，一般设置为这个设备的设备结构体或NULL

- request irq 返回0表示成功，
- 返回-EINVAL 表示中断号无效或处理函数指针为 NULL ,
- 返回-EBUSY 表示中断已经被占用且不能共享。 

```c
int devm_request_irq ( struct device * dev , unsigned int irq , irq_handler_t handler , unsigned long irqflags , const char * devname , void * dev id );
```

**此函数与 request_irq  的区别是 devm 我头的 API 申请的是内核“ managed ”的资源，一般不需要在出错处理和 remove 接口里再显式的释放。有点类似 Java 的垃圾回收机制。**

顶半部 handler 的类型 irq_handler_t 定义为：

```c
 typedef irqreturn_t (* irq_handler_t )( int , void *): 
 typedef int irqreturn_t ;
```
 
**2.释放**
 
释放 irq 与 request_irq  相对应的函数为 free_irq  , free_irq 的原型为： 
```c
 void free_irq ( unsigned int irq , void * dev_id ); 
```
free_irq 中参数的定义与 request irq 相同。
 
## 使能和屏蔽中断

下列3个函数用于屏蔽一个中断源： 
```c
void disable_irq ( int irq ); 
void disable_irq_nosync ( int irg ): 
void enable_irq ( int irq ); 
```

disable_irq_nosync 与 disable_irq 的区别在于前者立即返回，而后者等待目前的中断处理完成。
由于 disable_irq 会等待指定的中断被处理完，**因此如果在 n 号中断的顶半部调用 disable_irq( n )，会引起系统的死锁，这种情况下，只能调用 disable_irq_nosync ( n )。**

下列两个函数（或宏，具体实现依赖于 CPU 的体系结构）将屏蔽本 CPU 内的所有中断： 

```c
#define local_irq_save ( flags ).
void local_irq_disable ( void );
```

 前者会将目前的中断状态保留在 flags 中（注意 flags 为 unsigned long 类型，被直接传遗，而不是通过指针），后者直接禁止中断而不保存状态。
 
 与上述两个禁止中断对应的恢复中断的函数（或宏）是： 

```c
 #define local_irq_restore ( flags ),
 void local_irq_enable ( void );
```

***以上各以 local_ 开头的方法的作用范围是本 CPU***

## 底半部机制

 Linux 实现底半部的机制主要有 tasklet 、工作队列、软中断和线程化 irq 。
 
### 1. tasklet

 tasklet 的便用较简单，**它的执行出下文是软中断**，执行时机通常是顶半部返回的时候。
 我们只需要定义 tasklet 及其处理函数，并将两者关联则可，例如： 
 
```c
 void my_tasklet_func ( unsigned 1onq) //定义一个处理函数 
 DECLARE TASKLEТ(mу_tasklet, my_tasklet_func , data ) //定义一个task1et 结构 my_task1et，与 my_tasklet_func ( data ）函数相关联
```

 代码 DECLARE_TASKLET ( my_tasklet , my_tasklet_func , data ）实现了定义名称为 my_tasklet 的 tasklet ，并将其与 my_tasklet_func 这个函数绑定，而传人这个函数的参数为 data 。
 
 在需要调度 tasklet 的时候引用一个 tasklet_schedule 函数就能使系统在适当的时候进行调度运行： 
 
```c
tasklet_schedule ( &mу_tasklet ) 
```
 
 使用 tasklet 作为底半部处理中断的设备驱动程序模板如代码清单所示（仅包含与中断相关的部分）。
 
 如下代码清单tasklet 使用模板: 

```c
 // 定义 tasklet 和底半部函数并将它们关联 
 void xxx_do_tasklet ( unsigned 1ong) 
 DECLARE_TASKLET ( xxx_tasklet , xxx_do_tasklet , 0)
 
 //中断处理底半部头
 void xxx_do_tasklet ( unsigned long )
 {
 ...
 }
 
 //中断处理顶半部 
 irqreturn_t xxx_interrupt ( int irq , void * dev_id )
 {
 ...
 tasklet_schedule (&xxx_tasklet )
 ...
 }
 
 //设备駆动模块加载函数內 
 int __init xxx_init ( void )
 {
 //申请中断
 result = request_irq ( xxx_irq , xxx_interrupt , 0 , " xxx " , NULL ); 
 ...
 return IRQ_HANDLED ;
 }
 
 //设备驱动模块卸载函数
 vold __exit xxx_exit ( void )
 {
 ...
 // 释放中断
 free_irq (xxx_irq , xxx_interrupt)
 ...
 }
 
```


### 2. 工作队列

工作队列的使用方法和 tasklet 非常相似，**但是工作队列的执行上政是内核线程，因此可以调度和睡眠。**
下面的代码用于定义一个工作队列和一个底半部执行函数： 
```c
struct work_struct my_wq;  //定义一个工作队列
void my_wq_func ( struct work_struct * work ) //定义一个处理面数
```

通过 INIТ_WORK 可以初始化这个工作队列并将工作队列与处理函数绑定： 
```
INIТ_WORK (&my_wq , my_wq_func ) // 初始化工作队列并将其与处理函数綁定·1
```
与 tasklet_schedule 对应的用于调度工作队列执行的函数为 schedule_work ，如： 
```c
schedule_work (&my_wq)  //调度工作队到执行
```

与代码清单tasklet对应的使用工作队列处理中断底半部的设备驱动程序模板如下代码清单所示（仅包含与中断相关的部分）。
如下代码清单工作队列使用模板：

```c
// 定义工作队列和关联函数 
struct work_struct xxx_wq
void xxx_do_work ( struct work_struct * work )

// 中断处理底半部
void xxx_do_work ( struct work_struct * work )
{
...
}

// 中新处理頂半部
irqreturn_t xxx_interupt ( int irq , void * dev_id )
{
...
schedule_work (&xxx_wq)
return IRQ_HANDLED;
...
}

// 设备駆动模块加载函数 
int xxx_init ( void )
{
...
// 申请中断 
result = request_irq( xxx_irq , xxx_interupt , 0 , " xxx ", NULL );

// 初始化工作队列 
INIТ_WORK(&xxx_wq, xxx_do_work ):
...
}

// 设备駆动模块卸載面数  
void xxx_exit ( void ) 
{
...
// 释放中断
free_irq ( xxx_irq , xxx_interrupt );
...
}

```

上述程序在设计驱动模块加载函数中增加了初始化工作队列的代码。

**工作队列早期的实现是在每个 CPU 核上创建一个 worker 内核找程，所有在这个核上调度的工作都在该 worker 线程中执行**，其并发性显然差强人意。
在 Linux 2.6.36以后，转而实现了“ Concurrency - managed workqueues "，简称 `cmwq` , cmwq 会自动维护工作队列的线程池以提高并发性，同时保持了 API 的向后兼容。

### 3. 软中断

软中断（ Softirq ）也是一种传统的底半部处理机制，它的执行时机通常是顶半部返回的时候， **tasklet 是基于软中断实现的，因此也运行于软中断上下文**。

在 Linux 内核中，用 softirq_action 结构体表征一软中断这个结构体包含软中断处理函数指针和传递给该函数的参数。
使用 open_softirq 函数可以注册软中断对应的处理函数，而 raise_softirq 函数可以触发一个软中断。

**软中断和 tasklet 运行于软中断上下文，仍然属于原于上下文的一种，而工作队列则运行于进程上下文。因此，在软中断和 tasklet 处理函数中不允许睡眠，而在工作队列处理函数中允许睡眠。**

`local_bh_disable` 和 `local_bh_enable` **是内核中用于禁止和使能软中断及 tasklet 底半部机制的函数。**

内核中果用 softirg 的地方包括 HI_SOFTIRQ 、 TIMER_SOFTIRQ 、 NET_TX_SOFTIRQ、 NET_RX_SOFTIRQ 、 SCSI_SOFTIRQ 、 TASKLET_SOFTIRQ 等。

一般来说，驱动的编程不会也不宜直接使用 softirq 。异步通知所基于的信号也类似于中断。


**总结一硬中断、软中断和信号区别：**：

***硬中断是外部设备对 CPU 的中断，软中断是中断底半部的一种处理机制，而信号蒯息由内核（或其他进程）对某个进程的中断。***

在涉及系统调用的场合，人们也常说通过软中斯（例如 ARM 为 `swi` ）陷人内核，此时软中断的概念是指由软件指令引发的中断，和我们这个地方说的 softirq 是两个完全不同的概念，一个是 software ，一个是 soft 。

需要特别说明的是，软中断以及基于软中断的 tasklet 如果在某段时间内大量出现的话内核会把后续软中断放人 ksoftirqd 内核线程中执行。

**总的来说，中断优先级高于软中断，软中断又高于任何一个线程。软中断适度线程化，可以级解高负载情况下系统的响应。**


### 4. threaded irq

在内核中，除了可以通过 request_irq 、 devm_request_irq 申请中断以外，还可以通过 request_threaded_irq 和 devm_request_threaded_irq 申请。
这两个函数的原型为： 
```c
int request_threaded_irq(unsigned int irq, irq_handler_t handler,
			 irq_handler_t thread_fn, unsigned long irqflags,
			 const char *devname, void *dev_id)
			 
int devm_request_threaded_irq(struct device *dev, unsigned int irq,
			      irq_handler_t handler, irq_handler_t thread_fn,
			      unsigned long irqflags, const char *devname,
			      void *dev_id)
```

由此可见，它们此 request_irq 、 devm_request_irq 多了一个参数 thread_fn 。用这两个 API 申请中断的时候，内核会为相应的中断号分配一个对应的内核线程。
注意这个线程只针对这个中断号，如果其他中断也通过request_threaded_irq 申请，自然会得到新的内核线程。

参数 handler 对应的函数执行于中断上下文， thread_fn 参数对应的函数则执行于内核或程。如果 handler 结束的时候，返回值是 IRQ_WAKE_ТHREAD ，内核会调度对应线程执行 thread_fn 对应的函数。 

request_threaded_irq 和 devm_request_threaded_irq 支持在 irqflags 中设置 IROF_ONESHOT 标记，这样内核会自动帮助我们在中断上下文中屏敢对应的中断号，而在内核调度 thread_fn 执行后，重新使能该中断号。
对于我们无法在上半部清除中断的情况， IROF_ONESHOT 特别有用，避免了中断服务程序一退出，`中断就洪泛的情况`。 

handler 参数可以设置为 NULL ，这种情况下，内核会用默认的 irq_default_primary_handler 代替 handler ，并会使用 IROF_ONESHOT 标记。 irq_default_primary_handler 定义为：

```c
/* 
* Default primary interrupt handler for threaded inteEruptB ,is
* assigned as primary handler when request_threaded_irq is called 
* with handler == NULL , Useful for oneshot interrupts .
*/

static irqreturn_t irq_default_primary_handler ( int irq , void * dev_id )
{
 return IRQ_WAKE_ТHREAD ;
}
```

# 中断共享

多个设备共享一根中断线的情况在实际的硬件中广泛存在，PCI设备即是如此。中断共享的使用方法如下：  

1. 共享中断的多个设备在申请中断的时候都应该使用SA_SHIRQ标志，而且一个设备以SA_SHIRQ申请中断成功的前提是之前申请该中断的所有设备都以SA_SHIRQ标志申请该中断。  
2. 尽管内核模块可访问的全局地址都可以作为`request_irq(...,void *dev_id)` 的最后一个参数dev_id，但是设备结构体指针是可传入的最佳参数。  
3. 中断到来时所有共享中断的中断处理程序都被执行，在中断处理程序的顶半部中，应迅速地根据硬件寄存器中的信息比照传入的dev_id参数做出判断是否是本设备的中断，若不是应该迅速返回。 

```c

/* *****************************************************************************  
 
  共享中断编程模板如下：  
   
***************************************************************************** */ 

/*中断处理顶半部*/ 
irqreturn_t xxx_interrupt(int irq,void *dev_id,struct pt_regs *regs)  
{  
 ...  
 int status = read_int_status();//获知中断源  
 if(!is_myint(dev_id,status))/*判断是否是本设备的中断*/ 
 {  
  return IRQ_NONE;//立即返回  
 }  
 ...  
 return IRQ_HANDLED;  
}  

/*设备驱动加载模块*/ 
int xxx_init(void)  
{  
 ...  
 //申请共享中断  
 result = request_irq(sh_irq,xxx_interrupt,SA_SHIRQ,"xxx",xxx_dev);  
 ...  
}  

/*设备驱动卸载模块*/ 
int xxx_exit(void)  
{  
 ...  
 //释放中断  
 free_irq(sh_irq,xxx_dev);  
 ...  
}  
```

# 例子：GPIO 按键的中断

drivers/input/keyboard/gpio_keys.c

```c
static int gpio_keys_setup_key(struct platform_device *pdev,
				struct input_dev *input,
				struct gpio_keys_drvdata *ddata,
				const struct gpio_keys_button *button,
				int idx,
				struct fwnode_handle *child)
{
...
		INIT_WORK(&bdata->work, gpio_keys_gpio_work_func);
		setup_timer(&bdata->timer,
			    gpio_keys_gpio_timer, (unsigned long)bdata);

		isr = gpio_keys_gpio_isr;

	/*
	 * If platform has specified that the button can be disabled,
	 * we don't want it to share the interrupt line.
	 */
	if (!button->can_disable)
		irqflags |= IRQF_SHARED;

	error = devm_request_any_context_irq(dev, bdata->irq, isr, irqflags,
					     desc, bdata);
	if (error < 0) {
		dev_err(dev, "Unable to claim irq %d; error %d\n",
			bdata->irq, error);
		return error;
	}

	return 0;
}

static void gpio_remove_key(struct gpio_button_data *bdata)
{
	free_irq(bdata->irq, bdata);
	if (bdata->timer_debounce)
		del_timer_sync(&bdata->timer);
	cancel_work_sync(&bdata->work);
	if (gpio_is_valid(bdata->button->gpio))
		gpio_free(bdata->button->gpio);
}


static irqreturn_t gpio_keys_gpio_isr(int irq, void *dev_id)
{
	struct gpio_button_data *bdata = dev_id;

	BUG_ON(irq != bdata->irq);
	// 唤醒锁相关，按的时候，拿锁不允许休眠
	if (bdata->button->wakeup)
		pm_stay_awake(bdata->input->dev.parent);
	if (bdata->timer_debounce)
		mod_timer(&bdata->timer,
			jiffies + msecs_to_jiffies(bdata->timer_debounce));
	else
		schedule_work(&bdata->work);

	return IRQ_HANDLED;
}

static void gpio_keys_gpio_work_func(struct work_struct *work)
{
	struct gpio_button_data *bdata =
		container_of(work, struct gpio_button_data, work);
	// 上报数据
	gpio_keys_gpio_report_event(bdata);
	// 唤醒锁相关，上报后放锁才允许休眠
	if (bdata->button->wakeup)
		pm_relax(bdata->input->dev.parent);
}

static struct gpio_keys_platform_data *
gpio_keys_get_devtree_pdata(struct device *dev)
{
		button->wakeup = !!of_get_property(pp, "gpio-key,wakeup", NULL);

		if (of_property_read_u32(pp, "debounce-interval",
					 &button->debounce_interval))
			button->debounce_interval = 5;  // 上报debounce 时间默认5ms

static int gpio_keys_probe(struct platform_device *pdev)
{

		error = gpio_keys_setup_key(pdev, input, bdata, button);
		if (error)
			goto fail2;

		if (button->wakeup)
			wakeup = 1;
	}
	// 唤醒锁相关
	device_init_wakeup(&pdev->dev, wakeup); //

	return 0;
```

ps. mod_timer、schedule_work 参考：https://github.com/1040003585/linux_driver_study/tree/main/song10--Timer_Delay/