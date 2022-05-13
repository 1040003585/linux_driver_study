#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "file_operations"
#define TAG "[file_operations]"

static unsigned char mem[1000];
static char read_flag = 'y';
static int written_count = 0;

static ssize_t file_operations_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	if (read_flag == 'n') {
		copy_to_user(buf, (void*) mem, written_count);

		printk(TAG " [%s] read written_count: %d\n", __func__, (int) written_count);
		printk(TAG " [%s] count: %d\n", __func__, (int) count);

		read_flag = 'y';
		return written_count;
	} else {
		printk(TAG " [%s] can not read data!!! count: %d\n", __func__, (int) count);
		return 0;
	}
}

static ssize_t file_operations_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	copy_from_user(mem, buf, count);

	read_flag = 'n';
	written_count = count;

	printk(TAG " [%s] written count: %d\n", __func__, (int) written_count);

	return written_count;

}

static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .read = file_operations_read, .write = file_operations_write };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };


static int file_operations_init(void)
{
	int ret;
	
	ret = misc_register(&misc);

	printk(TAG "file_operations_init sucess\n");
	return ret;
}

static void file_operations_exit(void)
{
	misc_deregister(&misc);

	printk(TAG "file_operations_exit sucess\n");
}

module_init(file_operations_init);
module_exit(file_operations_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_DESCRIPTION("statistics of word count.");
MODULE_ALIAS("word count module.");
MODULE_LICENSE("GPL");

