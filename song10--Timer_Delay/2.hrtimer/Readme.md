
# hrtimer

Linux 内核支持 tickless 和 NO_HZ 模式后，内核也包含对 hrtimer （高精度定时器）的支持，它可以支持到微秒级别的精度。

如下例子，在声卡打开的时候通过 hrtimer_init()初始化了 hrtimer ，并指定回调函数为 snd_hrtimer_callback()；
在启动播放（SNDRV_PCM_TRIGGER_START ）等时刻通过 hrtimer_start() 启动了 hrtimer ; 
iprtd->poll_time_ns 纳秒后，时间到 snd_hrtimer_callback() 函数在中断上下文被执行，它紧接着又通过 hrtimer_forward_now() 把 hrtimer 的时间前移了 iprtd -> poll_time_ns 纳秒，这样周而复始；
直到声卡被关闭，又调用了 hrtimer_cancel() 取消在 open 时初始化的 hrtimer 。

`common/sound/soc/fsl/imx-pcm-fiq.c`

```c


static int snd_imx_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct imx_pcm_runtime_data *iprtd = runtime->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		...
		hrtimer_start(&iprtd->hrt, ns_to_ktime(iprtd->poll_time_ns),
		      HRTIMER_MODE_REL);
	...
}
static int snd_imx_open(struct snd_pcm_substream *substream)
{
	...
	hrtimer_init(&iprtd->hrt, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	iprtd->hrt.function = snd_hrtimer_callback;
	...
}

static int snd_imx_close(struct snd_pcm_substream *substream)
{
	...
	kfree(iprtd);
}

static const struct snd_pcm_ops imx_pcm_ops = {
	.open		= snd_imx_open,
	.close		= snd_imx_close,
	.trigger	= snd_imx_pcm_trigger,
	...	
}
```