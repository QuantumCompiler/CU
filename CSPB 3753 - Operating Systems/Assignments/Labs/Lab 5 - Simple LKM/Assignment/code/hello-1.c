/*  
 *  hello-1.c - The simplest kernel module.
 *
 *  Kernel module that is to be loaded at runtime. Simply logs "Hello World" when loaded and "Goodbye World" when unloaded.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

/*Module's init entry point */

/*
    The entry point for the module means the function that will be called when the module is loaded.
    The __init macro tells the kernel that this code is to be used at "init time".
*/

static int __init helloworld_init(void)
{
    printk(KERN_INFO "Hello world (1)\n"); // Logging Hello World, Kernel style!
    return 0;
}

/*Module's cleanup entry point */

/*
    The exit point for the module means the function that will be called when the module is unloaded.
    The __exit macro tells the kernel that this code is to be used at "exit time".
*/

static void __exit helloworld_cleanup(void)
{
	printk(KERN_INFO "Goodbye world (1)\n"); // Logging Goodbye World, Kernel style!
}

module_init(helloworld_init); // Registering the entry point
module_exit(helloworld_cleanup); // Registering the exit point