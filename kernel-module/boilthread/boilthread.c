#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/kthread.h>             //kernel threads
#include <linux/sched.h>               //task_struct 
#include <linux/delay.h>
 
static struct task_struct *my_thread;
static struct task_struct *print_thread;
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
            return "__TASK_TRACED";
	case TASK_IDLE:
	    return "(TASK_UNINTERRUPTIBLE | TASK_NOLOAD)";
	case TASK_KILLABLE:
	    return "(TASK_WAKEKILL | TASK_UNINTERRUPTIBLE)";
	case TASK_STOPPED:
	    return "(TASK_WAKEKILL | __TASK_STOPPED)";
	case TASK_TRACED:
	    return "(TASK_WAKEKILL | __TASK_TRACED)";
        default:
        {
            sprintf(buffer, "Unknown Type:%ld", state);
            return buffer;
        }
    }
}

static int print_running_thread(void *data)
{
	 while(!kthread_should_stop()) {
		 struct task_struct *task_list;
		 for_each_process(task_list) {
			 if (task_list->state == TASK_RUNNING)
				 pr_info("Process: %s\t PID:[%d]\t State:%s\n", 
						 task_list->comm, task_list->pid,
						 get_task_state(task_list->state));
		 }
		 msleep(500);
	 }
	 return 0;
}

int thread_function(void *pv)
{
    int i=0;
    while(!kthread_should_stop()) {
        printk(KERN_INFO "In Thread Function %d\n", i++);
        msleep(1000);
    }
    return 0;
}
 
 
static int __init my_driver_init(void)
{

	my_thread = kthread_create(thread_function,NULL,"myThread");
	if(my_thread) {
		wake_up_process(my_thread);
        	print_thread = kthread_run(print_running_thread, NULL, "print_running_cpu");
		return 0;
	} else {
		printk(KERN_ERR "Cannot create kthread\n");
		return -1;
	}
}
 
void __exit my_driver_exit(void)
{
	pr_info("%s: In exit\n", __func__);
        kthread_stop(my_thread);
        kthread_stop(print_thread);
        printk(KERN_INFO "Device Driver Remove...Done!!\n");
}
 
module_init(my_driver_init);
module_exit(my_driver_exit);
 
MODULE_LICENSE("GPL");
