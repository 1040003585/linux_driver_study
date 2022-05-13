#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

static int try_module_get_init(void)
{
	bool result;

	printk("try_module_get_init sucess\n");

	result = try_module_get(THIS_MODULE);
	printk("try_module_get: %d\n", result);

	return 0;
}

static void try_module_get_exit(void)
{
	printk("try_module_get_exit sucess\n");
}

module_init(try_module_get_init);
module_exit(try_module_get_exit);

