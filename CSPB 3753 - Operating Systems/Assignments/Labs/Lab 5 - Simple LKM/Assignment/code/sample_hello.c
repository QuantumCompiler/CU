#include <linux/module.h>
#include <linux/kernel.h>

/*Module's init entry point */
static int helloworld_init(void)
{
    pr_info("3753: looks good");
    printk(KERN_ALERT "3753: Hello world\n");
    return 0;
}

/*Module's cleanup entry point */
static void helloworld_cleanup(void)
{
    printk(KERN_ALERT "3753: Goodbye world\n");
}

module_init(helloworld_init);
module_exit(helloworld_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("A simple kernel module for 3753");
