#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>


extern int add_integar(int a, int b);
extern int sub_integar(int a, int b);
extern char *book_name;


static int __init EXPORT_SYMBOL_another_init(void)
{
	printk("EXPORT_SYMBOL_another_init sucess\n");

	printk("EXPORT_SYMBOL_another add_integar: %d.\n", add_integar(1, 1) );
	printk("EXPORT_SYMBOL_another sub_integar: %d.\n", sub_integar(1, 1) );
	printk("EXPORT_SYMBOL_another book_name  : %s.\n", book_name );

	return 0;
}

static void __exit EXPORT_SYMBOL_another_exit(void)
{
	printk("EXPORT_SYMBOL_another_exit sucess\n");
}

module_init(EXPORT_SYMBOL_another_init);
module_exit(EXPORT_SYMBOL_another_exit);

MODULE_LICENSE("GPL v2");
