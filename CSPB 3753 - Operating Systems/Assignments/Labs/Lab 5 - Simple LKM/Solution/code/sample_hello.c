/*  
 *  sample_hello.c - The simplest kernel module.
 *
 *  Kernel module that is to be loaded at runtime. Simply logs "Hello World" when loaded and "Goodbye World" when unloaded.
 */
#include <linux/init.h> // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h> // Core header for loading LKMs into the kernel
#include <linux/kernel.h> // Contains types, macros, functions for the kernel
#include <linux/slab.h>  // For kmalloc and kfree

#define SIZE 1024 // Size of the buffer

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
    printk(KERN_INFO "3753: Hello, world.\n"); // Hello message
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
        dynamic_buffer = NULL; // Set the pointer to NULL
        printk(KERN_INFO "kmalloc Example: Memory freed\n"); // Success message
    }
    printk(KERN_INFO "3753: Goodbye, world.\n"); // Goodbye message
}

// Init and exit macros
module_init(kmalloc_example_init); // Registering the entry point
module_exit(kmalloc_example_exit); // Registering the exit point

// Module information
MODULE_LICENSE("GPL"); // License of the module (General Public License)
MODULE_AUTHOR("Taylor Larrehcea"); // Author of the module (Guess who? :))
MODULE_DESCRIPTION("3753: A simple kernel module using a buffer with dynamic memory instead of global."); // Description of the module
MODULE_VERSION("0.1"); // Version of the module