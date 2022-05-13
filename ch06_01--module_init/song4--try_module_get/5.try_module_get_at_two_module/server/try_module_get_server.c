#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
//#include <asm/uaccess.h>

#define DEVICE_NAME "try_module_get_server"
#define TAG "[try_module_get_server]"


static struct file_operations dev_fops =
{ .owner = THIS_MODULE };

static struct miscdevice misc_server =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

extern struct miscdevice misc_client;


static int __init try_module_get_server_init(void)
{
	int ret;
	
	printk(TAG "try_module_get at client: %d\n", try_module_get(misc_client.fops->owner));

	ret = misc_register(&misc_server);
	printk(TAG "try_module_get_server_init sucess \n");
	// do something ...
	printk(TAG "try_module_get_server_init do something ... \n");

	module_put(misc_client.fops->owner);
	printk(TAG "module_put:misc_client->fops.onwer\n");

	return ret;
}

static void __exit try_module_get_server_exit(void)
{
	misc_deregister(&misc_server);
	printk(TAG "try_module_get_server_exit sucess\n");
}

module_init(try_module_get_server_init);
module_exit(try_module_get_server_exit);

