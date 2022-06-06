#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
//#include <linux/workqueue.h>

//#include <linux/slab.h> //kzalloc
//#include <linux/platform_device.h>

#define TAG "[work] "

extern struct delayed_work usbwork; // must add extern

 void work_usb(struct work_struct *work);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_LICENSE("GPL v2");
