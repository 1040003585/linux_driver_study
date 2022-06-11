#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>				// register_chrdev_region register to fs
#include <asm/uaccess.h>			// copy_from_user, ...
#include <linux/cdev.h>
#include <linux/slab.h>				// kzalloc, kfree
//#include <linux/mutex.h>

#include <linux/platform_device.h>


#define TAG "[work_device_p] "


static struct platform_device work_device1_p = {
	.name = "work_device+driver_p",
	.id = -1,
	// add follow:
	//.dev = { .release = platform_device_release, } //not export: error: ‘platform_device_release’ undeclared here (not in a function)
};
/*
static struct platform_device *work_devices_p __initdata = {
	&work_device1_p,
	//...
};
*/

static int __init work_device_p_init(void)
{
	//platform_add_devices(&work_devices_p, 1);	// 1. add devices

	if (platform_device_register(&work_device1_p))	// or 1. add one device
		platform_device_unregister(&work_device1_p);

	//platform_driver_register(&character_driver_p);	// 2. register driver

	printk(TAG "work_device_p_init sucess\n");
	return 0;
}

static void __exit work_device_p_exit(void)
{
	platform_device_unregister(&work_device1_p);

	printk(TAG "work_device_p_exit sucess\n");
}

module_init(work_device_p_init);
module_exit(work_device_p_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_LICENSE("GPL");

