#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "word_count_userspace"
#define TAG "[word_count_userspace] "

static unsigned char mem[10000];
static int word_count = 0;

#define TRUE 1
#define FALSE 0


static char is_spacewhite(char c)
{
	if (c == ' ' || c == 9 || c == 13 || c == 10)
		return TRUE;
	else
		return FALSE;
}

static int get_word_count(const char *buf)
{
	int n = 1;
	int i = 0;
	char c = ' ';

	char flag = 0; // deal with multi space, 1 mean miss one space

	if (*buf == '\0')
		return 0;

	if (is_spacewhite(*buf) == TRUE)
		n--;

	for (; (c = *(buf + i)) != '\0'; i++) {
		if (flag == 1 && is_spacewhite(c) == FALSE)
			flag = 0;

		else if (flag == 1 && is_spacewhite(c) == TRUE)
			continue;

		if(is_spacewhite(c) == TRUE) {
			n++;
			flag = 1;
		}
	}

	if (is_spacewhite(*(buf + i -1)) ==  TRUE)
		n--;

	return n;
}

static ssize_t word_count_userspace_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	unsigned char temp[4];

	temp[0] = word_count >> 24;
	temp[1] = word_count >> 16;
	temp[2] = word_count >> 8;
	temp[3] = word_count;

	copy_to_user(buf, (void*) temp, 4);

	printk(TAG "[%s] read: word count: %d\n", __func__, (int) count);

	return count; /* Have a bug: contine again run word_count_read until return 0; */
	//return 0; //success function end

}

static ssize_t word_count_userspace_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	ssize_t written = count;

	copy_from_user(mem, buf, count);
	mem[count] = '\0';

	word_count = get_word_count(buf);

	printk(TAG "[%s] get  : char count: %d\n", __func__, (int) count);
	printk(TAG "[%s] write: word count: %d\n", __func__, (int) word_count);

	return written;

}

static struct file_operations dev_fops =
{ .owner = THIS_MODULE, .read = word_count_userspace_read, .write = word_count_userspace_write };

static struct miscdevice misc =
{ .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops };


static int word_count_userspace_init(void)
{
	int ret;
	
	ret = misc_register(&misc);

	printk(TAG "word_count_userspace_init sucess\n");
	return ret;
}

static void word_count_userspace_exit(void)
{
	misc_deregister(&misc);

	printk(TAG "word_count_userspace_exit sucess\n");
}

module_init(word_count_userspace_init);
module_exit(word_count_userspace_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_DESCRIPTION("statistics of word count.");
MODULE_ALIAS("word count module.");
MODULE_LICENSE("GPL");

