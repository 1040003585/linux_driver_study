#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

static int __init main_module_init(void)
{
	int ret;
	printk("main_module_init sucess\n");
	
	ret = request_module("sub_module");
	if (ret)
		printk("main_module requset sub module fail: %d.\n", ret);

	return 0;
}

static void __exit main_module_exit(void)
{
	printk("main_module_exit sucess\n");
}

module_init(main_module_init);
module_exit(main_module_exit);

