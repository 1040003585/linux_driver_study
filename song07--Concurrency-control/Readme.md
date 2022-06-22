
# 并发和竞态

**并发**：多个执行单元同时、并行被执行。

**共享资源**：硬件资源、软件的全局变量和静态变量。

**竞态**：多个执行单元存在对共享资源的访问。

竞态发生情况：

1. 对称多处理器（SMP）的多个CPU；
a. CPU0 的进程和CPU1 的进程；
b. CPU0 的进程和CPU1 的中断；
c. CPU0 的中断和CPU1 的中断；

2. 单CPU 内进程与抢占它的进程；
Linux2.6 支持内核抢占调度

3. 中断（硬中断、软中断、Tasklet、底半部）与进程之间；
Linux2.6.35 取消嵌套中断


# 编译乱序和执行乱序

**编译乱序**：编译器行为，用barrier() 编译屏障处理；

**执行乱序**：处理器运行时的行为；ARM 处理器屏障指令：DMB/DS/ISB，Linux 定义读写屏障mb()、读屏障rmb()、写屏障wmb()，寄存器的读写__iormb()、__iowmb()，API readl()/readl_relaxed(), writel()/writel_relaxed()。

# 并发控制机制

1. 中断屏蔽：针对单核处理器 
2. 原子操作：针对整型数据
3. 自旋锁：多核或可抢占的单核
4. 信号量：PV操作，不会忙等
5. 互斥体：同信号量，进程级

## 中断屏蔽 

中断屏蔽是对当前CPU屏蔽中断，适合单CPU，但长时间屏蔽中断比较危险。

1. 中断和进程不再并发；
2. 异步IO、进程调度依赖中断实现，抢占也能避免；

```c
local_irq_disable();    // 屏蔽中断
...
critical section        // 临界区
...
local_irq_ensable();    // 开中断
```

`local_irq_save(flag)` 和`local_irq_restore(flag)` 处理屏蔽恢复中断，还可以保存恢复中断信息；

`local_bh_disable()` 和`local_bh_enable()` 只禁止和恢复中断的底半部；

## 原子操作

可以保证对一个整型数据的修改是排他性，包括位和整型变量的原子操作。

### 整型原子操作
1. 设置原子变量的值
```
void atomic_set(atomic_t *v, int);
atomic_t v = ATOMIC_INIT(0);
```
2. 获取原子变量的值
```
atomic_read(atomic_t *v);
```
3. 原子变量的加减
```
void atomic_add(atomic_t *v, int);
void atomic_sub(atomic_t *v, int);
```
4. 原子变量自增自减
```
void atomic_inc(atomic_t *v);
void atomic_dec(atomic_t *v);
```
5. 操作并测试
```
int atomic_inc_and_test(atomic_t *v);   //test 为0 返回 ture
int atomic_dec_and_test(atomic_t *v);
int atomic_sub_and_test(int i, atomic_t *v);
```
6. 操作并返回
```
int atomic_add_return(int i, atomic_t *v);   //reture new data
int atomic_sub_return(int i, atomic_t *v); 
int atomic_inc_return(atomic_t *v);
int atomic_dec_return(atomic_t *v);
```

linux kernel 休眠的wakeup sources 也是用到原子变量的机制。

### 位原子操作

1. 设置位
```
void set_bit(nr, void *addr);       // 地址addr 的nr 位写位1
```
2. 清除位
```
void clear_bit(nr, void *addr);
```
3. 改变位
```
void change_bit(nr, void *addr);    // 地址addr 的nr 位反置
```
4. 测试位
```
test_bit(nr, void *addr);           // 返回地址addr 的nr 位
```
5. 测试并操作位
```
int test_and_set_bit(nr, void *addr);
int test_and_clear_bit(nr, void *addr);
int test_and_change_bit(nr, void *addr);
```

**使用例子**

原子变量使设备只能被一个进程打开。

