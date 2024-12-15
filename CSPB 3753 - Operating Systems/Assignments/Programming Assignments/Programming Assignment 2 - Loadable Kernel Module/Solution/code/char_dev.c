/*
    CSPB-3753: Operating Systems
    Programming Assignment 2 - LKM
    Taylor Larrechea

    char_dev.c - Character device driver implementation

    This file contains the implementation of a simple character device driver in Linux.
    Function defitions, globals, and others are defined in this file.
    To compile the module, use the Makefile provided in the same directory.

    To test the code, run the test file in this directory.
*/

// Libraries Etc.
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

/*  Globals
        DEVICE_NAME         - Name of the character device
        BUFFER_SIZE         - Size of the device buffer
        MAJOR_NUMBER        - Major number of the character device
        device_buffer       - Pointer to the device buffer
        device_open_count   - Number of times the device has been opened
*/
#define DEVICE_NAME "char_dev"
#define BUFFER_SIZE 1024
#define MAJOR_NUMBER 374
static char *device_buffer;
static int device_open_count = 0;

/*  Function Prototypes
        custom_open     - Opens the device
        custom_release  - Releases the device
        custom_read     - Reads from the device buffer
        custom_write    - Writes to the device buffer
        custom_llseek   - Seeks to a position in the device buffer
*/
static int custom_open(struct inode *, struct file *);
static int custom_release(struct inode *, struct file *);
static ssize_t custom_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t custom_write(struct file *, const char __user *, size_t, loff_t *);
static loff_t custom_llseek(struct file *, loff_t, int);

/*  fops - File operations structure 
        Description:
            Structure containing function pointers to the custom file operations
        Members:
            .owner      - Pointer to the module that owns the structure
            .open       - Pointer to the open function
            .release    - Pointer to the release function
            .read       - Pointer to the read function
            .write      - Pointer to the write function
            .llseek     - Pointer to the llseek function
        References:
            * Linux File Operations: https://tldp.org/LDP/lkmpg/2.6/html/x569.html
*/
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = custom_open,
    .release = custom_release,
    .read = custom_read,
    .write = custom_write,
    .llseek = custom_llseek
};

/*  custom_open - Opens the device 
        Input:
            inode - Pointer to the inode structure representing the device
            file - Pointer to the file structure representing the file associated with the device
        Algorithm:
            * Check if the device is already open
                * If so, log an error message and return -EBUSY (device is busy)
            * Increment the device_open_count
            * Log a message indicating successful opening of the device
            * Return 0 (success)
        Output:
            Returns 0 on success, or -EBUSY if the device is already open
        References:
            * Linux Inode Structure: https://tldp.org/LDP/tlk/fs/filesystem.html#tthFtNtHE
            * Linux File Operations: https://tldp.org/LDP/lkmpg/2.6/html/x569.html
            * Linux Error Codes: https://man7.org/linux/man-pages/man3/errno.3.html
*/
static int custom_open(struct inode *inode, struct file *file) {
    // Check if the device is already open (device_open_count > 0 implies device is open)
    if (device_open_count > 0) {
        printk(KERN_ALERT "CSPB-3753 Device is already open!\n"); // Log error
        return -EBUSY; 
    }
    device_open_count++; // Increment the open count
    printk(KERN_INFO "CSPB-3753 Device opened. Open count: %d\n", device_open_count); // Log success
    return 0;
}

/*  custom_release - Releases the device 
        Input:
            inode - Pointer to the inode structure representing the device
            file - Pointer to the file structure representing the file associated with the device
        Algorithm:
            * Check if any device is open (device_open_count > 0)
                * If so, decrement the device_open_count
                * Log the successful release of the device
                * Return 0 (success)
            * If no device is open, log an error and return -EINVAL
        Output:
            Returns 0 on success, or -EINVAL if no device is currently open
        References:
            * Linux Inode Structure: https://tldp.org/LDP/tlk/fs/filesystem.html#tthFtNtHE
            * Linux File Operations: https://tldp.org/LDP/lkmpg/2.6/html/x569.html
            * Linux Error Codes: https://man7.org/linux/man-pages/man3/errno.3.html
*/
static int custom_release(struct inode *inode, struct file *file) {
    // Check if there are any devices currently open
    if (device_open_count > 0) {
        device_open_count--; // Decrement the open count
        printk(KERN_INFO "CSPB-3753 Device released successfully\n"); // Log success
        return 0;
    } 
    // No open devices, log an error and return -EINVAL
    else {
        printk(KERN_ALERT "CSPB-3753 No devices currently open!\n"); // Log error
        return -EINVAL;
    }
}

