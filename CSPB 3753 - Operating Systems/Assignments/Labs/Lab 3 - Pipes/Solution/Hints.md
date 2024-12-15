## Linux Processes
### CSCI 3753: Operating Systems

### 1. Process Creation
A new process can be created from inside a C/C++ program by using the fork()
system call. The process that calls fork() is called the parent process, and the newly 
created process is called the child process. After the call, the parent process and the 
child process run concurrently. 
```
	#include <sys/types.h> 
	#include <unistd.h> 
	pid_t pid;
	pid = fork(); 
```
The child process is an exact copy of the parent process, except for the following: 
* The child process has a unique process id (PID). 
* The child process has a different process id of its creator (PPID).

The fork is called by the parent process, but returns in both the parent and the child
processes. In the parent process, the return value is the process id of the child 
process, whereas in the child process, the return value is 0. If fork fails, no child 
process is created and -1 is returned in the process calling fork.

```
	pid t pid;
	if ((pid = fork()) == -1) exit(1); /* FORK FAILED */
	if (pid == 0) {
		/*put code for child process here*/
		printf(”CHILD: I am the child process.\n”);
		printf(“CHILD: My process id = %d\n”, getpid());
		printf(“CHILD: My parent’s process id = %d\n”, getppid());
		exit(0);
	}
	/*put code for parent process here*/
	printf(”PARENT: I am the parent process.\n”);
	printf(”PARENT: My child process id = %d\n”, pid);
	printf(”PARENT: My process id = %d\n”, getpid());
```

### 2. Process Execution Image
The child process is not restricted to executing a subset of the statements in the 
parent process. It can also execute another program by overlaying itself with an 
executable file. The target executable file is read in on top of the address space of the 
very process that is executing, overwriting it in memory, and execution continues at 
the entry point defined in the file. The result is that the child process begins to 
execute a new program, under the same execution environment as the old program, 
which is now replaced.

The program overlay can be done by any of the several versions of exec system calls, 
including `execl`, `execv`, and `execve`. These calls differ from one another in the type 
and number of arguments they take. Read the man page of exec for details. 
```
	pid t pid;
	if ((pid = fork()) == -1) exit(1); /* FORK FAILED */
	if (pid == 0) {
		/* Child process will execute the executable code in the file a.out */ 
		execl(”a.out”, NULL);
		exit(0);
	}
	/*put code for parent process here*/
```

### 3. Synchronization between Parent and Child Processes
After creating a child process, the parent and the child processes run independently 
of one another. At any point during execution, the parent process can elect to wait 
for the child process to terminate, by using the `wait` system call, before proceeding 
further. 
```
	#include <sys/types.h>
	#include <sys/wait.h>
	int pid = wait(union wait *status) 
```
The `wait` system call searches for a terminated child of the calling process. 
1. If there are no child processes, wait returns immediately with value -1. 
2. If one or more child processes have terminated already, wait selects an 
arbitrary terminated child, stores its exit status in the variable status, and 
returns its process id. 
3. Otherwise, wait blocks until one of the child processes terminates and then 
goes to step 2. 

### 4. Process Termination
Every running process eventually terminates.
1. The process runs to completion and the function main returns. 
2. The process calls the library routine exit, or the system call exit. 
3. The process encounters an execution error or receives an interrupt signal, 
causing its premature termination.

The argument to `exit()` system call is part of the termination status of the process. 
Conventionally, a zero argument indicates normal termination and a non-zero 
argument indicates abnormal termination. 

### 5. Redirecting STDOUT to a file
There are the standard file descriptors for every process: `stdin`, `stdout`, and `stderr`.  These file descriptors are used for reading from the current input or writing to the output or error streams.  Sometimes we want to redirect the input to come from a different file descriptor or redirect the output to another file descriptor.   The file descriptor could be to a file on disk, which can be obtained from the `open()` system call.  You can now use that file descriptor explicitly to read or write to the file.
See the `fprintf` or `fscanf` library calls to read and write to a file descriptor.  

