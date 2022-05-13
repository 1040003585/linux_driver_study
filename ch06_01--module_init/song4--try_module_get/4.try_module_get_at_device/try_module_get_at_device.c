#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

#define DEVICE_NAME "try_module_get_at_device"
#define TAG "[try_module_get_at_device]"


static struct file_operations dev_fops =
{ .owner = THIS_MODULE };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };


static int try_module_get_at_device_init(void)
{
	int ret;
	
	printk(TAG "try_module_get: %d\n", try_module_get(misc.fops->owner));

	ret = misc_register(&misc);
	printk(TAG "try_module_get_at_device_init sucess\n");

	module_put(misc.fops->owner);
	printk(TAG "module_put:misc.fops->owner\n");

	return ret;
}

static void try_module_get_at_device_exit(void)
{
	misc_deregister(&misc);
	printk(TAG "try_module_get_at_device_exit sucess\n");
}

module_init(try_module_get_at_device_init);
module_exit(try_module_get_at_device_exit);


