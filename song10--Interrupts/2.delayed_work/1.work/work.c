#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
//#include <linux/workqueue.h>

//#include <linux/slab.h> //kzalloc
//#include <linux/platform_device.h>

#define TAG "[work] "

struct delayed_work usbwork;

void work_usb(struct work_struct *work)
{
    printk(TAG "%s.\n", __func__);

    // reschedule for the next time 
    schedule_delayed_work(&usbwork, msecs_to_jiffies(1* 1000));
}

/*
struct work_charger {
	struct delayed_work work;
	unsigned int interval;
};
*/


/*
static void work_charging_monitor(struct work_struct *work)
{
    struct work_charger *charger;

    printk(TAG "%s.\n", __func__);

    charger = container_of(work, struct work_charger, work.work);
    // reschedule for the next time 
    schedule_delayed_work(&charger->work, charger->interval);
}
*/

/*
static int work_probe(struct platform_device *pdev)
{
    struct work_charger *charger;

    printk(TAG "%s.\n", __func__);

    charger = kzalloc(sizeof(*charger), GFP_KERNEL);
    if (charger == NULL)
        return -ENOMEM;

    platform_set_drvdata(pdev, charger);

    charger->interval = msecs_to_jiffies(10 * 1000);
    INIT_DELAYED_WORK(&charger->work, work_charging_monitor);
    schedule_delayed_work(&charger->work, charger->interval);

    INIT_DELAYED_WORK(&usbwork, work_usb);
    schedule_delayed_work(&usbwork, msecs_to_jiffies(7 * 1000));

    return 0;
}

static int work_remove(struct platform_device *dev)
{
    struct work_charger *charger = platform_get_drvdata(dev);

    printk(TAG "%s.\n", __func__);
    cancel_delayed_work_sync(&charger->work);
    kfree(charger);

    return 0;
}

static int work_suspend(struct platform_device *dev, pm_message_t state)
{
    struct work_charger *charger = platform_get_drvdata(dev);

    printk(TAG "%s.\n", __func__);
    cancel_delayed_work_sync(&charger->work);
    cancel_delayed_work_sync(&usbwork);

    return 0;
}


static int work_resume(struct platform_device *dev)
{
    struct work_charger *charger = platform_get_drvdata(dev);

    printk(TAG "%s.\n", __func__);
    schedule_delayed_work(&charger->work, charger->interval);
    schedule_delayed_work(&usbwork, msecs_to_jiffies(7 * 1000));

    return 0;
}

static void work_shutdown(struct platform_device *dev)
{
    struct work_charger *charger = platform_get_drvdata(dev);

    printk(TAG "%s.\n", __func__);
    cancel_delayed_work_sync(&charger->work);
}

static struct platform_driver work_driver = {
    .driver = {
        .name = "work216-supplyer",
        .owner  = THIS_MODULE,
    },
    .probe = work_probe,
    .remove = work_remove,
    .suspend = work_suspend,
    .resume = work_resume,
    .shutdown = work_shutdown,
};

static int work_init(void)
{
    int ret =0;

    printk(TAG "%s.\n", __func__);
    ret = platform_driver_register(&work_driver);

    return ret;
}

static void work_exit(void)
{
    printk(TAG "%s.\n", __func__);
    platform_driver_unregister(&work_driver);
}
*/

static int work_init(void)
{
    printk(TAG "%s.\n", __func__);

    INIT_DELAYED_WORK(&usbwork, work_usb);
    schedule_delayed_work(&usbwork, msecs_to_jiffies(2 * 1000));

    return 0;
}

static void work_exit(void)
{
    printk(TAG "%s.\n", __func__);
    cancel_delayed_work_sync(&usbwork);
}

subsys_initcall(work_init);
module_exit(work_exit);

MODULE_AUTHOR("Chengbing.Wu");
MODULE_LICENSE("GPL v2");

