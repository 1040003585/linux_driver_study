
# delayed_work

除了定时器以外，在 Linux 内核中还可以利用一套封装得很好的快捷机制，本质是利用工作队列和定时器实现，这套快捷机制就是 delayed_work.

```c
struct delayed_work {
	struct work_struct work;
	struct timer_list timer;

	/* target workqueue and CPU ->timer uses to queue ->work */
	struct workqueue_struct *wq;
	int cpu;
	
};
```

如下是个例子模板：

```c

行 847: static void xxx_change(struct xxx_charger *charger)    
行 857:         //cancel_delayed_work_sync(&usbwork);
    static int xxx_battery_event(struct notifier_block *nb, unsigned long event,    
行 979:             xxx_change(charger);    
行 984:             xxx_change(charger);    
行 988:             xxx_change(charger);    
行 1596: static void xxx_charging_monitor(struct work_struct *work)    
行 1700:     schedule_delayed_work(&charger->work, charger→interval);    
行 1703: static void xxx_usb(struct work_struct *work)    
行 1796:     schedule_delayed_work(&usbwork, msecs_to_jiffies(5* 1000));    
行 1799: static int xxx_battery_probe(struct platform_device *pdev)
    charger->nb.notifier_call = xxx_battery_event;
    ret = xxx_register_notifier(charger->master, &charger->nb, xxx_NOTIFIER_ON);
    if (ret)
        goto err_notifier;    
行 2232:     INIT_DELAYED_WORK(&charger->work, xxx_charging_monitor);    
行 2233:     schedule_delayed_work(&charger->work, charger->interval);    
行 2236:     INIT_DELAYED_WORK(&usbwork, xxx_usb);    
行 2237:     schedule_delayed_work(&usbwork, msecs_to_jiffies(7 * 1000));    
行 2256: err_notifier:    
行 2257:     cancel_delayed_work_sync(&charger→work);    
行 2266: static int xxx_battery_remove(struct platform_device *dev)    
行 2276:     cancel_delayed_work_sync(&charger→work);    
行 2289: static int xxx_suspend(struct platform_device *dev, pm_message_t state)    
行 2296:     cancel_delayed_work_sync(&charger->work);    
行 2297:     cancel_delayed_work_sync(&usbwork);    
行 2310:     printk("!!!!!!!!!xxx_suspend\n");    
行 2333: static int xxx_resume(struct platform_device *dev)    
行 2341:     printk("!!!!!!!!!xxx_resume\n");    
行 2379:     schedule_delayed_work(&charger->work, charger->interval);    
行 2380:     schedule_delayed_work(&usbwork, msecs_to_jiffies(7 * 1000));    
行 2385: static void xxx_shutdown(struct platform_device *dev)    
行 2390:     cancel_delayed_work_sync(&charger->work);    
行 2408: static struct platform_driver xxx_battery_driver = {    
行 2413:     .probe = xxx_battery_probe,    
行 2414:     .remove = xxx_battery_remove,    
行 2415:     .suspend = xxx_suspend,    
行 2416:     .resume = xxx_resume,    
行 2417:     .shutdown = xxx_shutdown,

```