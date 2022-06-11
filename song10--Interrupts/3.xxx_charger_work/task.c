#include "xxx_driver.h"

struct delayed_work usb_charger;

static int s_int = 10;

void usb_charger_work(struct work_struct *work)
{
    printk(TAG "%s.%d\n", __func__, s_int);

    // reschedule for the next time 
    schedule_delayed_work(&usb_charger, msecs_to_jiffies(1* 1000));
}
