#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

#define DEVICE_NAME "misc_register"

static struct file_operations  dev_fops =
{ .owner = THIS_MODULE };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };


static int misc_register_init(void)
{
	int ret;
	
	ret = misc_register(&misc);

	printk("misc_register_init sucess\n");
	return ret;
}

static void misc_register_exit(void)
{
	misc_deregister(&misc);

	printk("misc_register_exit sucess\n");
}

module_init(misc_register_init);
module_exit(misc_register_exit);

