#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>				// register_chrdev_region register to fs
#include <asm/uaccess.h>			// copy_from_user, ...
#include <linux/cdev.h>
#include <linux/slab.h>				// kzalloc, kfree
#include <linux/mutex.h>//

#include <linux/sched.h>/**/
#include <linux/poll.h>/**/

#define DEVICE_NAME "character_devices_wq_poll"
#define TAG "[character_devices_wq_poll] "

#define GLOBALFIFO_SIZE 0x20
#define GLOBALFIFO_MAJOR 0

//#define GLOBALFIFO_MAGIC 'g'
//#define FIFO_CLEAR _IO(GLOBALFIFO_MAGIC, 0)
#define FIFO_CLEAR 0x1

//#define GLOBALFIFO_NUM 10


static int globalfifo_major = GLOBALFIFO_MAJOR;
module_param(globalfifo_major, int, S_IRUGO);

struct globalfifo_dev {
	struct cdev cdev;
	unsigned char mem[GLOBALFIFO_SIZE];
	struct mutex mutex;//

	unsigned int current_len; /**/
	wait_queue_head_t r_wait; /**/
	wait_queue_head_t w_wait; /**/
};


struct globalfifo_dev *globalfifo_devp;
//struct globalfifo_dev globalfifo_dev;


static ssize_t globalfifo_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	int ret = 0;
	struct globalfifo_dev *dev = filp->private_data;
	DECLARE_WAITQUEUE(wait, current); /**/

	printk(TAG "[%s] count: %d. start.\n", __func__, (int) count);

	mutex_lock(&dev->mutex);//
	add_wait_queue(&dev->r_wait, &wait); /**/

	while (dev->current_len == 0) {
		if (filp->f_flags & O_NONBLOCK) {
			printk(TAG "[%s] filp->f_flags is O_NONBLOCK. ret.\n", __func__);
			ret = -EAGAIN;
			goto out1;
		}
		__set_current_state(TASK_INTERRUPTIBLE);

		mutex_unlock(&dev->mutex);//

		printk(TAG "[%s] schedule before.\n", __func__);
		schedule();
		printk(TAG "[%s] schedule after.\n", __func__);

		printk(TAG "[%s] signal_pending before.\n", __func__);
		if (signal_pending(current)) {
			printk(TAG "[%s] signal_pending.\n", __func__);
			ret = -ERESTARTSYS;
			goto out2;
		}
		printk(TAG "[%s] signal_pending after.\n", __func__);

		mutex_lock(&dev->mutex);//
	}

	if (count > dev->current_len)
		count = dev->current_len;

	if (copy_to_user(buf, dev->mem, count)) {
		printk(TAG "[%s] -EFAULT:%d read %u bytes.\n", __func__, -EFAULT, count);
		ret = -EFAULT;
		goto out1;
	} else {
		memcpy(dev->mem, dev->mem + count, dev->current_len - count);
		dev->current_len -= count;

		printk(TAG "[%s] read %u bytes, current_len: %u.\n", __func__, count, dev->current_len);
		
		printk(TAG "[%s] wake_up_interruptible before.\n", __func__);
		wake_up_interruptible(&dev->w_wait); /*wake up w_wait*/
		printk(TAG "[%s] wake_up_interruptible after.\n", __func__);

		ret = count;
	}

out1:
	mutex_unlock(&dev->mutex);//
out2:
	remove_wait_queue(&dev->r_wait, &wait); /**/
	set_current_state(TASK_RUNNING);

	return ret;
}

