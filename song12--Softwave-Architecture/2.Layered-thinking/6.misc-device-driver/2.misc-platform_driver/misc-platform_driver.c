#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
//#include <asm/uaccess.h>
#include <linux/platform_device.h>

#define DEVICE_NAME "misc_platform_driver_NAME"
#define TAG "[misc_platform_driver] "


static struct file_operations  dev_fops =
{ .owner = THIS_MODULE };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };

struct globalfifo_dev {
	struct miscdevice miscdev;
};

static int misc_platform_driver_probe(struct platform_device *pdev)
{
	int ret;
	struct globalfifo_dev *gl;

	gl = devm_kzalloc(&pdev->dev, sizeof(*gl), GFP_KERNEL);
	if (!gl)
		return -ENOMEM;

	gl->miscdev = misc;
	platform_set_drvdata(pdev, gl);
	
	ret = misc_register(&gl->miscdev);
	if (ret < 0)
		goto err;

	printk(TAG "misc_platform_driver_probe sucess\n");
	return 0;
err:
	printk(TAG "misc_platform_driver_init err...\n");
	return 0;
}


static int misc_platform_driver_remove(struct platform_device *pdev)
{
	struct globalfifo_dev *gl = platform_get_drvdata(pdev);
	misc_deregister(&gl->miscdev);

	printk(TAG "misc_platform_driver_remove sucess\n");

	return 0;
}

static struct platform_driver misc_platform_driver = {
	.driver = {
		//.name  = "misc_platform_driver-name",
		.name  = "misc_platform_device+driver-name",
		.owner = THIS_MODULE,
	},
	.probe = misc_platform_driver_probe,
	.remove = misc_platform_driver_remove,
};

/*
#define module_driver(__driver, __register, __unregister, ...) \
static int __init __driver##_init(void) \
{ \
	return __register(&(__driver) , ##__VA_ARGS__); \
} \
module_init(__driver##_init); \
static void __exit __driver##_exit(void) \
{ \
	__unregister(&(__driver) , ##__VA_ARGS__); \
} \
module_exit(__driver##_exit);


#define module_platform_driver(__platform_driver) \
	module_driver(__platform_driver, platform_driver_register, \
			platform_driver_unregister)
*/

module_platform_driver(misc_platform_driver);

MODULE_LICENSE("GPL");
