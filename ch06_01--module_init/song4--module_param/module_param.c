#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

static char *book_name = "dissecting Linux Device Driver";
module_param(book_name, charp, S_IRUGO);

static int book_num = 4000;
module_param(book_num, int, S_IRUGO);

static int __init module_param_init(void)
{
	printk("hello_world_init sucess\n");

	printk("book_name: %s\n", book_name);
	printk("book_num : %d\n", book_num);
	return 0;
}

static void __exit module_param_exit(void)
{
	printk("module_param_exit sucess\n");
}

module_init(module_param_init);
module_exit(module_param_exit);

MODULE_LICENSE("GPL v2");