static ssize_t globalfifo_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	int ret = 0;
	struct globalfifo_dev *dev = filp->private_data;
	DECLARE_WAITQUEUE(wait, current); /**/

	printk(TAG "[%s] count: %d. start.\n", __func__, (int) count);

	mutex_lock(&dev->mutex);//
	add_wait_queue(&dev->w_wait, &wait); /**/

	while (dev->current_len == GLOBALFIFO_SIZE) {
		if (filp->f_flags & O_NONBLOCK) {
			printk(TAG "[%s] filp->f_flags is O_NONBLOCK. ret\n", __func__);
			ret = -EAGAIN;
			goto out1;
		}
		__set_current_state(TASK_INTERRUPTIBLE);

		mutex_unlock(&dev->mutex);//

		printk(TAG "[%s] schedule before.\n", __func__);
		schedule();
		printk(TAG "[%s] schedule after.\n", __func__);

		printk(TAG "[%s] signal_pending before.\n", __func__);
		if (signal_pending(current)) {
			printk(TAG "[%s] signal_pending.\n", __func__);
			ret = -ERESTARTSYS;
			goto out2;
		}
		printk(TAG "[%s]  signal_pending after.\n", __func__);

		mutex_lock(&dev->mutex);//
	}

	if (count > GLOBALFIFO_SIZE - dev->current_len)
		count = GLOBALFIFO_SIZE - dev->current_len;

	if (copy_from_user(dev->mem + dev->current_len, buf, count)) {
		printk(TAG "[%s] -EFAULT:%d write %u bytes.\n", __func__, -EFAULT, count);
		ret = -EFAULT;
		goto out1;
	} else {
		dev->current_len += count;

		printk(TAG "[%s] written %u bytes, current_len: %u.\n", __func__, count, dev->current_len);
		
		printk(TAG "[%s] wake_up_interruptible before.\n", __func__);
		wake_up_interruptible(&dev->r_wait); /*wake up R_wait*/
		printk(TAG "[%s] wake_up_interruptible after.\n", __func__);

		ret = count;
	}

out1:
	mutex_unlock(&dev->mutex);//
out2:
	remove_wait_queue(&dev->w_wait, &wait); /**/
	set_current_state(TASK_RUNNING);

	return ret;

}

static ssize_t globalfifo_open(struct inode *inode, struct file *filp)
{
	//struct globalfifo_dev *dev = container_of(inode->i_cdev, struct globalfifo_dev, cdev);
	//filp->private_data = dev;

	struct globalfifo_dev *dev = container_of(inode->i_cdev, struct globalfifo_dev, cdev);
	filp->private_data = dev;

	printk(TAG "[%s] container_of private_data.\n", __func__);

	return 0;
}


static int globalfifo_release(struct inode *inode, struct file *filp)
{
	printk(TAG "[%s] release.\n", __func__);
	return 0;
}