/*  custom_read - Reads from the device buffer 
        Input:
            file        - Pointer to the file structure representing the device file
            user_buffer - Pointer to the user space buffer where data will be copied
            count       - Number of bytes requested to read
            offset      - Pointer to the file offset position in the buffer
        Algorithm:
            * Check if the offset is beyond the buffer size
                * If true, log a message and return 0 (indicating EOF)
            * Calculate the number of bytes to read by taking the minimum of the requested count and the remaining buffer size
            * Copy data from the device buffer to the user space buffer using copy_to_user
                * If an error occurs, log the error and return -EFAULT (bad address)
            * Update the file offset to reflect the number of bytes read
            * Log the number of bytes read and the new offset
            * Return the number of bytes successfully read
        Output:
            Returns the number of bytes read from the device buffer, or an error code
        References:
            * Read / Write /proc in Linux: https://linux.die.net/lkmpg/x769.html
*/
static ssize_t custom_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offset) {
    size_t bytes; // Number of bytes to read
    int ret; // Return value
    // Check if offset is beyond the buffer
    if (*offset >= BUFFER_SIZE) {
        printk(KERN_INFO "CSPB-3753 Reached beyond end of buffer\n"); // Log error
        return 0;
    }
    // Calculate the number of bytes to read, considering the buffer size
    bytes = min(count, (size_t)(BUFFER_SIZE - *offset));
    // Copy data to user space
    ret = copy_to_user(user_buffer, device_buffer + *offset, bytes);
    if (ret != 0) {
        printk(KERN_ERR "CSPB-3753 Failed to read data to user space\n"); // Log error
        return -EFAULT;
    }
    // Update the file offset
    *offset += bytes;
    // Log the number of bytes read
    printk(KERN_INFO "CSPB-3753 reading %zu characters at offset %lld\n", bytes, *offset); // Log success
    return bytes;
}

/*  custom_write - Writes to the device buffer 
        Input:
            file        - Pointer to the file structure
            user_buffer - Pointer to the user space buffer containing data to write
            count       - Number of bytes requested to write
            offset      - Pointer to the file offset position in the buffer
        Algorithm:
            * Check if the offset is beyond the buffer size
                * If true, log a message and return 0 (indicating EOF)
            * Calculate the number of bytes to write by taking the minimum of the requested count and the remaining buffer size
            * Copy data from the user space buffer to the device buffer using copy_from_user
                * If an error occurs, log the error and return -EFAULT (bad address)
            * Update the file offset to reflect the number of bytes written
            * Log the number of bytes written and the new offset
            * Return the number of bytes successfully written
        Output:
            Returns the number of bytes written to the device buffer, or an error code
        References:
            * Read / Write /proc in Linux: https://linux.die.net/lkmpg/x769.html
*/
static ssize_t custom_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *offset) {
    size_t bytes; // Number of bytes to write
    int ret; // Return value
    // Check if offset is beyond the buffer
    if (*offset >= BUFFER_SIZE) {
        printk(KERN_INFO "CSPB-3753 Reached beyond end of buffer\n"); // Log error
        return 0; 
    }
    // Calculate the number of bytes to write, considering the buffer size
    bytes = min(count, (size_t)(BUFFER_SIZE - *offset));
    // Copy data from user space
    ret = copy_from_user(device_buffer + *offset, user_buffer, bytes);
    if (ret != 0) {
        printk(KERN_ERR "CSPB-3753 Failed to write data from user space\n"); // Log error
        return -EFAULT;
    }
    // Update the file offset
    *offset += bytes;
    // Log the number of bytes written
    printk(KERN_INFO "CSPB-3753 writing %zu characters at offset %lld\n", bytes, *offset); // Log success
    return bytes;
}

