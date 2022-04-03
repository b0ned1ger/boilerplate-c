#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("abc");
static int test_hello_init2(void)
{
    printk(KERN_INFO"%s: In init\n", __func__);
    return 0;
}

static void test_hello_exit2(void)
{
    printk(KERN_INFO"%s: In exit\n", __func__);
}

module_init(test_hello_init2);
module_exit(test_hello_exit2);