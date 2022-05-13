#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

#define DEVICE_NAME "try_module_get_client"
#define TAG "[try_module_get_client]"


static struct file_operations dev_fops =
{ .owner = THIS_MODULE };

struct miscdevice misc_client =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

EXPORT_SYMBOL(misc_client);

static int __init try_module_get_client_init(void)
{
	int ret;

	ret = misc_register(&misc_client);
	printk(TAG "try_module_get_client_init sucess\n");
	// do something ...

	return ret;
}

static void __exit try_module_get_client_exit(void)
{
	misc_deregister(&misc_client);
	printk(TAG "try_module_get_client_exit sucess\n");
}

module_init(try_module_get_client_init);
module_exit(try_module_get_client_exit);


