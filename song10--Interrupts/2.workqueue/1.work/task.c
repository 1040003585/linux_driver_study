#include "work.h"

struct delayed_work usbwork;

static int s_int = 10;

void work_usb(struct work_struct *work)
{
    printk(TAG "%s.%d\n", __func__, s_int);

    // reschedule for the next time 
    schedule_delayed_work(&usbwork, msecs_to_jiffies(1* 1000));
}
