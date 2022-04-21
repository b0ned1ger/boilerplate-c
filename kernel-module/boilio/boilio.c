#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/ioport.h>

MODULE_LICENSE("abc");

#define MY_BASEPORT 0x0062
#define NUMBER_PORTS 2

static int ioport_init(void)
{
	if (!request_region(MY_BASEPORT, NUMBER_PORTS, "myports")) {
		pr_info("requested region failed for myports \n");
	} else {
		pr_info("requested regions sucess for my ports \n");
	}
	printk(KERN_INFO"%s: In init\n", __func__);
	return 0;
}

static void ioport_exit(void)
{
	printk(KERN_INFO"%s: In exit\n", __func__);
	release_region(MY_BASEPORT, NUMBER_PORTS);
}

module_init(ioport_init);
module_exit(ioport_exit);
