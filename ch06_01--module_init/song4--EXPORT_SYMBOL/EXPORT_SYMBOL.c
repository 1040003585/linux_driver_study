#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>


static char *book_name = "EXPORT_SYMBOL module";
EXPORT_SYMBOL_GPL(book_name);

int add_integar(int a, int b)
{
	return a + b;
}
EXPORT_SYMBOL(add_integar);

int sub_integar(int a, int b)
{
	return a - b;
}
EXPORT_SYMBOL_GPL(sub_integar);


static int __init EXPORT_SYMBOL_init(void)
{
	printk("EXPORT_SYMBOL_init sucess\n");

	return 0;
}

static void __exit EXPORT_SYMBOL_exit(void)
{
	printk("EXPORT_SYMBOL_exit sucess\n");
}

module_init(EXPORT_SYMBOL_init);
module_exit(EXPORT_SYMBOL_exit);

MODULE_LICENSE("GPL v2");