```c
static atomic_t xxx_avaiable = ATOMIC_INIT(1); 

static ssize_t xxx_open(struct inode *inode, struct file *flip)
{
	...
    if(!atomic_dec_and_test(&xxx_available)) {
        atomic_inc(&xxx_available);
        return -EBUSY;               // 已经打开过了
    }
	...
    return 0;                        // 成功打开
}

static int xxx_release(struct inode *inode, struct file *filp)
{
    atomic_inc(&xxx_avaiable);      // 释放设备
    return 0;
}
```

## 自旋锁


### 自旋锁的使用

spin_lock自旋锁主要针对SMP 或单CPU可抢占的情况，忙等待，但会受中断和底半部影响，所以：

1. 进程上下文使用：spin_lock_irqsave()和spin_unlock_irqrestore();
2. 中断上下文使用：spin_lock()和spin_unlock();

```
spin_lock_irq() = spin_lock() + local_irq_disable()
spin_unlock_irq() = spin_unlock() + local_irq_enable()
spin_lock_irqsave() = spin_lock() + local_irq_save()
spin_unlock_irqrestore() = spin_unlock() + local_irq_restore()
spin_lock_bh() = spin_lock() + local_bh_disable()
spin_unlock_bh() = spin_unlock() + local_bh_enable()
```

**自旋锁使用注意**：
1. 会忙等待，临界区或共享资源太多会影响系统性能；
2. cpu 同一个进程递归拿同一个锁，会死锁；（互斥锁也一样）
3. 拿锁期间，不能调用会让系统调度的函数，如copy_from_user, copy_to_user, kmalloc, msleep 等；
4. spin_lock_irqsave不能屏蔽其他cpu中断，如果其他cpu 中断没有加spin_lock，也会并发访问统一共享资源；

**自旋锁使用例子**

使用模板：
```
spinlock_t lock;
spin_lock_init(&lock);

spin_lock(&lock);
//ret = spin_trylock(&lock);  //如果获取不到，不自旋，返回false
...//临界区
spin_unlcok(&lock);
```

如下自旋锁使用的设备只能被一个进程打开:

```c
int xxx_count = 0;      // 定义文件打开次数

static ssize_t xxx_open(struct inode *inode, struct file *flip)
{
	...
	spin_lock(&xxx_count);
    if(xxx_count) {     // 已经打开过了
        spin_unlock(&xxx_count);
        return -EBUSY;
    }
    xxx_count++;         // 增加引出次数
    spin_unlock(&xxx_count);
	...
    return 0;                        // 成功打开
}

static int xxx_release(struct inode *inode, struct file *filp)
{
    spin_lock(&xxx_count);
    xxx_count--;         //减少加引出次数
    spin_unlock(&xxx_count);
    return 0;
}
```

### 读写自旋锁

rwlock 可以多个进程读，只能一个进程写，读和写不能同时进行。

使用模板：
```
rwlock_t lock;
rwlock_init(&lock);

// 读时候
read_lock(&lock);
...//临界区
read_unlcok(&lock);

// 写时候
write_lock_irqsave(&lock, flag);
//ret = write_trylock(&lock);  //如果获取不到，不自旋，返回false
...//临界区
write_unlcok_restore(&lock, flag);

```

### 顺序锁

seqlock 运行读写同时进行，但写和写不能同时，如果读过程有写需要重读。

写执行单元，还有`write_seqlock_irqsave`、`write_seqlock_irq`、`write_seqlock_bh`。
```
write_seqlock(&seqlock);
//ret = write_tryseqlock(&seqlock);  //如果获取不到，不自旋，返回false
...//临界区
write_sequnlcok(&seqlock);
```

读执行单元，还有`read_seqbegin_irqstore`、`read_seqretry_irqstore`。
```
do {
    seqnum = read_seqbegin(&seqlock);
    ...//临界区
} while (read_seqretry(&seqlock, seqnum));
```

