#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/interrupt.h>

#include <linux/delay.h>
#include <linux/kthread.h> //schedule_timeout


#define TAG "[tasklet] "

static struct tasklet_struct my_tasklet;

static void tasklet_handler(unsigned long data)
{
	printk(KERN_INFO TAG "tasklet_handler is running.INFO\n");
	printk(KERN_DEBUG TAG "tasklet_handler is running.DEBUG\n");
	printk(KERN_ALERT TAG "tasklet_handler is running.ALERT\n");

	mdelay(1000); // msleep will dead vmwave // schedule_timeout will dead master
	tasklet_schedule(&my_tasklet);
}

static int __init tasklet_module_init(void)
{
	tasklet_init(&my_tasklet, tasklet_handler, 0);
	tasklet_schedule(&my_tasklet);
	printk(KERN_ALERT TAG "tasklet_init.\n");

	return 0;
}

static void __exit tasklet_module_exit(void)
{
	tasklet_kill(&my_tasklet);
	printk(KERN_ALERT TAG "tasklet_exit.\n");
}

module_init(tasklet_module_init);
module_exit(tasklet_module_exit);

MODULE_LICENSE("GPL");
