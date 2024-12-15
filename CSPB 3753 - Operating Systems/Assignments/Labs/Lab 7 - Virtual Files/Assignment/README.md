# CSPB-3753 Lab : `/proc` virtual files
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right" style="margin:10px">
</figure>
<br>
In Linux, the `/proc` directory is a virtual filesystem that provides an interface to kernel data structures and information about the system and its processes. The `/proc` directory does not contain actual files but rather dynamically generates information about the running kernel and system state when the file is accessed. The `/proc` directory is mounted during the boot process, and its contents are updated in real-time.

Here are some key aspects of the `/proc` directory:

1. **Process Information:** Each running process on the system is represented by a directory within `/proc` with a numerical name (e.g., `/proc/1234/` for process ID 1234). Inside these directories, you can find various files containing information about the respective process, such as `cmdline` (command line arguments), `status` (status information), `exe` (executable path), and `fd` (file descriptors).

2. **System Information:** The `/proc` directory also contains files that provide information about the system as a whole. For example:
   - `/proc/cpuinfo`: Information about the CPU(s) in the system.
   - `/proc/meminfo`: Information about memory usage.
   - `/proc/version`: Kernel version information.
<br><br>
3. **Kernel Parameters:** Some files in `/proc` allow you to view and modify kernel parameters dynamically. For example:
   - `/proc/sys/kernel/`: Contains various kernel-related parameters that you can read or modify.
<br><br>
4. **Network Information:** Network-related information, such as the status of network interfaces, can be found in the `/proc/net/` directory.

While you can read information from many files in `/proc`, attempting to write to certain files can have a direct impact on the system's behavior. Therefore, extreme caution should be exercised, and changes should be made carefully, as inappropriate modifications can lead to system instability.

	
<hr>
	 
<img src="images/construction-set-icon.jpg" alt="Under Construction" WIDTH=120 ALIGN="left" />

### This lab is still under construction.  
 
 Please report all speeling and grammered issues.<br>
 Also let us know about any unclear descriptions of work to be performed. 
 <br><br><br>
<hr>

**Objectives**

* *Understanding System Internals:* - Gain insight into the inner workings of the operating system by exploring the `/proc` filesystem, which provides a virtual interface to kernel data structures.

* *Process Management:* - Learn about process management by navigating through `/proc/<PID>` directories and extracting information about running processes.

* *System Monitoring and Troubleshooting:* - Develop skills for monitoring system health and diagnosing issues by examining files in `/proc` related to memory usage, CPU information, and network statistics.

* *Kernel Parameter Configuration:* - Explore the configuration of kernel parameters through `/proc/sys` and understand how modifying these parameters can impact system behavior.

* *Documentation Reading:* - Encourage students to refer to Linux kernel documentation (e.g., [`https://www.kernel.org/doc/Documentation/filesystems/proc.txt`](`https://www.kernel.org/doc/Documentation/filesystems/proc.txt`) ) to understand the purpose and structure of `/proc` entries.

* *Research Skills:*  - Foster research skills by requiring students to investigate specific `/proc` entries, understand their significance, and present findings.

This assignment of the `/proc` filesystem will provide hands-on experience with system administration tasks, increase the understanding of operating system internals, and enhance problem-solving skills in the context of Unix-like systems. 
<hr>
    
In Unix-like operating systems, virtual devices refer to devices that are not physical hardware components but are instead implemented in software to provide specific functionality. These devices are often represented as files in the file system and are accessed through standard file I/O operations. 
	
Here are a few examples of Unix virtual devices:

* /dev/null: This device discards any data written to it and returns an end-of-file (EOF) when read. It is often used to eliminate unwanted output. The command ` my_app > /dev/null` will redirect all the output from an application to that device.

* /dev/zero: Reading from this device produces an endless stream of null bytes (zeros), while writing to it discards the data. It is frequently used for creating empty files or initializing storage.

* /dev/random and /dev/urandom: These devices provide access to the kernel's random number generator. /dev/random provides high-quality random numbers, but it may block if the system's entropy pool is low. /dev/urandom is similar but does not block; it will generate less-secure random numbers if the entropy pool is depleted.

* /dev/stdin, /dev/stdout, and /dev/stderr: These are file descriptors representing standard input, standard output, and standard error, respectively. They allow redirection of input and output streams.

