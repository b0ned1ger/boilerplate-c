#include <linux/kernel.h>
#include <linux/module.h>
#include "func.h"

MODULE_LICENSE("abc");

int stack = 0;
static int test_arguments(void);
static void test_hello_dump_stack(void);

module_param(stack, int, S_IRUGO);

static int test_hello_init(void)
{
    test_arguments();
    printk(KERN_INFO"%s: In init\n", __func__);
    func();
    return 0;
}

static int test_arguments(void)
{
	if (stack)
		test_hello_dump_stack();
	return 0;
}

static void test_hello_exit(void)
{
    printk(KERN_INFO"%s: In exit\n", __func__);
}

static void test_hello_dump_stack(void)
{
    printk(KERN_INFO"%s: dumping stack! \n", __func__);
    dump_stack();
}

module_init(test_hello_init);
module_exit(test_hello_exit);
