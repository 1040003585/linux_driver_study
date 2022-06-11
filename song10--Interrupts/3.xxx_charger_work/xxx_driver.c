/* move to "xxx_driver.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
//#include <linux/workqueue.h>

//#include <linux/slab.h> //kzalloc
//#include <linux/platform_device.h>
*/

#include "xxx_driver.h"


struct xxx_charger {
	struct delayed_work dwork;
	unsigned int interval;
};


static void work_charging_monitor(struct work_struct *work)
{
    struct xxx_charger *charger;
    // struct delayed_work *dworkp;

    printk(TAG "%s.\n", __func__);

    // dworkp = container_of(work, struct delayed_work, work);
    // charger = container_of(dworkp, struct xxx_charger, dwork);
    charger = container_of(work, struct xxx_charger, dwork.work);

    // reschedule for the next time 
    schedule_delayed_work(&charger->dwork, charger->interval);
}



static int xxx_driver_probe(struct platform_device *pdev)
{
    struct xxx_charger *charger;

    printk(TAG "%s.\n", __func__);

    charger = kzalloc(sizeof(*charger), GFP_KERNEL);
    if (charger == NULL)
        return -ENOMEM;

    platform_set_drvdata(pdev, charger);

    charger->interval = msecs_to_jiffies(5 * 1000);
    INIT_DELAYED_WORK(&charger->dwork, work_charging_monitor);
    schedule_delayed_work(&charger->dwork, charger->interval);

    INIT_DELAYED_WORK(&usb_charger, usb_charger_work);
    schedule_delayed_work(&usb_charger, msecs_to_jiffies(2 * 1000));

    return 0;
}

static int xxx_driver_remove(struct platform_device *dev)
{
    struct xxx_charger *charger = platform_get_drvdata(dev);

    printk(TAG "%s.\n", __func__);
    cancel_delayed_work_sync(&charger->dwork);
    kfree(charger);

    return 0;
}

static int xxx_driver_suspend(struct platform_device *dev, pm_message_t state)
{
    struct xxx_charger *charger = platform_get_drvdata(dev);

    printk(TAG "%s.\n", __func__);
    cancel_delayed_work_sync(&charger->dwork);
    cancel_delayed_work_sync(&usb_charger);

    return 0;
}


static int xxx_driver_resume(struct platform_device *dev)
{
    struct xxx_charger *charger = platform_get_drvdata(dev);

    printk(TAG "%s.\n", __func__);
    schedule_delayed_work(&charger->dwork, charger->interval);
    schedule_delayed_work(&usb_charger, msecs_to_jiffies(3 * 1000));

    return 0;
}

static void xxx_driver_shutdown(struct platform_device *dev)
{
    struct xxx_charger *charger = platform_get_drvdata(dev);

    printk(TAG "%s.\n", __func__);
    cancel_delayed_work_sync(&charger->dwork);
}

static struct platform_driver xxx_driver = {
    .driver = {
        .name = "work_device+driver_p",
        .owner  = THIS_MODULE,
    },
    .probe = xxx_driver_probe,
    .remove = xxx_driver_remove,
    .suspend = xxx_driver_suspend,
    .resume = xxx_driver_resume,
    .shutdown = xxx_driver_shutdown,
};

static int xxx_driver_init(void)
{
    int ret =0;

    printk(TAG "%s.\n", __func__);
    ret = platform_driver_register(&xxx_driver);

    return ret;
}

static void xxx_driver_exit(void)
{
    printk(TAG "%s.\n", __func__);
    platform_driver_unregister(&xxx_driver);
}

subsys_initcall(xxx_driver_init);
module_exit(xxx_driver_exit);