```
$ ls -l /dev/*random /dev/z* /dev/null
crw-rw-rw- 1 root root 1, 3 Feb  6 20:31 /dev/null
crw-rw-rw- 1 root root 1, 8 Feb  6 20:31 /dev/random
crw-rw-rw- 1 root root 1, 9 Feb  6 20:31 /dev/urandom
crw-rw-rw- 1 root root 1, 5 Feb  6 20:31 /dev/zero
```
These virtual devices play a crucial role in the Unix philosophy of treating everything as a file, making it easier for programs to interact with various resources using standard I/O operations.  Notice that the listing above has the `c` character listed for the file type indicating that it is a character device.  The `stdin`, `stdout`, and `stderr` devices are links to files in the `/proc` directory.

```
$ ls -l dev/std*
lrwxrwxrwx 1 root root 15 Feb  6 20:31 /dev/stderr -> /proc/self/fd/2
lrwxrwxrwx 1 root root 15 Feb  6 20:31 /dev/stdin -> /proc/self/fd/0
lrwxrwxrwx 1 root root 15 Feb  6 20:31 /dev/stdout -> /proc/self/fd/1
```
    
<hr>    
In Unix-like operating systems, the `/proc` directory is a *virtual filesystem* that provides an interface to kernel data structures and system information. The files and subdirectories under `/proc` allow users and processes to access and manipulate information about the running kernel, processes, and other system-related details. The `/proc` filesystem is dynamic, meaning that the information it exposes reflects the current state of the system.

Here are some common types of information available in the `/proc` directory:

1. **/proc/cpuinfo:** Contains information about the system's CPU, including its architecture, model, and features.

2. **/proc/meminfo:** Provides information about the system's memory usage, including total, free, and used memory.

3. **/proc/version:** Displays the kernel version, compiler version, and other information about the running kernel.

4. **/proc/cmdline:** Shows the command-line parameters passed to the kernel during boot.

5. **/proc/sys:** Is a directory containing various directories and files that display system-related parameters.  These parameters can be read or modified to configure kernel settings. For example, `/proc/sys/kernel/hostname` displays the current host name for the kernel.

6. **/proc/<PID>:** There is a subdirectory for each running process, identified by its process ID (PID). Inside this directory, you can find information about the process, such as its status, command line, and memory maps.

7. **/proc/net:** Contains information about network-related parameters and statistics, such as `/proc/net/tcp` and `/proc/net/udp`.

8. **/proc/fs:** Contains information about filesystems mounted on the system.

Keep in mind that the files and directories in `/proc` are not actual physical files on disk; they are interfaces to kernel data structures and are generated dynamically. Reading from or writing to these files allows users and processes to interact with and obtain information about the system. The information provided by `/proc` is invaluable for system administrators, developers, and tools that need insights into the system's current state and configuration.    
<hr>

### Create C programs to extract information from `/proc` files
	
In this lab, you will explore the `/proc` file system in linux. The `/proc` file system provides
a means to get and set various information about the kernel and about particular processes.
Remember that the `/proc` file system is an example of a virtual file system whose contents are not
actually stored anywhere but are computed on demand according to user file I/O requests.
    
    
Write a C program that will read the appropriate `/proc` file and extract the following:
1. The number of CPUs in your machine and their clock speed, number of cores.
2. The version of Linux kernel running on your system
3. The time in day:hr:min:sec when the system was last booted
4. The average load on the system in the last 15 minutes
5. The total usable and currently free memory in the system
6. The total swap space and the currently used swap space in the system
7. The swap partitions and their sizes
8. The time the CPU spent (over all processes) in the user mode and kernel mode
9. The number of context switches made by the system so far

Write a second C program that gets the following information specific to a process (given by PID):
1. The time spent by the process in running and in waiting
2. The time spent by the process in the user mode, kernel mode
3. The environment of the process
4. The contents of the address space of the process
    

<hr>