There are times when a file descriptor should take the place of another file descriptor.  Such as when the input or output is being redirected. There is a `dup()` system call that will duplicate an open file descriptor and can be used to create a clone descriptor.
To replace a currently open file descriptor, the current file descriptor needs to be closed and then that file descriptor is set to a new stream by either `open()` or `dup()`.
However, the two system calls `close()` and `dup()` being used in sequence would allow for a possible race condition.  If there was an asynchronous event between the first and second system call, the event could cause a system fault.

Luckily there is a system call that will combine the two calls into an atomic operation.  The `dup2()` system call will both clone the new file descriptor and close the currently open destination file descriptor.
See the documentation for the `dup2()` system call (you can check out the man page and/or read about it at the end of Chapter 3 in our textbook).


Here's a brief description:

```	
	int dup2(int oldfd, int newfd);
		oldfd: old file descriptor whose copy is to be created.
		newfd: new file descriptor which is used by dup2() to make the copy.
		result: makes newfd be the copy of oldfd, closing newfd first if necessary.
```

Below is an example of redirecting the `stdout` file descriptor to be a disk file instead of printing to the terminal.  Note that if we pass a file descriptor that's already bound (`stdout`) as `newfd`, then `dup2()` will close the current descriptor and then override it with a clone of the old descriptor.

```
	#include<stdlib.h> 
	#include<unistd.h> 
	#include<stdio.h> 
	#include<fcntl.h> 
	
	int main() 
	{ 
	  // do not confuse open() with fopen(): open() is a syscall
	  // that returns a file descriptor, not a FILE data structure.
	  int fd = open("redirected.txt",O_WRONLY); 
	
	  // here the newfd is the file descriptor of stdout (i.e. 1) 
	  dup2(fd, 1) ;  
	
	  printf("I will be written to redirected.txt"); 
	  
	  // must always close any opened descriptor
	  // the system will take care of closing stdio descriptors
	  close(fd);  
	  
	  return 0;
	  
	  // We aren't doing any error handling in this example code.
	  // Very, VERY Sad! 
	} 
```
In the example code, the `printf` call will send the character to the `stdout` descriptor.  When it has been redirected, the `printf` will write to the disk file.

### 6. Using Pipes to Redirect input and output
When you call the `pipe(pipe_fd)` system call, it returns two file descriptors.
One descriptor `pipe_fd[0]` is the read descriptor for the pipe.  
The other file descriptor (`pipe_fd[1]`) is for the write descriptor for the pipe.

```
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	int main() {
		int pipe_fd[2];
		pid_t child_pid;

		// Create a pipe
		if (pipe(pipe_fd) == -1) {
			perror("pipe create");
			exit(EXIT_FAILURE);
		}

		// Fork a child process
		if ((child_pid = fork()) == -1) {
			perror("fork failed");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0) {
			// Child process
			// Close write end of the pipe
			// Redirect stdin to read from the pipe
			// Close the read end of the pipe
			. . .

			// start another command
			. . .

		} else {
			// Parent process
			// Close read end of the pipe
			// Redirect stdout to write to the pipe
			// Close the write end of the pipe
			. . .


			// Write data to the pipe (e.g., "Hello, World!\n")
			printf("Hello, World!\n");

			// Wait for the child process to finish
			wait(NULL);
		}

		return 0;
	}
```


### 7. Process Suspension
Most programs are written to execute as fast as possible.  But there are times we would like a process to stay around awhile.  Execution of a process may be suspended for some interval of time using the `sleep()` function or the `sleep` bash command if running a shell script.
```
#include <unistd.h> unsigned seconds;
unsigned r = sleep(seconds);
```

### 8. Some Useful Commands for Process Management
The OS knows about all the processes running on a system.  There are commands that can be used to access that information and print it to the terminal.  

`ps` : The `ps` command displays information about the existing processes 
in the system. This command has several command-line arguments.
Access the man page for more details. 

`kill <pid>` : This command sends a signal to a process whose 
process id is `<pid>`.
The `kill` command is used to terminate an existing process.
Useful when a process is in an infinite loop or is a zombie.
