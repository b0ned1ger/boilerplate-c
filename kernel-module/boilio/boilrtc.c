#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_LICENSE("abc");

#define RTC_ADDRESS	0x0072
#define RTC_DATA	0x0072

#define SECONDS		0x00
#define MINUTES		0x02
#define HOURS		0x04
#define DAY_WEEK	0x06
#define DAY_MONTH	0x07
#define MONTH		0x08
#define YEAR		0x09

#define REGA		0x0A
#define REGB		0x0B
#define REGC		0x0C
#define REGD		0x0D

unsigned char rtc_read(unsigned char address)
{
	outb_p(address, RTC_ADDRESS);
	return inb_p(RTC_DATA);
}

void rtc_write(unsigned char address, unsigned char value)
{
	outb_p(address, RTC_ADDRESS);
	outb_p(value, RTC_DATA);
}

static int __init rtc_init(void)
{
	unsigned char regb = rtc_read(REGB);

	pr_info("Register B:%02x\n", regb);

	// We do not need to request exclusive region since it is already
	// binded to RTC driver
	//if (!request_region(MY_BASEPORT, NUMBER_PORTS, "myports")) {
	//	pr_info("requested region failed for myports \n");
	//} else {
	//	pr_info("requested regions sucess for my ports \n");
	//}

	if (regb & 0x01) {
		pr_info("Daylight saving is enabled \n");
	} else {
		pr_info("Daylight saving is disabled \n");
	}

	if (regb & 0x02) {
		pr_info("24 hour mode \n");
	} else {
		pr_info("12 hour mode \n");
	}

	if (regb & 0x04) {
		pr_info("Data in binary Format \n");
	} else {
		pr_info("Data in BCD format \n");
	}

	printk(KERN_INFO"%s: In init\n", __func__);

	pr_info("Hours:%02x\t Minutes:%02x\t Seconds:%02x\n",
			rtc_read(HOURS), rtc_read(MINUTES), rtc_read(SECONDS));

	rtc_write(HOURS, 2);
	rtc_write(MINUTES, 2);
	rtc_write(SECONDS, 2);

	pr_info("Hours:%02x\t Minutes:%02x\t Seconds:%02x\n",
			rtc_read(HOURS), rtc_read(MINUTES), rtc_read(SECONDS));

	return 0;
}

static void rtc_exit(void)
{
	printk(KERN_INFO"%s: In exit\n", __func__);
	// Nothing to release
	// release_region(MY_BASEPORT, NUMBER_PORTS);
}

module_init(rtc_init);
module_exit(rtc_exit);