/*  custom_llseek - Seeks to a position in the device buffer 
        Input:
            file   - Pointer to the file structure representing the open file
            offset - The offset to seek to, relative to the whence parameter
            whence - The base position to seek from (SEEK_SET, SEEK_CUR, SEEK_END)
        Algorithm:
            * Calculate the new offset based on the whence parameter:
                * SEEK_SET: Set the new position to the specified offset
                * SEEK_CUR: Set the new position to the current file position + offset
                * SEEK_END: Set the new position to the buffer size + offset
            * Check if the new offset is within valid bounds (0 <= new_offset < BUFFER_SIZE)
                * If the offset is invalid, return -EINVAL (invalid argument)
            * Update the file's current position (file->f_pos) to the new offset
            * Log the seek operation, including the new position
            * Return the new offset on success
        Output:
            Returns the new offset position in the device buffer, or -EINVAL for invalid arguments
        References:
            * lseek System Call in Linux: https://man7.org/linux/man-pages/man2/lseek.2.html
*/
static loff_t custom_llseek(struct file *file, loff_t offset, int whence) {
    loff_t new_offset; // New offset position
    switch (whence) {
        // Calculate the new offset based on the whence parameter
        case SEEK_SET:
            new_offset = offset;
            break;
        // Calculate the new offset based on the current position and offset
        case SEEK_CUR:
            new_offset = file->f_pos + offset;
            break;
        // Calculate the new offset based on the end of the buffer and offset
        case SEEK_END:
            new_offset = BUFFER_SIZE + offset;
            break;
        // Invalid whence parameter
        default:
            printk(KERN_ERR "CSPB-3753 Invalid whence parameter\n"); // Log error
            return -EINVAL;
    }
    // Ensure the new offset is within bounds
    if (new_offset < 0 || new_offset >= BUFFER_SIZE) {
        printk(KERN_ERR "CSPB-3753 Invalid offset\n"); // Log error
        return -EINVAL;
    }
    // Update the file position
    file->f_pos = new_offset;
    // Log the seek operation
    printk(KERN_INFO "CSPB-3753 Seeked to position %lld\n", new_offset); // Log success
    return new_offset;
}

/*  custom_module_init - Initialize the module 
        Algorithm:
            * Register the character device with the kernel using register_chrdev
                * If an error occurs, log the error and return the error code
            * Allocate memory for the device buffer using kmalloc
                * If memory allocation fails, unregister the character device and log an error
            * Log the successful loading of the module
            * Return 0 (success)
        Output:
            Returns 0 on success, or an error code on failure
        References:
            * kmalloc: https://www.kernel.org/doc/htmldocs/kernel-api/API-kmalloc.html
            * register_chrdev / unregister_chrdev: https://www.kernel.org/doc/html/latest/core-api/kernel-api.html#c.__register_chrdev
*/
static int __init custom_module_init(void) {
    int ret; // Return value
    // Register the character device
    ret = register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &fops);
    // Check for errors
    if (ret < 0) {
        printk(KERN_ALERT "Failed to register character device\n"); // Log error
        return ret;
    }
    // Allocate memory for the device buffer
    device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    // Check for memory allocation errors
    if (!device_buffer) {
        unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME); 
        printk(KERN_ALERT "CSPB-3753 Failed to allocate memory for the device buffer\n"); // Log error
        return -ENOMEM;
    }
    // Log the successful loading of the module
    printk(KERN_INFO "CSPB-3753 loaded LKM\n");
    return 0;
}

/*  custom_module_exit - Unload the module 
        Input:
            None
        Algorithm:
            * Free the allocated device buffer using kfree
            * Unregister the character device using unregister_chrdev
            * Log the successful unloading of the module
        Output:
            Unloads the module and frees the device buffer
        References:
            * kfree: https://www.kernel.org/doc/html/latest/core-api/memory-allocation.html
*/
static void __exit custom_module_exit(void) {
    // Free the allocated buffer
    kfree(device_buffer);
    // Unregister the character device
    unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
    // Log the successful unloading of the module
    printk(KERN_INFO "CSPB-3753 unloaded LKM\n");
}


// Register the module initialization and exit functions
module_init(custom_module_init);
module_exit(custom_module_exit);

// Module information
MODULE_LICENSE("GPL");  
MODULE_AUTHOR("Taylor Larrechea");  
MODULE_DESCRIPTION("CSPB-3753: LKM Programming Assignment");  
MODULE_VERSION("0.1");  