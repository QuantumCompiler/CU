# CSPB-3753 Lab: fork()
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>
<br>
Process management 
This lab will help you create multiple processes running different executables from a parent process and have the parent process report the return values from each child process.<br><br>

Process management is a fundamental aspect of operating systems that involves the creation, communication with, and termination of processes. A process is a program in execution, and process management is responsible for coordinating and controlling the execution of these processes. 

#### Process Creation:

The operating system creates a new process by duplicating an existing process. The new process, called the child process, inherits the code and data of the parent process.  The system call that will cause the kernel to create a new process is `fork()`.  Once the fork call has been completed, there will be two identical (except for the the process identifier) running. 

After forking a new process, the process may make a system call to replace its current program with a new one. This allows the process to evolve into a different program.  The `exec()` functions are designed to allow you to start the new executable program with a set of parameters.


#### Inter-Process communication (IPC)
Processes may need to communicate with each other, and process management provides mechanisms for inter-process communication (IPC), such as pipes, message queues, shared memory, and sockets.  We will explore these mechanisms in future labs.


#### Process Termination:
A process may voluntarily terminate itself, typically by calling an `exit()` system call.  The operating system may terminate a process in response to an error, violation of system policies, or completion of the process's task.
#### Process Identification:

Each process is assigned a unique process identifier (PID) for identification and management purposes.
Processes can be organized into a hierarchical structure, where a parent process may create one or more child processes.  Effective process management is crucial for ensuring the efficient and secure execution of programs on a computer system. Operating systems use process management to allocate resources, provide a responsive user experience, and maintain the integrity of the system.

#### **Objectives**

* review the system calls used for process management
* create new processes using `fork()`
* load new executable into a process using `exec()`
* receive notification of process termination using `wait()`
* provide a foundation for implementing the *Shell Programming Assignment*

<hr>


    
<img src="images/construction-set-icon.jpg" alt="Under Construction" WIDTH=120 ALIGN="left" />

### This lab is still under construction.  
 
 Please report all speeling and grammered issues.<br>
 Also let us know about any unclear descriptions of work to be performed. 
 <br><br><br>
<hr>    

### Lab Details
You will implement a new program (`lab2-3753.c`) written in C.  Using the parameters in `main(argc, argv)` you will create new processes to run the list of executables given in the command line.

For each of the command line arguments in `argv`, create a child process, have the child process execute the program listed in the argv string, and wait for termination of that child process.

<hr>

#### Step 1 - Process Creation
A new process can be created from inside a C/C++ program by using the `fork()`
system call. The process that calls `fork()` is called the *parent process*, and the newly
created process is called the *child process*. After the call, the parent process and the
child process run the same program code concurrently.

A simple example of code to create a new process:
```
#include <sys/types.h>
#include <unistd.h>

pid_t pid;
pid = fork();

// code following the fork() command
. . .
```

The child process is an exact copy of the parent process, except for the following:
* The child process has a unique process id (PID).
* The child process has a different process id of its creator (PPID).

The fork is called by the parent process, but the function will return in both the parent and the child processes. The statement following the call to `fork()` will be the next statement to be executed in each process. 
	
#### How to tell if the code is running in parent or child
Most of the time, you will want the parent and the child to execute different code.  The parent will continue with it's processing and the child will perform some new task.  So how do we know programmatically  when we are in the parent or the child?
In the parent process, the return value is the process id of the child
process, whereas in the child process, the return value is 0. If fork fails, no child
process is created and -1 is returned in the process calling fork.

You can see in the program listed below, we check for the return value of the `fork()` command.
If the value is `-1` then the child process was not created and we can print an error message and exit the parent process.
Otherwise the process was created and we need to check the return value received by the process.  The two processes will behave differently.  If the returned process identifier is `0`, then the process is the child and we will print some information and exit the child process.

In the case of the parent process, the `pid` will be greater than 0 and represent the processes identifier.  This is the same identifier that will be returned from the `getpid()` call in the child.
	The parent code is not placed in an `else` because the other path will result in the child's termination (`exit()`).

```
pid t pid;

if ((pid = fork()) == -1) {
	/* FORK FAILED */
	perror("fork failed");
	exit(1); 
}

if (pid == 0) {
	/*put code for child process here*/
	printf(”Child: I am the child process.\n”);
	printf(“Child: My process id = %d\n”, getpid());
	printf(“Child: My parent’s process id = %d\n”, getppid());
 exit(0);
}

/*put code for parent process here*/
printf(”I am the parent process.\n”);
printf(”Parent: process id = %d\n”, getpid());
...
```
<hr>

