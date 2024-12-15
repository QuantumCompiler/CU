# CSPB-3753 Assignment: Extending a Simple Character Device LKM
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>

[VM Access Link](https://cs-vsphere.int.colorado.edu/)

Sensors have become ubiquitous in modern technology, cover a wide range of technologies, and have become an integral part of our daily lives. Sensors are commonly used in various electronic devices to gather information from the physical world, such as temperature, light, motion, or proximity.
The advancements in sensor technology, along with reductions in size and cost, have contributed to their widespread adoption.  The ubiquity of sensors is driven by their ability to provide valuable data for decision-making, automation, and enhancing user experiences across a diverse range of industries and applications. As technology continues to advance, it's likely that sensors will become even more pervasive in our surroundings.

To integrate these sensors with computers, you must create a sensor device driver that allows the operating system to communicate with and control a specific sensor hardware device.  The driver acts as an interface between the sensor hardware and the operating system, enabling the OS to interact with and make use of the sensor's data.

Your task is to implement a LKM device driver for a simple character device that supports reading, writing, and seeking. This assignment assumes you have completed the simple LKM lab. You are advised to complete the simple LKM lab before beginning this assignment.   Although your device driver will not collect actual data, it will dynamically allocate a memory buffer and manage the data within that buffer.

Your LKM  will support reading from beginning of the buffer to the end of the buffer.  You will need to validate the read and write requests to not allow reading/writing outside of the buffer.   You will support the seek function to modify the current file position from which the next read or write will occur.  Your LKM must transfer data from user space into kernel space and from kernel space into user space.  This requires specific system calls to transfer the data.
<br><br>
#### **Objectives**

* add new functionality to a kernel.
* create a working protoype of a character device driver.
* use the tools for building and loading/unloading the LKM.
* maintain the file position correctly for reads, writes, and seeks.
* debug LKM using system log messages
<hr>


    
<img src="images/construction-set-icon.jpg" alt="Under Construction" WIDTH=120 ALIGN="left" style="margin-right:10px" />

### This lab is still under construction.  
 
 Please report all speeling and grammered issues.<br>
 Also let us know about any unclear descriptions of work to be performed. 
 <br><br><br>
<hr>

## Creating Your Own Device Driver

In the previous LKM lab you created a source file that had the initialization and termination of the LKM module for loading and unloading the LKM to/from the kernel.  You used the `printk()` function to write information to the system log.  You were able to compile the LKM into a `.ko` file and load that LKM into the kernel, seeing that the log messages were written.  You also dynamically created a memory buffer from the kernel with `kmalloc to hold data and released that memory on termination.

Much of the kernel is isolated into the base kernel, which has been compiled together from the Linux source.  Because you are a superuser for your virtual machines, you can create your own kernels and add new systems calls that user programs could access.  Once you add the code, you must recompile and link the new kernel into an executable.  Then you set up the boot loader to make your new kernel available to be booted.  

The Linux kernel provides a standardized interface for device drivers through a set of well-defined structures, functions, and mechanisms. Some of the common device driver types include:

* Character Device Interface: <br>
The character device interface is used for devices that are accessed as a stream of characters, such as terminals or serial ports. The main structures include struct file_operations and struct cdev, which define the operations supported by the character device driver.

* Block Device Interface: <br>
The block device interface is designed for devices that store data in fixed-size blocks, such as hard drives or SSDs. Key structures include struct block_device_operations and struct gendisk.

* Network Device Interface: <br>The network device interface is used for network-related device drivers. Key structures include struct net_device and struct net_device_ops.

For this assignment, you will be creating a character device which is accessed as a stream of data.  The interface is similar to the interface for interacting with a file of data. The interface defines functions for open, close, read, write, and seek among the functions used for managing the device. 

There is a tendency to think of LKMs like user space programs. 
Modules do share a lot of user space program properties, but LKMs are definitely not user space programs. LKMs (when loaded) are very much part of the kernel. As such, they have free run of the system and can easily crash it.  There are specific functions to move data between the user space and the kernel space.  Memory over runs (or under runs)  that unintentionally access memory within the kernel is a well known area for hacker access to data.  Be careful with your LKM code to only access memory that is associated with the device.
<hr>

### Extending your Source Code for a New Device Driver

Using your previous lab's code for a LKM, extend the functionality to include support for open/close and read/write/seek functions.   You will first need to define an interface data structure to map the functions in your code to the operations in the interface.  The names of the functions in your code do not matter as you specify the function to be called for each operation.  This data structure is creating a jump table, which is a common data structure in the kernel.


Below is the full definition of the somewhat involved `file_operations` struct:
```
struct file_operations {
       struct module* owner;
       loff_t (*llseek) (struct file* , loff_t, int);
       ssize_t (*read) (struct file* , char* , size_t, loff_t* );
       ssize_t (*write) (struct file* , const char* , size_t, loff_t* );
       int (*readdir) (struct file* , void* , filldir_t);
       unsigned int (* poll) (struct file* , struct poll_table_struct* );
       int (*ioctl) (struct inode* , struct file* , unsigned int, unsigned long);
       int (*mmap) (struct file* , struct vm_area_struct* );
       int (*open) (struct inode* , struct file* );
       int (*flush) (struct file* );
       int (*release) (struct inode* , struct file* );
       int (*fsync) (struct file* , struct dentry * , int datasync);
       int (*fasync) (int, struct file* , int);
       int (*lock) (struct file* , int, struct file_lock* );
       ssize_t (*readv) (struct file* , const struct iovec* , unsigned long, loff_t* );
       ssize_t (*writev) (struct file* , const struct iovec* , unsigned long, loff_t* );
    };  
```
Except for its first member, all of the structure members are pointers to functions.  Each of these members supports some file operation functionality, and it is your responsibility to provide implementations of these operations.
If you do not provide an implementation of any one of these functions, then the corresponding member is set to NULL by default, then the system will take care of the implementation of the function to give it some default functionality.  For this assignment, you won't provide implementations for the majority of these members.

You might have also noticed the `_t` suffix naming convention.  This suffix stands for "type" and it is a C way of making the results span across machine types.  Different machines have different sizes of memory for the standard `int` and the code may need to abstract how to define the data.  The types are set by a `define` in the kernel code.  For example, an implementation of `read` should return a value of "signed size type": if the return value is positive it's a valid size, otherwise it signals an error.

You will only be defining functions for the `read, write, llseek, open, and release` operations.  These are lowest level functions of file operations that are performed by user space processes on files.  They correspond to the `fread, fwrite, fseek, fopen, and fclose` functions that are given a file descriptor.

The following code will setup a file operations data structure and specify the function to call for the read operation.  This code specifies that the `myread(...)` function is to be called.  Each operation requires a function with the correct parameters and return type for the operation.

```
// recall that '.' is the member access operator in C
static struct file_operations simple_driver_fops =
{
    .owner   = THIS_MODULE,
    .read    = my_read,
};
```
The declaration of the `THIS_MODULE` macro is contained in the `linux/module.h` header file. 
The definition of the read function can be seen above in the full operations listing.  The prototype definition for `myread` would be as follows:
```
 ssize_t my_read (struct file* , char* , size_t, loff_t* );
```

Here is a break down the parameters of the `read` function:

```
struct file *filp:
```

* Pointer to the file structure associated with the file being read. The file structure (struct file) holds information about the opened file, including the file position, file status flags, and a reference to the corresponding struct inode structure.  This is the data structure referenced by a file descriptor.

```
char __user *buf:
```
* A user-space buffer where the data read from the device buffer will be placed. The __user annotation indicates that this pointer is in user space, and the kernel must use appropriate mechanisms (such as `copy_to_user()` ) to access or modify its contents.

```
size_t count:
```
* The count parameter specifies the number of bytes to read from the device buffer into the user-space buffer (buf parameter). The function is expected to read up to count bytes of data from the device.  However this value is mediated by the actual length of the device buffer.

```
loff_t *f_pos:
```
* This is probably the most important parameter to study.  The parameter is a pointer to the file position or offset within the data. *Let me repeat that: It is a pointer to a type of integer which holds the current offset within the data.* The value represents the current position for reading and is updated to where the next read will occur after this read operation.  The device driver is responsible for updating the position to reflect the new position in the data. The `loff_t` data type is used to handle large file offsets using a large integer dat type.
<br><br>
The read function returns a `ssize_t` value, which represents the number of bytes read. The return value can be one of the following:

   * A positive value: The number of bytes successfully read from the file.
   * 0: Indicates the end of the file (EOF) has been reached.
   * A negative value: An error code, indicating that an error occurred during the read operation.

Here's a simplified example of a read function implementation in a file operations structure:

```
#include <linux/fs.h>
#include <linux/uaccess.h>

ssize_t my_read_function(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    // Implementation of the read function
    // ...

    *f_pos += bytes_read;   update the value of the offset

    return bytes_read; // Number of bytes read, or an error code
}
```
In the implementation, the actual reading (transfer) of data and updating the file position would take place. Additionally, care must be taken to handle errors and use appropriate kernel functions to interact with user space, such as `copy_to_user()`.  You must also take care to limit the bytes transferred when the request would extend past the allocated memory in the device driver.

### HINT: below is mock read function
You can test if your device driver is working before you write the real code.  You must handle transferring some data and indicating EOF.   The code below will xfer bytes into user space and update the offset allow EOF to be returned on second read.

```
// Mock read to use for testing before writing actual read code
    if  (*f_pos > 0) return 0;
    
	put_user('K', buff++);
	put_user('N', buff++);
	put_user('O', buff++);
	put_user('X', buff++);
	put_user(0, buff++);
	*f_pos += 5;
	
    return 5;
}
```

<hr>

### How to activate the LKMs read operation
You have seen the initialization and termination code run and you have printed log messages.
How can you get the device to read?  You must create a new device that is specific to your driver.

Take a look at all the devices in the `/dev` directory.  Below you will see the end of the list of devices in that directory.  The first character of each line tells you what type of file this is.  The 'd' indicates a directory, a 'b' would indicate a block device, and `c` specifies the file is a character device.  The number following the `tty` or `root` indicates a device number.

```
... 
crw-rw----   1 root    tty       7,  69 Feb  5 18:17 vcsu5
crw-rw----   1 root    tty       7,  70 Feb  5 18:17 vcsu6
drwxr-xr-x   2 root    root          60 Feb  5 18:17 vfio/
crw-------   1 root    root     10, 122 Feb  5 18:17 vmci
crw-rw-rw-   1 root    root     10, 121 Feb  5 18:17 vsock
crw-rw-rw-   1 root    root      1,   5 Feb  5 18:17 zero
crw-------   1 root    root     10, 249 Feb  5 18:17 zfs
```
You will need to create a new device with a new device number in the `/dev` directory.  Your LKM code will register itself to be the device handler for that specific device number.   
The register code can be added to the initialization code.  Below is an example of the code needed for the registering of device handler.  The register is telling the kernel the device number 375 is associated with `/dev/knox375` and a pointer to the LKM's `simple_driver_fpos` data structure.

```
	printk(KERN_ALERT "KNOX %s function\n",__FUNCTION__);
	int ret = register_chrdev (375, "knox375", &simple_driver_fops); 
	printk(KERN_ALERT "KNOX %s : register_chrdev ==> %d\n",__FUNCTION__, ret);  
