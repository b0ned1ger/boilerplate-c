#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("abc");

static unsigned int PID = 1;
module_param(PID, int, 0400);

void print_task(struct task_struct *task)
{
	printk("Process: %s, parent process: %s\n", task->comm, task->parent->comm);
}

static int find_task(void)
{
	struct task_struct *task = NULL;

	for_each_process(task) {
		if (task->pid == (pid_t)PID) {
			print_task(task);
		}
	}
	return 0;
}

static int test_hello_init(void)
{
    find_task();
    printk(KERN_INFO"%s: In init\n", __func__);
    return 0;
}

static void test_hello_exit(void)
{
    printk(KERN_INFO"%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
