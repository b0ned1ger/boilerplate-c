#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <asm/current.h>

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

static void get_current_task(void)
{
	pr_info("Current process pid: %d \n", current->pid);
	pr_info("Current process name: %s \n", current->comm);
}

static void walk_to_init_task(void)
{
	struct task_struct *task;
	unsigned int process_count = 0;
	pr_info("Take me to the beginning\n");
	for (task = current; task != &init_task; task=task->parent){
		pr_info("%d: pid=%d name=%s \n",process_count, task->pid, task->comm);
		process_count++;
	}
}

static int test_hello_init(void)
{
    list_tasks();
    get_current_task();
    walk_to_init_task();
    printk(KERN_INFO"%s: In init\n", __func__);
    return 0;
}

static void test_hello_exit(void)
{
    printk(KERN_INFO"%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