```
On exit, the module needs to remove the handler by unregistering the LKM.
```
	unregister_chrdev(375, "knox375");
	printk(KERN_ALERT "KNOX %s : unregister_chrdev\n",__FUNCTION__);  
```
<hr>

## Creating a Virtual File for Your  Device

Each device will have a corresponding device file that is located in the `/dev` directory. If you list the files in that directory you will see all the devices currently known by the kernel. These are not regular files, they are <i>virtual files</i> that only supply data from or give data to the device. There is not any physical storage on the disk for these devices like the regular files that are used to store persistent data. The device driver code is responsible for creating a mechanism to store all the information while it is active.

To add a new device you need to create a new entry in the `/dev` directory. Each virtual file has information associated with it to tell the kernel which device driver to use when accessing the device. Recall that in Linux, each device driver is given a device {major number} to uniquely identify it.

You can create a new virtual device file to be associated with your device driver. First, we'll find an unused major number for your kernel, then we'll use the `mknod` command to create a new device entry and associate the new major number for your device driver. 
```
sudo mknod  <location> <type of driver> <major number> <minor number>
```
The major number should be unique and you can look at current devices already installed, but usually user modules start at 240.  The <i>minor number</i> can be 0. The type of your driver should be `c` for character. Note that more sophisticated drivers must deal with blocks of arbitrary data, in which case the type is `b` (see `man mknod` for more details).  Putting it all together, run the following command:
```
sudo mknod /dev/simple_character_device c 375 0
```
Note that `simple_character_device` is a file and can change its permissions using `chmod`.  To be sure that you can read, write, and execute this file, run the following command to allow everyone to access the device:
```
sudo chmod 777 /dev/simple_character_device
```
You will  need to create the device in the `/dev` directory.  This is a special file and you need to to use the `mknod` command as superuser.  The following command will create a new device file in the `/dev` with the name given.  The parameters are `c` for a character device, `375` is the device major number and `0` is the device minor number.
```
	sudo mknod /dev/knox375 c 375 0
