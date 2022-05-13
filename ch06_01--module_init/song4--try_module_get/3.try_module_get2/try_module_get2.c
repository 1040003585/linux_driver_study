#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

static int __init try_module_get2_init(void)
{
	bool result;

	printk("try_module_get2_init sucess\n");

	result = try_module_get(THIS_MODULE);
	printk("try_module_get1: %d\n", result);

	result = try_module_get(THIS_MODULE);
	printk("try_module_get2: %d\n", result);

	module_put(THIS_MODULE);
	printk("module_put: %d\n", result);

	return 0;
}

static void __exit try_module_get2_exit(void)
{
	printk("try_module_get2_exit sucess\n");
}

module_init(try_module_get2_init);
module_exit(try_module_get2_exit);