### Hints: getting info from '/proc' does not always have field explainations
The `/proc/[pid]/stat` file provides various pieces of information about a specific process with a given process ID (PID) in a Linux system. The file contains a single line of space-separated values, representing different fields. 
```
$ sudo cat  /proc/2885/stat
2885 (bash) S 2661 2885 2885 34816 4782 4194304 5072 33762 5 288 5 7 35 48 20 0 1 0 3069 11812864 1344 18446744073709551615 94726950334464 94726951247629 140723948417584 0 0 0 65536 3686404 1266761467 1 0 0 17 1 0 0 0 0 0 94726951492272 94726951540304 94726971125760 140723948419787 140723948419792 140723948419792 140723948421102 0
```
Lots of numbers, but what does it all mean?  You need to search for documentation (internet search) on each of the virtual commands.  The format of the output for this request is as follows:

```
pid (comm) state ppid pgrp session tty_nr tpgid flags minflt cminflt majflt cmajflt utime stime cutime cstime priority nice num_threads itrealvalue starttime vsize rss rsslim startcode endcode startstack kstkesp kstkeip signal blocked sigignore sigcatch wchan nswap cnswap exit_signal processor rt_priority policy delayacct_blkio_ticks guest_time cguest_time start_data end_data start_brk arg_start arg_end env_start env_end exit_code
```
Here's a breakdown of some key fields in the `/proc/[pid]/stat` file:

1. **pid:** Process ID.
2. **comm:** Command name or command-line arguments (wrapped in parentheses).
3. **state:** Process state (e.g., 'R' for running, 'S' for sleeping, 'Z' for zombies).
4. **ppid:** Parent process ID.
5. **pgrp:** Process group ID.
6. **session:** Session ID.
7. **tty_nr:** Controlling terminal number.
8. **tpgid:** ID of the foreground process group in the controlling terminal.
9. **flags:** Process flags.
10. **utime:** User-mode CPU time (in clock ticks).
11. **stime:** Kernel-mode CPU time (in clock ticks).
12. **cutime:** User-mode CPU time of dead children (summed).
13. **cstime:** Kernel-mode CPU time of dead children (summed).
14. **priority:** Priority value (not the nice value).
15. **nice:** Nice value (user-defined priority).
16. **num_threads:** Number of threads in the process.
17. **starttime:** Time the process started (in clock ticks).
18. **vsize:** Virtual memory size in kilobytes (KB).
19. **rss:** Resident Set Size (in pages).
20. **rsslim:** Current limit in bytes on the rss.
21. **signal:** Bitmap of pending signals.
22. **blocked:** Bitmap of blocked signals.
23. **sigignore:** Bitmap of ignored signals.
24. **sigcatch:** Bitmap of caught signals.
25. **wchan:** Address of the kernel function where the process is sleeping.
26. **nswap:** Number of pages swapped.
27. **cnswap:** Cumulative nswap for child processes.
28. **exit_signal:** Signal to be sent to the parent when the process dies.
29. **processor:** CPU number last executed on.
30. **rt_priority:** Real-time scheduling priority.
31. **policy:** Scheduling policy (e.g., SCHED_OTHER, SCHED_FIFO, SCHED_RR).
32. **delayacct_blkio_ticks:** Aggregated block I/O delays.
33. **guest_time:** Guest time of the process in clock ticks.
34. **cguest_time:** Guest time of dead children in clock ticks.
35. **start_data:** Address above which program data (initialized and uninitialized) is placed.
36. **end_data:** Address below which program data (initialized and uninitialized) is placed.
37. **start_brk:** Address above which the program heap can be expanded with `brk()`.
38. **arg_start:** Address above which the `argv` strings are placed.
39. **arg_end:** Address below which the `argv` strings are placed.
40. **env_start:** Address above which the environment strings are placed.
41. **env_end:** Address below which the environment strings are placed.
42. **exit_code:** The value returned by the process in its exit() system call.

Keep in mind that the values are in different units (e.g., time in clock ticks, memory sizes in kilobytes). To interpret these values, you may need to refer to the documentation or source code for more details about the specific units and meanings of each field. The values in this file are generally useful for monitoring and analyzing the behavior of a running process.

<hr>
	
### Submission
***Make sure to `commit` to your local repository and `push` to the remote repository.*** 
Grading of your work will be based on the information that you have in your remote repository.

<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" style="margin-right:20px" />

* C code to extract system data
* C code to extract process data
* `Makefile` to build and test your code

Although the grading of your lab will be done by accessing your <br> remote repository,
you must submit the following to Moodle Assignment:

* Your name:
* CU ID: (4 letters - 4 digits)
* GitHub Username:
* hours to complete lab:

<hr><hr><hr>