```
you will see the device in the `/dev` directory.
```
crw-r--r-- 1 root root 375,  0 Feb  5 19:19 /dev/knox375
```
<hr>

#### Accessing the device from a user space process
The easiest way to access the device would be to use `cat` to access the data.  The cat program will open the filename given, read data copy it to the screen until EOF is returned, and finally close the file.  The command below will access the LKM (if it is installed and has registered the device) and read the data (see the mock read function).  Notice that the 4 characters are copied to the output, but there was not a newline in those 4 characters so the prompt immediately follows the output.

```
$cat /dev/knox375
KNOX$ 
```
<hr>

###  Complete the `read, write, lseek` Operations
Create functions for each of the operations and be sure to use and maintain the file position offset.   You will need to update the file operations data structure to have the functions associated with the operation.

<hr>

## Hints for Implementing Your Character Device Driver

Your main task is to give an implementation of five functions: `read`, `write`, `llseek`, `open`, `release`. You must name your functions:

The close functionality is handled by `release`. Since you are developing a very simple character device driver, many of the arguments to these functions that you need to implement will not be used.  Along these lines, do not overthink the `open` and `release` functions -- their implementations should be trivial. The nontrivial programming component of this assignment is the implementation of the following functions.

### `read` and `write`

- The read and write methods both perform a similar task, that is, copying data from and to application code. Therefore, their prototypes are pretty similar, and it’s worth introducing them at the same time:
```
ssize_t read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
ssize_t write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);
```
For both methods, `filp` is the file pointer and `count` is the size of the requested data transfer. The `buff` argument points to the user buffer holding the data to be written or the empty buffer where the newly read data should be placed. Finally, `offp` is a pointer to a "long offset type" object that indicates the file position the user is accessing. The return value is a "signed size type"; its use is discussed later. Let us repeat that the `buff` argument to the read and write methods is a <i>user space pointer</i>; therefore, it cannot be directly dereferenced by kernel code. Note that if the user attempts to write beyond the buffer, then you should write as many bytes to the buffer as possible, disregarding the remainder.

The return value for `read` is interpreted by the calling application program as follows:
- If the value equals the `count` argument passed to the read system call, the requested number of bytes has been transferred. This is the optimal case.
- If the value is positive, but smaller than `count`, only part of the data has been transferred. This may happen for a number of reasons, depending on the device. Most often, the application program retries the read. For instance, if you read using the `fread` function, the library function reissues the system call until completion of the requested data transfer. You can also see this behavior when you do a `strace` of `cat`.
- If the value is 0 , end-of-file was reached (and no data was read).
- A negative value means there was an error. The value specifies what the error was, according to `<linux/errno.h>`. Typical values returned on error include `-EINTR` (interrupted system call) or `-EFAULT` (bad address). For your LKM, the latter should be returned if any of the system calls invoked in `read` or `write` throws an error.

The return value for `write` is interpreted by the calling application program as follows:
- If the value equals `count`, the requested number of bytes has been transferred.
- If the value is positive, but smaller than `count`, only part of the data has been transferred. The program will most likely retry writing the rest of the data.
- If the value is 0, nothing was written. This result is not an error, and there is no reason to return an error code. Once again, the standard library retries the call to `write`. 
- A negative value means an error occurred; as for `read`, valid error values are those defined in `<linux/errno.h>`.
- If the buffer is filled and an attempt is made to write beyond the last position, then `write` must return -1 to indicate this error.

### `llseek`
The `llseek function` is called when one moves the cursor position within a file. The entry point of this method in user space is `lseek()`. One can refer to the `man` page in order to print the full description of either method from user space: `man llseek` and `man lseek`. Its prototype looks as follows:
```
loff_t(*llseek) (structfile *filp, loff_t offset, int whence);
```
- The return value is the new position in the file
- `loff_t` is an offset, relative to the current file position, which defines how much it will be changed
- `whence` defines where to seek from. In particular,
	- If `whence` is `SEEK_SET`, the cursor is set to `offset` bytes.
	- If `whence` is `SEEK_CUR`, the cursor is set to its current location plus `offset`.
	- If `whence` is `SEEK_END`, the cursor is set to the size of the file plus `offset`.
You must use these macros in your implementation. If adding the offset causes the cursor to become negative, then `-EINVAL` (invalid value) is returned, and the cursor remains unchanged.


### Hints

- If you are having trouble getting started, use `helloworld.c` as a starting point. 
- You will need to keep track of what header files are needed for implementing the five functions (these can be found by visiting their man pages). They will all be of the form `#include <linux/*.h>`.
- Remember that your module lives in <i>kernel space</i> but some arguments of the functions point to buffers in <i>user space</i>.

