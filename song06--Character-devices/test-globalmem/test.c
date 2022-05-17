#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/mutex.h>

#define GLOBALMEM_SIZE 0x1000 
#define GLOBALMEM_MAJOR 0
#define GLOBALMEM_MAGIC 'g'
#define MEM_CLEAR _IO(GLOBALMEM_MAGIC, 0)
#define GLOBALMEM_NUM 10
static int globalmem_major = GLOBALMEM_MAJOR;
module_param(globalmem_major, int, S_IRUGO);

struct globalmem_dev{
    struct cdev cdev;
    unsigned char mem[GLOBALMEM_SIZE];
    struct mutex mutex;
};
struct globalmem_dev *globalmem_devp;


static ssize_t globalmem_read(struct file *filp, char __user *buff, size_t size, loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    struct globalmem_dev *dev = filp->private_data;
    if (p >= GLOBALMEM_SIZE)
        return 0;
    if (count > GLOBALMEM_SIZE - p)
        count = GLOBALMEM_SIZE - p;
    mutex_lock(&dev->mutex);
    if (copy_to_user(buff, dev->mem + p, count)){
        ret = -EFAULT;
    }else{
        *ppos += count;
        ret = count;
        printk(KERN_INFO"read %u bytes from %lu\n", count, p);
    }
    mutex_unlock(&dev->mutex);
    return ret;
}

static ssize_t globalmem_write(struct file *filp, const char __user *buff, size_t size, loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret;
    struct globalmem_dev *dev = filp->private_data;
    if (p >= GLOBALMEM_SIZE)
        return 0;
    if (count > GLOBALMEM_SIZE - p)
        count = GLOBALMEM_SIZE - p;
    mutex_lock(&dev->mutex);
    if (copy_from_user(dev->mem + p, buff, count)){
        ret = -EFAULT;
    }else
    {
        *ppos += count;
        ret = count;
        printk(KERN_INFO"written %u bytes from %lu\n", count, p);
    }
    mutex_unlock(&dev->mutex);
    return ret;
}

static int globalmem_open(struct inode *inode, struct file *filp)
{
    struct globalmem_dev *dev = container_of(inode->i_cdev, struct globalmem_dev, cdev);
    filp->private_data = dev;
    return 0;
}

static int globalmem_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static loff_t globalmem_llseek(struct file *filp, loff_t offset, int arg)
{
    loff_t ret = 0;
    switch(arg){
    case 0://begin from the start
        if (offset < 0)
        {
            ret = -EINVAL;
            break;
        }
        if ((unsigned int)offset > GLOBALMEM_SIZE){
            ret = -EINVAL;
            break;
        }
        filp->f_pos = offset;
        ret = filp->f_pos;
        break;
    case 1://begin from current position
        if ((unsigned int)offset + (unsigned int)filp->f_pos < 0)
        {
            ret = -EINVAL;
            break;
        }
        if ((unsigned int)offset + (unsigned int)filp->f_pos > GLOBALMEM_SIZE)
        {
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
    switch(cmd){
        case MEM_CLEAR:
            mutex_lock(&dev->mutex);
            memset(dev->mem, 0, GLOBALMEM_SIZE);
            mutex_unlock(&dev->mutex);
            printk(KERN_INFO"globalmem is set to zero\n");
            break;
       default:
            return -EINVAL;
    }
    return 0;
}
static const struct file_operations globalmem_fops = {
    .owner = THIS_MODULE,
    .llseek = globalmem_llseek,
    .read = globalmem_read,
    .write = globalmem_write,
    .open = globalmem_open,
    .release = globalmem_release,
    .unlocked_ioctl = globalmem_ioctl,
};

static void globalmem_setup_cdev(struct globalmem_dev *dev, int index)
{
    int err, devno = MKDEV(globalmem_major, index);
    cdev_init(&dev->cdev, &globalmem_fops);
    dev->cdev.owner = THIS_MODULE;
    err = cdev_add(&dev->cdev, devno, 1);
    if (err)
        printk(KERN_NOTICE"ERROR %d adding globalmem %d", err, index);
}

static int __init globalmem_init(void){
    int i = 0;
    int ret;
    //allocate dev_t
    dev_t devno = MKDEV(globalmem_major, 0);
    if (globalmem_major)
    {
        ret = register_chrdev_region(globalmem_major, GLOBALMEM_NUM, "globalmem");
    }else
    {
        ret = alloc_chrdev_region(&devno, 0, GLOBALMEM_NUM, "globalmem");
        globalmem_major = MAJOR(devno);
    }
    if (ret < 0)
    {
        return ret;
    }

    // allocate memory for device
    globalmem_devp = kzalloc(sizeof(struct globalmem_dev) * GLOBALMEM_NUM, GFP_KERNEL);
    if (!globalmem_devp)
    {
        ret = -ENOMEM;
        goto fail_malloc;
    }
    mutex_init(&globalmem_devp->mutex);
    //register cdev
    for (i = 0; i < GLOBALMEM_NUM; ++i)
    {
        globalmem_setup_cdev(globalmem_devp, i);
    }
    return 0;
fail_malloc:
    unregister_chrdev_region(devno, GLOBALMEM_NUM);
    return ret;
}
module_init(globalmem_init);

static void __exit globalmem_exit(void)
{
    int i = 0;
    for (i = 0; i < GLOBALMEM_NUM; ++i)
        cdev_del(&(globalmem_devp+i)->cdev);
    kfree(globalmem_devp);
    unregister_chrdev_region(MKDEV(globalmem_major, 0), GLOBALMEM_NUM);
}
module_exit(globalmem_exit);
MODULE_LICENSE("Dual BSD/GPL");