### 读-复制-更新

RCU (Read-Copy-Update) 读端没有锁、内存屏障、原子指令等开销，只是标记读开始和结束；
写端再访问共享资源先复制一个副本，对副本修改，回调时机把指针指向副本。

允许多个读，允许多个写。逻辑如下：

```
struct foo {
    struct list_head list;
    int a, b, c;
};
LIST_HEAD(head);

p = search(head, key);
if(p == NULL) {
    // Take appropriate action, unlock and return
}

q = kmalloc(sizeof(*p), GFP_KERNEL);
*q = *p;
q->a = 1;
q->b = 2;
list_replace_rcu(&p->list, &q->list);
synchronize_rcu(); 宽限期(Grace Period)：等待所有读完成。
kfree(p);
```

Linux RCU 操作：

```
1. 读锁定和解锁
rcu_read_lock(); // or rcu_read_lock_bh()
...// 临界区
rcu_read_unlock; // or rcu_read_unlock_bh()

2. 同步RCU
synchronize_rcu() 不会等待后续(Subsequent)的读临界区的完成.

3. 挂接回调
...
```
RCU 目前有用于GPU 相关code中。

## 信号量

Semaphore 处理系统的同步和互斥问题，即操作系统的PV 操作，信号量值可以是0、1...N。

P(s)：1. 如果信号量s大于0，进程继续运行；2. s为0，进程等待，直到V操作加信号量唤醒之。

```
// 定义信号量
struct semaphore sem;
// 初始化信号量为val
void sema_init(struct semaphore *sem, int val);

//获取信号量
void down(struct semaphore *sem);      // 会导致进程睡眠，不能再中断上下文使用
int down_interruptible(struct semaphore *sem); // 睡眠状态的进程可以被信号打断,返回非0，上面函数不能被信号打断
int down_trylock(struct semaphore *sem);  // 如果获取不到，返回非0，不会让调用者睡眠，可以中断上下文使用

if(down_interruptible(&sem))
    return -ERESTARTSYS;

//释放信号量
void up(struct semaphore *sem);
```

**互斥问题**

与自旋锁不同的时，等不到信号时，进程不会原地打转而是进入休眠等待状态。Linux 一般用mutex 代替来操作此类问题。

**同步问题**

进程A 执行down()等待信号量，进程B执行up()释放信号量，这样A 同步的等待B。即生产者和消费者问题。

## 互斥体

进程级，获取不到锁也会让当前进程休眠，调度上下文切换给其他进程运行。

用法和信号量完全一样，也有`mutex_lock_interruptible`和`mutex_trylock`。
```
struct mutex my_mutex;
mutex_init(&my_mutex);

mutex_lock(&my_mutex);
... // 临界区
mutex_unlock(&my_mutex);
```

**自旋锁和互斥锁**

1. 互斥锁的开销是上下文切换时间，自旋锁开销是临界区忙等时间，如果临界区小用自旋锁，如果大就用互斥锁；
2. 互斥锁临界区可以保护会阻塞的代码（copy_to_user）, 自旋锁不行，因为阻塞要调度上下文切换，如果进程切换出去，另外一个进程来获取这个自旋锁，也会死锁；
3. 互斥锁用与进程上下文，如果有中断或软中断，则用自旋锁，或mutex_trylock;


## 完成量

Completion 用于执行单元等待另一个执行单元执行完成某事。

```
// 1. 定义完成量
struct completion my_completion;

// 2. 初始化完成量为0
init_completion(&my_completion);
reinit_completion(&my_completion);

// 3. 等待一个完成量被唤醒
void wait_for_completion(struct completion *c);

// 4. 完成量唤醒
void complete(struct completion *c);    // 只唤醒一个
void complete_all(struct completion *c);// 唤醒所有
```

Completion 实际由**等待队列（Wait Queue）** （`wake_up()`与`wait_event()`）来实现。
参考，song07 章节目录。