- The `loff_t` data type is a 64-bit value on all platforms
(`long long` in gcc terminology) so it can handle very large files. You should not use the value in the file object, but use the last argument in the call. The `read` and `write` operations should update the position using that pointer they receive as the last argument (instead of acting on `filp->f_pos` directly).  There are times that the kernel will pass a pointer to a different loff_t variable than the one in the file descriptor.  
- Since you are implementing `llseek`, you will need to keep track of the <i>present position</i> in the buffer for each open file descriptor. The `loff_t f_pos` field of the `file* filp` struct is used for keeping track of this information. It represents the current reading or writing position. 
The purpose of the `llseek` method is to change the file position, which is why it will be modifying `filp->f_pos` directly. This is illustrated in the figure below.
![Screen Shot 2021-08-20 at 9 49 40 PM](https://user-images.githubusercontent.com/5934852/130309813-f673eebd-68ff-47fe-af13-359f1abb3900.png)
 - For more info on the `file` struct, visit https://docs.huihoo.com/doxygen/linux/kernel/3.7/structfile.html (even though most fields will not be used for your assignment).

## Testing

- For testing your device driver, you should modify the `seek` lab code so you can monitor the content of your device driver's buffer from user space. It is possible for `read, write, and seek` to appear functional in your C test code, but not interface properly with unix system utilities such as `echo`, `tail`, `head`, and so on. This means your implementation is incorrect, so be sure that your code interfaces with these utilities. Recall that `strace` allows you to see how these utilities are interfacing with your device. 

- An easy way to test the `write` functionality of your device driver is to perform I/O redirection in the terminal as follows:
```
echo 'hello world' > /dev/simple_character_device
```
which will write "hello world" to your character device driver. 
- To test the reading of characters from your device, try using the `cat` command, which will `open`, `read` repeatedly until EOF is reached, and then `close` the file.
```
cat /dev/simple_character_device
```
- To partially test `llseek` functionality you may use the `tail` system utility , which will seek to the end of the file.  To thoroughly test `llseek` you will need to write your own test program in C by modifying the `seek` lab. Remember, your character device is a <i>file</i>, so you can use familiar file I/O operations (e.g., `fopen`, `fclose`, `fseek`, etc..) for creating your test program. You are free to consult your notes or online tutorials about file I/O in C.

<hr><hr><hr>

<img src="images/construction-set-icon.jpg" alt="Under Construction" WIDTH=120 ALIGN="left" style="margin-right:10px" />

### This lab is still under construction.  
 
 I have updated the documentation and grading criteria.<br>
 Please report all ambiguous and contradictory information.<br>
 Also let us know about any unclear descriptions of work to be performed. 
 <br><br><br>

<hr>

## Submission Instructions

You must follow these instructions below carefully.  I need to be able to test your solutions.  To make testing the same across solutions, the `Makefile` will hold the procedures for performing the common actions.  

- Remember to `push` your results to your remote repository.  
- The repository must contain a code directory that has the following: 
	- code for device driver
	- a `Makefile` that will complete common actions (you can modify the Makefile provided).
	- The `Makefile` must have the following targets that will be called:
	  - device - to make the device in the `/dev` directory  (`mknod` command)
	  - remove - to remove the device from `/dev` directory (`rm` command)
	  - load - to load your device driver (`insmod` command)
	  - unload - to unload your device driver (`rmmod` command)
	  - Default target should be to compile the `.ko` file for your driver.

To see the commands that would be performed by `make` for the default or for another target, use the `-n` option.  Below are the commands for the default target and the `load` target that would be performed by `make`.

```
$ make -n
make -C /lib/modules/6.5.0-15-generic/build M=/home/student/kernel/Assignment-LKM modules
$ make -n load
sudo insmod knox_module.ko
```
## Grading

Recall that points for your assignment are determined by code working correctly **and useful comments being place in the source**. There is also additional points that you will obtain for your code interview.  

There is a grading script that will run through the functionality of your device and determine the score.  The `test.py` script outputs an estimate on how many of the coding points you have earned.  You are encouraged to look at the grading script to understand how your solution will be evaluated. To ensure that you maximize your score on this assignment, you should write your assignment with respect to the following checkpoints.  Each checkpoint requires the previous checkpoints to have been completed.  You must have both read and write functional to have the seek checkpoint graded.
	
### Checkpoint 1  (15)

* Successfully install/uninstall device driver as LKM.   
   - `make` completes successfully and builds `.ko` file.
   - `make load` inserts the LKM into the kernel.
   - print message to syslog with "CSPB-3753" and "loaded LKM" in the log message.
   - `make unload` removes the LKM from the kernel.
   - print message to syslog with "CSPB-3753" and "unloaded LKM" in the log message.
   - useful comments being place in the source to show your understanding of the code.

### Checkpoint 2 (15)
* Successfully created device that is associated with your LKM.operations.  
   - `make device` creates virtual device.
   - create virtual device in `/dev` directory with correct permissions (rwx for all)
* Successfully register and unregister your device driver.
   - print message to syslog with "CSPB-3753" and "register returned = " in the log message.
   - print message to syslog with "CSPB-3753" and "unregister called" in the log message.
* Successfully add the `open` and `release` functions of the LKM. 
   - create data structure in the LKM for file operations.
   - associate your open and release functions to the associated file operation.    
   - print message to syslog with "CSPB-3753" and "opened device" in the log message.
   - print message to syslog with "CSPB-3753" and "released device" in the log message.
   - useful comments being place in the source to show your understanding of the code.

### Checkpoint 3 (25)
* Implement `write` functionality.  
   - print message to syslog with "CSPB-3753" and "writing %d characters" in the log message.
   - use and maintain current file position.
   - handle buffer overrun.
   - useful comments being place in the source to show your understanding of the code.

### Checkpoint 4 (25)
* Implement the `read` functionality required to support reading of data in the device buffer.
   - print message to syslog with "CSPB-3753" and "reading %d characters" in the log message.
   - use and maintain current file position.
   - handle buffer overrun.
   - useful comments being place in the source to show your understanding of the code.

### Checkpoint 5 (20)
* Implement `llseek` functionality. 
   - use and maintain current file position.
   - handle buffer overrun.
   - handle all three seek modes
   - useful comments being place in the source to show your understanding of the code.

## References

[1] Daniel Bovet and Marco Cesati. 2005. <i>Understanding The Linux Kernel</i>. Oreilly & Associates Inc.

[2] John Madieu. 2017. <i>Linux Device Drivers Development: Develop customized drivers for embedded Linux</i>. Packt Publishing.

