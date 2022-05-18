
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
3. 自旋锁
4. 信号量
5. 互斥体

## 中断屏蔽 

中断屏蔽是对当前CPU屏蔽中断，适合单CPU，但长时间屏蔽中断比较危险
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

### 使用例子

原子变量使设备只能被一个进程打开

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

## 信号量

## 互斥体
