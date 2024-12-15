#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>  // For kmalloc and kfree

#define SIZE 1024

static char *dynamic_buffer;

static int __init kmalloc_example_init(void)
{
    // Allocate memory using kmalloc
    dynamic_buffer = kmalloc(SIZE, GFP_KERNEL);

    if (!dynamic_buffer) {
        printk(KERN_ALERT "Failed to allocate memory with kmalloc\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "kmalloc Example: Memory allocated successfully\n");
    return 0;
}

static void __exit kmalloc_example_exit(void)
{
    // Free the allocated memory using kfree
    if (dynamic_buffer) {
        kfree(dynamic_buffer);
        dynamic_buffer = NULL;  # forget the old pointer to memory just in case.
        printk(KERN_INFO "kmalloc Example: Memory freed\n");
    }
}

module_init(kmalloc_example_init);
module_exit(kmalloc_example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("3753: A simple kernel module using kmalloc");
MODULE_VERSION("0.1");