#### Step 2 - Process Execution Image
The child process is not restricted to executing a subset of the statements in the
parent process. It can also execute another program by overlaying itself with an
executable file. The target executable file is read in on top of the address space of the
very process that is executing, overwriting it in memory, and execution continues at
the entry point defined in the file. The result is that the child process begins to
execute a new program, under the same execution environment as the old program,
which is now replaced.

The program overlay can be done by any of the several versions of `exec` system calls,
including `execl`, `execv`, and `execve`. These calls differ from one another in the type
and number of arguments they take. Read the man page of `exec` for more details.

Modify the code in the child specific section to print the information and 
then start a new program in that process.
```
pid t pid;

if ((pid = fork()) == -1) {
	/* FORK FAILED */
	perror("fork failed");
	exit(1); 
}

if (pid == 0) {
	. . .  print process information . . .
	
	/* Child process will execute the executable code in the file /bin/ls */
	execl(”/bin/ls”, NULL);
	exit(0);
}

/*put code for parent process here*/
. . .
```
<hr>

#### Step 3 - 3. Synchronization between Parent and Child Processes
After creating a child process, the parent and the child processes run independently
of one another. At any point during execution, the parent process can elect to wait
for the child process to terminate, by using the `wait` system call, before proceeding
further.

```
#include <sys/types.h>
#include <sys/wait.h>

. . .

int child_pid = wait(union wait *status);
// check the return value of the system call
. . .
```

The `wait` system call searches for a terminated child of the calling process.
1. If there are no child processes, wait returns immediately with value -1.
2. If one or more child processes have terminated already, wait selects an
arbitrary terminated child, stores its exit status in the variable status, and
returns its process id.
3. Otherwise, wait blocks until one of the child processes terminates and then
goes to step 2. 

Modify the parent code to print the process information and wait for the child process to complete.

#### Process Termination
Every running process eventually terminates.
* The process runs to completion and the function main returns.
* The process calls the library routine exit, or the system call exit.
* The process encounters an execution error or receives an interrupt signal,
causing its premature termination.

The argument to `exit(...)` system call is part of the termination status for the process.
Conventionally, a zero argument indicates normal termination and a non-zero
argument indicates abnormal termination. Often you will define a set of exit codes 
that can be used to indicate where in the program the exit occurred.

Modify your code to use different values in each `exit` call to indicate where the exit occurred.
<hr>

#### Step 4 - Make your parent process the command line arguments in `argv`
Your code should now create a child process, run a different executable in that child, and the parent should wait for the child's termination.

The command line is parsed by the `bash` shell and passed to your program via the `argc, argv` parameters to the `main` function in C programs.  You should modify your code to iterate through
the command line arguments, create a new child and execute the command in the string of `argv`.
The parent should wait for each child to complete processing before continuing to process more of its program arguments.

The command below would have your program create a child and run the `/bin/ls` program, wait for its termination, then create another child to run the `/bin/ps` program and wait for its termination.

```
lab2-3753 /bin/ls /bin/ps
```


#### Some Useful Commands
To see what is actually running on your system, use the `ps` command.  
The `ps` command displays information about the existing processes in the
system. This command has several command-line arguments. Read the man page for
details.

Sometimes you will create processes and the parent process does not collect the termination information, or you end up with an infinite loop and the process does not terminate.  In these cases, the `ps` command will list the processes with their process identifier.  You can use this identifier to send signals to the process.  Only signal is the `SIG_KILL` signal that will cause the process to terminate.  Use the `kill(...)` system command to pass the correct signal to the process.
<hr>

***Make sure to `commit` to your local repository and `push` to the remote repository.***    
Grading of your work will be based on the information that you have in your remote repository.

Your code should include:
* code to handle parent processing
* code to handle child processing
* processing return codes of all system calls
* code that is well commented


<br><br>
<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" />
Your completed code should iterate through the command line arguments and create a child process, run the given command in the child process, and the parent process should report the termination status of that child process before continuing with its processing.

<br>
Although the grading of your code will be done by accessing your remote repository, <br>
you must submit the following to the Moodle Assignment:

* Your name:
* CU ID: (4 letters - 4 digits)
* GitHub Username:
* hours to complete lab:

<hr><hr><hr>
