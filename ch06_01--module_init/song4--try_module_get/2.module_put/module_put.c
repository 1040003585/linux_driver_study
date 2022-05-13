#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

static int __init module_put_init(void)
{
	bool result;

	printk("module_put_init sucess\n");

	result = try_module_get(THIS_MODULE);
	printk("try_module_get1: %d\n", result);

	module_put(THIS_MODULE);
	printk("module_put: %d\n", result);

	return 0;
}

static void __exit module_put_exit(void)
{
	printk("module_put_exit sucess\n");
}

module_init(module_put_init);
module_exit(module_put_exit);

