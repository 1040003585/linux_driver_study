#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/miscdevice.h>
//#include <asm/uaccess.h>
#include <linux/platform_device.h>


#define TAG "[misc_platform_device] "

static struct platform_device *pdev;

static int misc_platform_device_init(void)
{
	int ret;
	
	//pdev = platform_device_alloc("misc_platform_device-name", -1);
	pdev = platform_device_alloc("misc_platform_device+driver-name", -1);
	if (!pdev)
		return -ENOMEM;

	ret = platform_device_add(pdev);
	if(ret) {
		platform_device_put(pdev);
		return ret;
	}

	printk(TAG "misc_platform_device_init sucess\n");
	return ret;
}

static void misc_platform_device_exit(void)
{
	platform_device_unregister(pdev);

	printk(TAG "misc_platform_device_exit sucess\n");
}

module_init(misc_platform_device_init);
module_exit(misc_platform_device_exit);

MODULE_LICENSE("GPL");
