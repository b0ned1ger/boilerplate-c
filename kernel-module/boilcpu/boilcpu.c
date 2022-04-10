#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>

MODULE_LICENSE("abc");

char buffer[256];
char * get_task_state(long state)
{
	switch (state) {
		case TASK_RUNNING:
			return "TASK_RUNNING";
		case TASK_INTERRUPTIBLE:
			return "TASK_INTERRUPTIBLE";
		case TASK_UNINTERRUPTIBLE:
			return "TASK_UNINTERRUPTIBLE";
		case __TASK_STOPPED:
			return "__TASK_STOPPED";
		case __TASK_TRACED:
			return "TASK_TRACED";
		default:
		{
			sprintf(buffer, "Unknown Typer:%ld\n", state);
			return buffer;
		}
	}
}

static int list_tasks(void)
{
	struct task_struct *task_list;
	unsigned int process_count = 0;
	pr_info("CPUs online %d \n", num_online_cpus());
	for_each_process(task_list) {
		pr_info("Task: %s\t PID:[%d]\t State:%s\n", task_list->comm,
				task_list->pid, get_task_state(task_list->state));
		process_count++;
	}
	pr_info("Number of tasks: %u\n", process_count);
	return 0;
}


static int test_hello_init(void)
{
    list_tasks();
    printk(KERN_INFO"%s: In init\n", __func__);
    return 0;
}

static void test_hello_exit(void)
{
    printk(KERN_INFO"%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);