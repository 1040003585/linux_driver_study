#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>				// register_chrdev_region register to fs
#include <asm/uaccess.h>			// copy_from_user, ...
#include <linux/cdev.h>
#include <linux/slab.h>				// kzalloc, kfree
//#include <linux/mutex.h>

#include <linux/platform_device.h>


#define TAG "[character_device_p] "



static struct platform_device character_device1_p = {
	.name = "character_device+driver_p",
	.id = -1,
	// add follow:
	//.dev = { .release = platform_device_release, } //not export: error: ‘platform_device_release’ undeclared here (not in a function)
};
/*
static struct platform_device *character_devices_p __initdata = {
	&character_device1_p,
	//...
};
*/

static int __init character_device_p_init(void)
{
	//platform_add_devices(&character_devices_p, 1);	// 1. add devices

	if (platform_device_register(&character_device1_p))	// or 1. add one device
		platform_device_unregister(&character_device1_p);

	//platform_driver_register(&character_driver_p);	// 2. register driver

	printk(TAG "character_device_p_init sucess\n");
	return 0;
}

static void __exit character_device_p_exit(void)
{
	platform_device_unregister(&character_device1_p);
	//platform_driver_unregister(&character_driver_p);

	printk(TAG "character_device_p_exit sucess\n");
}

module_init(character_device_p_init);
module_exit(character_device_p_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_LICENSE("GPL");

