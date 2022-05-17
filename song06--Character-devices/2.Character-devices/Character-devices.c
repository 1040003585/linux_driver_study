#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>				// register_chrdev_region register to fs
#include <asm/uaccess.h>			// copy_from_user, ...
#include <linux/cdev.h>
#include <linux/slab.h>				// kzalloc, kfree
//#include <linux/mutex.h>

#define DEVICE_NAME "character_devices"
#define TAG "[character_devices] "

#define GLOBALMEM_SIZE 0x1000 	//0x1000
#define GLOBALMEM_MAJOR 0	//231

#define GLOBALMEM_MAGIC 'g'
#define MEM_CLEAR _IO(GLOBALMEM_MAGIC, 0)


static int globalmem_major = GLOBALMEM_MAJOR;
module_param(globalmem_major, int, S_IRUGO);

struct globalmem_dev {
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
	//struct mutex mutex;
};


struct globalmem_dev *globalmem_devp;
//struct globalmem_dev globalmem_dev;


static ssize_t globalmem_read(struct file *flip, char __user *buf, size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct globalmem_dev *dev = flip->private_data;

	printk(TAG "[%s] read count: %d, p:%lu.\n", __func__, (int) count, p);

	if (p >= GLOBALMEM_SIZE)
		return 0;

	if (count > GLOBALMEM_SIZE - p)
		count = GLOBALMEM_SIZE - p;

	//mutex_lock(&dev->mutex);
	if (copy_to_user(buf, dev->mem + p, count)) {
		printk(TAG "[%s] -EFAULT:%d read %u bytes from %lu.\n", __func__, -EFAULT, count, p);
		return -EFAULT;
	} else {
		*ppos += count;
		ret = count;

		printk(TAG "[%s] read %u bytes from %lu.\n", __func__, count, p);
	}
	//mutex_unlock(&dev->mutex);

	return ret;
}

static ssize_t globalmem_write(struct file *flip, const char __user *buf, size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct globalmem_dev *dev = flip->private_data;

	printk(TAG "[%s] written count: %d, p:%lu.\n", __func__, (int) count, p);

	if (p >= GLOBALMEM_SIZE)
		return 0;

	if (count > GLOBALMEM_SIZE - p)
		count = GLOBALMEM_SIZE - p;

	//mutex_lock(&dev->mutex);
	if (copy_from_user(dev->mem + p, buf, count)) {
		printk(TAG "[%s] -EFAULT:%d written %u bytes from %lu.\n", __func__, -EFAULT, count, p);
		return -EFAULT;
	} else {
		*ppos += count;
		ret = count;

		printk(TAG "[%s] written %u bytes from %lu.\n", __func__, count, p);
	}
	//mutex_unlock(&dev->mutex);

	return ret;
}

static ssize_t globalmem_open(struct inode *inode, struct file *flip)
{
	printk(TAG "[%s] init flip private_data.\n", __func__);

	flip->private_data = globalmem_devp;
	return 0;
}


static int globalmem_release(struct inode *inode, struct file *filp)
{
	printk(TAG "[%s] release.\n", __func__);
	return 0;
}

static loff_t globalmem_llseek(struct file *filp, loff_t offset, int arg)
{
	loff_t ret = 0;
	switch(arg) {
	case 0: //begin from the start
		if (offset < 0) {
			ret = -EINVAL;
			break;
		}
		if ((unsigned int)offset > GLOBALMEM_SIZE) {
			ret = -EINVAL;
			break;
		}
		filp->f_pos = offset;
		ret = filp->f_pos;
		break;
	case 1: //begin from current position
		if ((unsigned int)offset + (unsigned int)filp->f_pos < 0) {
			ret = -EINVAL;
			break;
		}
		if ((unsigned int)offset + (unsigned int)filp->f_pos > GLOBALMEM_SIZE) {
			ret = -EINVAL;
			break;
		}
		filp->f_pos += offset;
		ret = filp->f_pos;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}

static long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct globalmem_dev *dev = filp->private_data;
	switch(cmd) {
	case MEM_CLEAR:
		//mutex_lock(&dev->mutex);
		memset(dev->mem, 0, GLOBALMEM_SIZE);
		//mutex_unlock(&dev->mutex);
		printk(KERN_INFO"globalmem is set to zero\n");
		break;
	default:
		 return -EINVAL;
	}
	return 0;
}

static struct file_operations globalmem_fops = {
	.owner = THIS_MODULE,
	.open = globalmem_open,
	.read = globalmem_read,
	.write = globalmem_write,
	.llseek = globalmem_llseek,
	.unlocked_ioctl = globalmem_ioctl,
	.release = globalmem_release,
};

/*
static struct miscdevice misc = {
	//.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &globalmem_fops,
};
*/

static int __init character_devices_init(void)
{
	int ret;
	dev_t devno = MKDEV(globalmem_major, 0);


	if (globalmem_major)							//init devno
		ret = register_chrdev_region(devno, 1, "globalmem_name1");
	else {
		ret = alloc_chrdev_region(&devno, 0, 1, "globalmem_name2");
		globalmem_major = MAJOR(devno);
	}
	
	if (ret < 0) {
		printk(TAG "character_devices_init *chrdev_region fail: %d.\n", ret);
		return ret;
	}

	globalmem_devp = kzalloc(sizeof(struct globalmem_dev), GFP_KERNEL);
	if (!globalmem_devp) {
		ret = -ENOMEM;
		printk(TAG "character_devices_init kzalloc fail: %d.\n", ret);

		goto fail_malloc;
	}

	//mutex_init(&globalmem_devp->mutex);

	cdev_init(&globalmem_devp->cdev, &globalmem_fops);			//init cdev
	globalmem_devp->cdev.owner = THIS_MODULE;

	ret = cdev_add(&globalmem_devp->cdev, devno, 1);			//register cdev, bind devno
	
	if (ret < 0) {
		printk(TAG "character_devices_init cdev_add fail: %d.\n", ret);
		return ret;
	}

	printk(TAG "character_devices_init sucess\n");
	return 0;


fail_malloc:
	unregister_chrdev_region(devno, 1);
	return ret;
}

static void __exit character_devices_exit(void)
{
	kfree(globalmem_devp);
	cdev_del(&globalmem_devp->cdev);				//unregister cdev

	unregister_chrdev_region(MKDEV(globalmem_major, 0), 1);

	printk(TAG "character_devices_exit sucess\n");
}

module_init(character_devices_init);
module_exit(character_devices_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_LICENSE("GPL");

