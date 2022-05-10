#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

static int hello_world_init(void)
{
	printk("hello_world_init sucess\n");
	return 0;
}

static void hello_world_exit(void)
{
	printk("hello_world_exit sucess\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

