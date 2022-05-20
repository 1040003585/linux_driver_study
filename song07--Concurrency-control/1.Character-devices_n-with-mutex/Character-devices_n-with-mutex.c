#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>				// register_chrdev_region register to fs
#include <asm/uaccess.h>			// copy_from_user, ...
#include <linux/cdev.h>
#include <linux/slab.h>				// kzalloc, kfree
#include <linux/mutex.h>//

#define DEVICE_NAME "character_devices_n_with_mutext"
#define TAG "[character_devices_n_with_mutext] "

#define GLOBALMEM_SIZE 0x1000 	//0x1000
#define GLOBALMEM_MAJOR 0	//231

#define GLOBALMEM_MAGIC 'g'
#define MEM_CLEAR _IO(GLOBALMEM_MAGIC, 0)

#define GLOBALMEM_NUM 10


static int globalmem_major = GLOBALMEM_MAJOR;
module_param(globalmem_major, int, S_IRUGO);

struct globalmem_dev {
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
	struct mutex mutex;//
};


struct globalmem_dev *globalmem_devp;
//struct globalmem_dev globalmem_dev;


static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct globalmem_dev *dev = filp->private_data;

	printk(TAG "[%s] read count: %d, p:%lu.\n", __func__, (int) count, p);

	if (p >= GLOBALMEM_SIZE)
		return 0;

	if (count > GLOBALMEM_SIZE - p)
		count = GLOBALMEM_SIZE - p;

	mutex_lock(&dev->mutex);//
	if (copy_to_user(buf, dev->mem + p, count)) {
		printk(TAG "[%s] -EFAULT:%d read %u bytes from %lu.\n", __func__, -EFAULT, count, p);
		return -EFAULT;
	} else {
		*ppos += count;
		ret = count;

		printk(TAG "[%s] read %u bytes from %lu.\n", __func__, count, p);
	}
	mutex_unlock(&dev->mutex);//

	return ret;
}

static ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct globalmem_dev *dev = filp->private_data;

	printk(TAG "[%s] written count: %d, p:%lu.\n", __func__, (int) count, p);

	if (p >= GLOBALMEM_SIZE)
		return 0;

	if (count > GLOBALMEM_SIZE - p)
		count = GLOBALMEM_SIZE - p;

	mutex_lock(&dev->mutex);//
	if (copy_from_user(dev->mem + p, buf, count)) {
		printk(TAG "[%s] -EFAULT:%d written %u bytes from %lu.\n", __func__, -EFAULT, count, p);
		return -EFAULT;
	} else {
		*ppos += count;
		ret = count;

		printk(TAG "[%s] written %u bytes from %lu.\n", __func__, count, p);
	}
	mutex_unlock(&dev->mutex);//

	return ret;
}

static ssize_t globalmem_open(struct inode *inode, struct file *filp)
{
	struct globalmem_dev *dev = container_of(inode->i_cdev, struct globalmem_dev, cdev);
	filp->private_data = dev;

	printk(TAG "[%s] container_of private_data.\n", __func__);

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
		mutex_lock(&dev->mutex);//
		memset(dev->mem, 0, GLOBALMEM_SIZE);
		mutex_unlock(&dev->mutex);//
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

static void globalmem_setup_cdev(struct globalmem_dev *dev, int index)
{
	int err, devno = MKDEV(globalmem_major, index);

	cdev_init(&dev->cdev, &globalmem_fops);			//init cdev
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);			//register cdev, bind devno

	if (err)
		printk(TAG "ERROR %d adding globalmem %d", err, index);
}

static int __init character_devices_n_with_mutext_init(void)
{
	int ret, i;
	dev_t devno = MKDEV(globalmem_major, 0);


	if (globalmem_major)							//init devno
		ret = register_chrdev_region(devno, GLOBALMEM_NUM, "character_devices_n_with_mutext-globalmem_name1_n");
	else {
		ret = alloc_chrdev_region(&devno, 0, GLOBALMEM_NUM, "character_devices_n_with_mutext-globalmem_name2_n");
		globalmem_major = MAJOR(devno);
	}
	
	if (ret < 0) {
		printk(TAG "character_devices_n_with_mutext_init *chrdev_region fail: %d.\n", ret);
		return ret;
	}

	globalmem_devp = kzalloc(sizeof(struct globalmem_dev) * GLOBALMEM_NUM, GFP_KERNEL);
	if (!globalmem_devp) {
		ret = -ENOMEM;
		printk(TAG "character_devices_n_with_mutext_init kzalloc fail: %d.\n", ret);

		goto fail_malloc;
	}

	//mutex_init(&globalmem_devp->mutex); // bug: only for first devp

	for (i = 0; i < GLOBALMEM_NUM; i++) {
		//globalmem_setup_cdev(globalmem_devp, i);
		globalmem_setup_cdev(globalmem_devp + i, i);

		mutex_init(&(globalmem_devp + i)->mutex);
	}

	printk(TAG "character_devices_n_with_mutext_init sucess\n");
	return 0;


fail_malloc:
	unregister_chrdev_region(devno, 1);
	return ret;
}

static void __exit character_devices_n_with_mutext_exit(void)
{
	int i;
	//kfree(globalmem_devp);

	for (i = 0; i < GLOBALMEM_NUM; i++)
		cdev_del(&(globalmem_devp + i)->cdev);				//unregister cdev

	kfree(globalmem_devp);
	unregister_chrdev_region(MKDEV(globalmem_major, 0), GLOBALMEM_NUM);

	printk(TAG "character_devices_n_with_mutext_exit sucess\n");
}

module_init(character_devices_n_with_mutext_init);
module_exit(character_devices_n_with_mutext_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_LICENSE("GPL");
