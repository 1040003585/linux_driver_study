#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>				// register_chrdev_region register to fs
//#include <asm/uaccess.h>			// copy_from_user...
#include <linux/cdev.h>
//#include <linux/slab.h>			// kzalloc, kfree

#define DEVICE_NAME "character_devices_tmp"
#define TAG "[character_devices_tmp] "

#define GLOBALMEM_SIZE 0x1000
#define MEM_CLEAR 0x1
#define GLOBALMEM_MAJOR 230

static int globalmem_major = GLOBALMEM_MAJOR;
module_param(globalmem_major, int, S_IRUGO);

struct globalmem_dev {
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
};

//struct globalmem_dev *globalmem_devp;
struct globalmem_dev globalmem_dev;


static struct file_operations globalmem_fops = {
	.owner = THIS_MODULE,
/*	.llseek = globalmem_llseek,
	.read = globalmem_read,
	.write = globalmem_write,
	.unlocked_ioctl = globalmem_unlocked_ioctl,
	.open = globalmem_open,
	.release = globalmem_release,
*/};

/*
static struct miscdevice misc = {
	//.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &globalmem_fops,
};
*/

static int __init character_devices_tmp_init(void)
{
	int ret;
	dev_t devno = MKDEV(globalmem_major, 0);

/*
	globalmem_devp = kzalloc(sizeof(struct globalmem_dev), GFP_KERNEL);
	if (!globalmem_devp) {
		ret = -ENOMEM;
		goto fail_malloc;
	}
*/

	cdev_init(&globalmem_dev.cdev, &globalmem_fops);	//init cdev
	globalmem_dev.cdev.owner = THIS_MODULE;

	if (globalmem_major)					//init devno
		ret = register_chrdev_region(devno, 1, "globalmem_name1");
	else {
		ret = alloc_chrdev_region(&devno, 0, 1, "globalmem_name2");
		globalmem_major = MAJOR(devno);
	}
	
	if (ret < 0) {
		printk(TAG "character_devices_tmp_init *chrdev_region fail: %d.\n", ret);
		return ret;
	}

	ret = cdev_add(&globalmem_dev.cdev, devno, 1);		//register cdev, bind devno
	
	if (ret < 0) {
		printk(TAG "character_devices_tmp_init cdev_add fail: %d.\n", ret);
		return ret;
	}

	printk(TAG "character_devices_tmp_init sucess\n");
	return 0;


//fail_malloc:
//	unregister_chrdev_region(devno, 1);
	return ret;
}

static void __exit character_devices_tmp_exit(void)
{
//	kfree(globalmem_devp);
	cdev_del(&globalmem_dev.cdev);				//unregister cdev

	unregister_chrdev_region(MKDEV(globalmem_major, 0), 1);

	printk(TAG "character_devices_tmp_exit sucess\n");
}

module_init(character_devices_tmp_init);
module_exit(character_devices_tmp_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_LICENSE("GPL");