static loff_t globalfifo_llseek(struct file *filp, loff_t offset, int arg)
{
	loff_t ret = 0;
	switch(arg) {
	case 0: //begin from the start
		if (offset < 0) {
			ret = -EINVAL;
			break;
		}
		if ((unsigned int)offset > GLOBALFIFO_SIZE) {
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
		if ((unsigned int)offset + (unsigned int)filp->f_pos > GLOBALFIFO_SIZE) {
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

static long globalfifo_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct globalfifo_dev *dev = filp->private_data;
	switch(cmd) {
	case FIFO_CLEAR:
		mutex_lock(&dev->mutex);//
		memset(dev->mem, 0, GLOBALFIFO_SIZE);
		mutex_unlock(&dev->mutex);//
		printk(TAG "[%s] ioctl CLEAR.\n", __func__);
		break;
	default:
		 return -EINVAL;
	}
	return 0;
}

static unsigned int globalfifo_poll(struct file *filp, poll_table *wait)
{
	unsigned int mask = 0;
	struct globalfifo_dev *dev = filp->private_data;

	mutex_lock(&dev->mutex);//
	poll_wait(filp, &dev->r_wait, wait);
	poll_wait(filp, &dev->w_wait, wait);

	if (dev->current_len != 0) {
		mask |= POLLIN | POLLRDNORM;
		printk(TAG "[%s] poll POLLIN | POLLRDNORM.\n", __func__);
	}
	if (dev->current_len != GLOBALFIFO_SIZE) {
		mask |= POLLOUT | POLLWRNORM;
		printk(TAG "[%s] poll POLLOUT | POLLWRNORM.\n", __func__);
	}

	mutex_unlock(&dev->mutex);//

	return mask;
}

static struct file_operations globalfifo_fops = {
	.owner = THIS_MODULE,
	.open = globalfifo_open,
	.read = globalfifo_read,
	.write = globalfifo_write,
	.release = globalfifo_release,
	.poll = globalfifo_poll, /**/
	.llseek = globalfifo_llseek,
	.unlocked_ioctl = globalfifo_ioctl,

};

static void globalfifo_setup_cdev(struct globalfifo_dev *dev, int index)
{
	int err, devno = MKDEV(globalfifo_major, index);

	cdev_init(&dev->cdev, &globalfifo_fops);			//init cdev
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);			//register cdev, bind devno

	if (err)
		printk(TAG "ERROR %d adding globalfifo %d", err, index);
}

static int __init character_devices_wq_poll_init(void)
{
	int ret;
	// int i;
	dev_t devno = MKDEV(globalfifo_major, 0);


	if (globalfifo_major)							//init devno
		//ret = register_chrdev_region(devno, GLOBALFIFO_NUM, "character_devices_wq_poll-globalfifo_name1_n");
		ret = register_chrdev_region(devno, 1, "character_devices_wq_poll-globalfifo_name1_n");
	else {
		//ret = alloc_chrdev_region(&devno, 0, GLOBALFIFO_NUM, "character_devices_wq_poll-globalfifo_name2_n");
		ret = alloc_chrdev_region(&devno, 0, 1, "character_devices_wq_poll-globalfifo_name2_n");
		globalfifo_major = MAJOR(devno);
	}
	
	if (ret < 0) {
		printk(TAG "character_devices_wq_poll_init *chrdev_region fail: %d.\n", ret);
		return ret;
	}

	//globalfifo_devp = kzalloc(sizeof(struct globalfifo_dev) * GLOBALFIFO_NUM, GFP_KERNEL);
	globalfifo_devp = kzalloc(sizeof(struct globalfifo_dev) * 1, GFP_KERNEL);
	if (!globalfifo_devp) {
		ret = -ENOMEM;
		printk(TAG "character_devices_wq_poll_init kzalloc fail: %d.\n", ret);

		goto fail_malloc;
	}

	//mutex_init(&globalfifo_devp->mutex); // bug: only for first devp

	//for (i = 0; i < GLOBALFIFO_NUM; i++) {
		globalfifo_setup_cdev(globalfifo_devp, 0);
		//globalfifo_setup_cdev(globalfifo_devp + i, i);

		//mutex_init(&(globalfifo_devp + i)->mutex);
		mutex_init(&globalfifo_devp->mutex);
	//}

	init_waitqueue_head(&globalfifo_devp->r_wait); /**/
	init_waitqueue_head(&globalfifo_devp->w_wait); /**/

	printk(TAG "character_devices_wq_poll_init sucess\n");
	return 0;


fail_malloc:
	unregister_chrdev_region(devno, 1);
	return ret;
}

static void __exit character_devices_wq_poll_exit(void)
{
	//int i;

	//for (i = 0; i < GLOBALFIFO_NUM; i++)
		//cdev_del(&(globalfifo_devp + i)->cdev);	
		cdev_del(&globalfifo_devp->cdev);				//unregister cdev

	kfree(globalfifo_devp);
	//unregister_chrdev_region(MKDEV(globalfifo_major, 0), GLOBALFIFO_NUM);
	unregister_chrdev_region(MKDEV(globalfifo_major, 0), 1);

	printk(TAG "character_devices_wq_poll_exit sucess\n");
}

module_init(character_devices_wq_poll_init);
module_exit(character_devices_wq_poll_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_LICENSE("GPL");

