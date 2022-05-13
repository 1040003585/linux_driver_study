#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

static int __init sub_module_init(void)
{
	printk("sub_module_init sucess\n");
	return 0;
}

static void __exit sub_module_exit(void)
{
	printk("sub_module_exit sucess\n");
}

module_init(sub_module_init);
module_exit(sub_module_exit);

