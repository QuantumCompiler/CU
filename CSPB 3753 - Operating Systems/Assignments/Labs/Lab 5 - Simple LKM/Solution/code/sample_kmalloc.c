/*  
 *  sample_hello.c - The simplest kernel module.
 *
 *  Kernel module that is to be loaded at runtime. Simply logs "Hello World" when loaded and "Goodbye World" when unloaded.
 *  This is built with kmalloc (kernel memory allocation) to allocate memory at runtime instead of using global memory (like in sample_hello.c).
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>  // For kmalloc and kfree

#define SIZE 1024

static char *dynamic_buffer; // Pointer to the allocated memory

/*
    The entry point for the module means the function that will be called when the module is loaded.
    The __init macro tells the kernel that this code is to be used at "init time".
*/

static int __init kmalloc_example_init(void)
{
    // Allocate memory using kmalloc
    dynamic_buffer = kmalloc(SIZE, GFP_KERNEL);

    if (!dynamic_buffer) {
        printk(KERN_ALERT "Failed to allocate memory with kmalloc\n"); // Error message
        return -ENOMEM;
    }

    printk(KERN_INFO "kmalloc Example: Memory allocated successfully\n"); // Success message
    return 0;
}

/*
    The exit point for the module means the function that will be called when the module is unloaded.
    The __exit macro tells the kernel that this code is to be used at "exit time".
*/

static void __exit kmalloc_example_exit(void)
{
    // Free the allocated memory using kfree
    if (dynamic_buffer) {
        kfree(dynamic_buffer); // Free the memory (deallocate with kfree)
        dynamic_buffer = NULL;  # forget the old pointer to memory just in case. // Set the pointer to NULL
        printk(KERN_INFO "kmalloc Example: Memory freed\n"); // Success message
    }
    printk(KERN_INFO "3753: Goodbye, world.\n");
}

module_init(kmalloc_example_init); // Registering the entry point
module_exit(kmalloc_example_exit); // Registering the exit point

MODULE_LICENSE("GPL"); // License of the module (General Public License)
MODULE_AUTHOR("Taylor Larrehcea"); // Author of the module (Guess who? :))
MODULE_DESCRIPTION("3753: A simple kernel module using kmalloc"); // Description of the module
MODULE_VERSION("0.1"); // Version of the module

