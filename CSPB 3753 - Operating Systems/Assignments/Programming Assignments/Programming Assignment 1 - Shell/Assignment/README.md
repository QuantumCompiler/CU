# CSPB-3753 Programming Assignment - Creating your own Shell
<figure width=100%>
  <IMG SRC="https://www.colorado.edu/cs/profiles/express/themes/cuspirit/logo.png" WIDTH=100 ALIGN="right">
</figure>

This assignment provides a hands-on experience in creating a basic ***shell*** , which will
introduce you to fundamental concepts of operating systems, process management, and command-line interfaces. 

The implementation of a ***shell*** program requires a solid understanding of system calls, process creation, and basic command parsing.

A ***shell*** is a command-line interface (CLI) that allows users to interact with an operating system by entering commands. It serves as a mediator between the user and the operating system, interpreting the commands entered by the user and passing them to the operating system for execution. The ***shell*** is a fundamental component of Unix-like operating systems such as including Linux and the macOS.


#### Building a shell can be a valuable exercise for several reasons:

* *Understanding Operating Systems:*<br>
Building a shell provides hands-on experience with operating system concepts. You'll gain insights into how processes are created, managed, and executed within an operating system.

* *System Programming Skills:*<br>
 Developing a shell requires knowledge of system calls and low-level programming. This experience will enhance your system programming skills and give you a deeper understanding of how software interacts with the underlying hardware.

* *Command-Line Interface Familiarity:*<br>
Shells are fundamental to interacting with Unix-like operating systems. By building a shell, you'll become more familiar with command-line interfaces which are commonly used in software development, system administration, and other technical fields.

* *Processes and Forking:*<br>
The process creation and management aspects of building a shell involve concepts like forking and executing processes. Understanding these concepts is crucial for developing robust and efficient software.


#### Common Unix shells include:
* Bash (Bourne Again SHell): The default shell for many Linux distributions and macOS.
* Zsh (Z Shell): An extended and highly customizable shell.
* Ksh (Korn Shell): Developed by David Korn as an extension of the original Bourne Shell.

#### Key features of a shell include:

* *Command Interpretation:* <br>
The shell interprets the commands entered by the user and translates them into system calls that the operating system can understand and execute.

* *User Interface:*<br>
Shells provide a text-based user interface where users interact with the system by typing commands. The commands can perform a wide range of tasks, from simple file manipulations to complex system configurations. Built-in commands are used to change the shell's environment.

* *Scripting:*<br>
Shells support scripting, allowing users to write scripts or programs consisting of a series of shell commands. This enables automation of repetitive tasks and the creation of more complex workflows.

* *Redirection and Pipes:*<br>
Shells support input and output redirection, allowing users to redirect the output of a command to a file or another command. Pipes enable the output of one command to be used as the input for another.

* *Variables and Environment:*<br>
Shells allow the use of variables to store and manipulate data. They also manage the environment for each command, providing a set of variables and settings that influence how commands execute.

* *Job Control:* <br>
Shells allow users to manage multiple processes concurrently. Users can start processes in the background, bring them to the foreground, and suspend or terminate them.

The core feature of a shell is the command-line interface that facilitates communication between users and the operating system.  The shell interprets the text to execute commands, manage processes, and automate tasks. It plays a crucial role in the daily workflow of users working with Unix-like systems.

You will implement a shell that will support:
* *User Interface* - The shell will request commands from the user until the built-in command `done` is seen, at which time the shell process will exit.
Often your implementation will need to handle an unspecified amount of data.
You can always try to create a buffer that is large enough to handle any data, but it is a waste of space in most instances and will not handle all quantities of data.
A better solution is to use the heap to dynamically allocate space as needed.
In this lab you will dynamically create data structures to handle space efficiency with an unknown amount of data.

* *Command Interpretation* - Each command line received by the user interface will be interpreted to determine each command and its parameters.  The shell will spawn new processes to handle each command.

* *Redirection and Pipes* - 
Multiple commands can be entered in a single command line.  The pipe symbol '|' will divide the command line into multiple commands and specify that the output of a command is redirected to the input of the next command.


<hr>

<img src="images/construction-set-icon.jpg" alt="Under Construction" WIDTH=120 ALIGN="left" style="margin-right:10px"/>

### This lab is still under construction.  
 
 Please report all speeling and grammered issues.<br>
 Also let us know about any unclear descriptions of work to be performed. 
 <br><br><br>
<hr>

This assignment will combine the concepts from labs 1-3 into your solution.  Please reuse your code from those labs.  Keep the functions in separate code files in your shell repository and create header files (.h) for each source file (.c).  Be sure to provide good documentation in both the source and header files.  You should also create a `makefile` to handle the compulation of the source files into a single executable.

### Programming Assignment Objectives:
#### **Command Parsing:**
>Accept user input and parse it to identify the command and its arguments.  
>Handle simple commands and parameters.  
>Dynamically allocate data structures by using systems calls (e.g. malloc, realloc, free).

#### **Command Execution:**
>Execute system commands using system calls (e.g., fork, exec).  
>Implement basic error handling for command execution.
#### **Built-in Commands:**
>Implement a few built-in commands (e.g., cd, exit) to demonstrate versatility.

#### **Interactive Interface:**
>Display a command prompt to indicate that the shell is ready to accept user input.

>Continuously prompt the user for input and execute commands until an exit command is issued.


	
<hr>

### Creating Your Own Shell
Your task is to extend the Unbound Data, Fork, and Pipe labs to create a basic shell with a small memory footprint. 

The shell should operate as follows:
1. Print a customized welcome message to stdout.
2. Display a customized command prompt.
3. Fetch a command from stdin and store it into a dynamic buffer.
4. Execute this command.
5. Report the exit status of this command to stdout if not run in background.
6. Repeat the steps 2 through 5 until the user enters DONE.
7. Release all allocated memory

To keep things simple, we will not do any sophisticated parsing of the user’s input
 (e.g., no quotation matching, checks for escape characters, etc..). 
 In particular, you may assume that the user will input data that obeys the following grammatical structure:
 ```
cmd_1 arg arg ... arg <pipe> cmd_2 arg arg ... arg <pipe> ... <pipe> cmd_n arg arg ... arg 
```
Notice that the background symbol '&' is not specified in the syntax.  You do not need to provide support for leaving a process (or set of processes) running in the background.  Your shell should always wait for the processes to complete before requesting and accepting another command line from the user.
<hr>

### Step 1 - Create command line reader
Similar to your first lab, you need to read a buffer of data of an unknown size while keeping the memory usage minimized.  Create your interface handler to read a buffer of data, process the data, and release the buffer.  

<hr>

### Step 2 - Parse the Command Line
Create a main function to iterate reading a command line and performing built-in commands.  Start by creating a loop to call your dynamic command line reading routine and print the results.  Remember that you will need to explicitly `free` the memory returned on each iteration. Once you can iterate through reading multiple command lines, add processing to look for the built-in commands that are processed by the shell. 

#### 2.1 **Handle the Built-in Commands.**
Built-in shell commands are commands that are part of the shell itself, rather than being separate executable programs. These commands are built into the shell for efficiency and are usually simple and fundamental operations. When a user enters a command in a shell, the shell checks whether the command is a built-in command or an external executable.  External executables will be dealt with in Step 3.  For this assignment, you must only handle built-in commands that are the first and only command in the command line.

Common built-in shell commands in a `BASH` shell include:
| command | | functionality |
|---|---|---|
| `cd` |  | Changes the current working directory.|
| `echo` || Prints text to the standard output.|
| `pwd` || Prints the current working directory.|
| `exit` || Exits the shell or a script.|
| `export` || Sets environment variables.|
| `alias` || Creates a shortcut or alias for a command.|
| `unset` || Removes a variable or function.|
| `source` || Executes commands from a file within the current shell session.|
| `history` || Displays command history (a list of the previous commands given to the shell).|

Your shell needs to handle two built-in commands: `done` to exit the shell program and `cd` to change the current working directory of the shell process. The `done` command will exit the shell command processor, cleaning up any outstanding dynamically allocated data. 
The `cd` command needs to handle changing the current directory of the shell process so all future commands will start with the new directory as its current directory.  See the system calls for managing the current working directory of the current process.  You need to modify the parent process' environment because a child process will inherit that environment from the parent.

***HINT: You can look at the `example.c` code in `client-server lab` for an example of handling built-in commands.***

#### 2.2 **Parse the user input to identify the command and its arguments.**
You will be using the  *exec family* of functions to execute other programs.  You should parse the command line into a set of strings separated by white space.  The best  utility to use for parsing would be `strtok()`.  Use that function to create a list of pointers to the strings.  Make sure to make the list dynamically sized to handle any number of parameters.

***HINT: You can look at the `example.c` code in `client-server lab` for an example of using `strtok()` to build a list of parameters.***


<hr>

### Step 3 - Execute Commands
Once you can read a command line and parse the parameters, implement the parent's creation of a child process to execute the given program.  Start simple with commands that do not require a parameter such as `ls` to make sure the process creation works.  Then add in parameters to make sure the parsing is correct.  Only implement the code needed to handle a single executable at this point.  You will handle multiple executables in a command line in Step 4.

#### **3.1 Fork a new process using fork() to create a child process.**
The `fork lab` guided you through creating new processes.  The `fork()` system call is used to create a new process. When `fork()` is called, it essentially creates a copy of the current process, referred to as the parent process, resulting in two identical processes. These processes are distinguished by their process IDs (PIDs) and the original process continues to be the parent, and the newly created process is the child.

#### **3.2  In the child process, use exec() to execute the parsed command.**
The `fork lab` guided you through replacing the program running in a process. The `execv` system call is used to execute a program. It is part of the *exec family* of functions, which includes various variations like `execv, execve, execl`, and others. The `execv()` function specifically takes an array of pointers to null-terminated strings as its arguments.
When a process calls `execv()`, the operating system replaces the process' current program image with the one specified in the call. The new program is specified by providing the path to its executable file.<br><br>
Most programs require command-line arguments. With `execv()`, these arguments are passed as an array of pointers to null-terminated strings. The last element of the array must be a NULL pointer to indicate the end of the argument list. The new program also inherits the environment variables of the calling process, such as the current working directory.

#### **3.3 In the parent process, wait for the child process to finish using wait().**
A zombie process, in the context of operating systems, refers to a process that has completed its execution, but still has an entry in the process table. This entry is retained to allow the parent process to retrieve information about the child process, such as its exit status. Despite being technically "dead" or completed, a zombie process continues to consume a small amount of system resources.<br><br>
Zombie processes are usually created when a child process finishes execution, but the parent process has not yet collected the exit status using system calls like wait() or waitpid(). If a parent process fails to reap its child processes properly, they may remain in the zombie state until the parent terminates.<br><br>
It's important for the parent process to handle the termination of its child processes correctly to avoid leaving behind zombie processes, as they can accumulate and potentially lead to resource issues in the long run.


<hr>

### Step 4 - Redirect output from one process to the input of the next process
Now that you can support the parsing of command parameters, you will implement support for multiple commands in a command line that are separated by the pipe symbol `|`.  Using the concepts you learned in the `pipes lab`, create the redirection between each 
of the commands where you found a `|` pipe symbol.

Piping is a mechanism that allows the output of one command to serve as the input for another command. This enables the combination of multiple commands to perform more complex operations. The syntax for indicating piping in your shell will use the vertical bar (|) character.

1. The first command in the pipeline is executed.
Its output (stdout) is sent to the next command in the pipeline.
2. The second command (and subsequent commands, if any) takes the output of the previous command as its input.   In the example below, `command1` is executed, and its output is sent as input to `command2`.

```
        command1 | command2
```

3. You can chain multiple commands together using multiple pipes between multiple commands.  In the example below, the output of `command1` is passed to `command2`, and the output of `command2` is passed to `command3`.

```
        command1 | command2 | command3
```

Real-world Example:  List all files in the current directory, filter for files containing the word "example," and then count the number of lines.  In the example below, `ls -l` lists files in the current directory, then `grep` "example" filters for lines containing the word "example", and finally `wc -l` counts the number of lines in the output.

```
        ls -l | grep "example" | wc -l
```

Piping is a fundamental concept in operating systems and is widely used in shell scripting to build more sophisticated and efficient command-line operations. The flexibility of pipes allows users to create complex data processing workflows by combining simple, specialized commands into complex solutions.

<hr>

### Step 5 - Use `valgrind` to profile your code
Valgrind is an instrumentation framework for building dynamic analysis tools. There are Valgrind tools that can automatically detect many memory management and threading bugs as it profiles your programs in detail. You can also use Valgrind to build new tools.
<br><br>
The Valgrind distribution currently includes seven production-quality tools: ***a memory error detector***, two thread error detectors, a cache and branch-prediction profiler, a call-graph generating cache and branch-prediction profiler, and two different heap profilers. 

Memory management and dynamic data structures are prone to errors that are too hard to detect. Some of the common errors are listed below:
* Use of uninitialized memory
* Reading/writing memory after it has been freed
* Reading/writing off the end of malloc'd blocks
* Reading/writing inappropriate areas on the stack
* Memory leaks -- where pointers to malloc'd blocks are lost forever
* Mismatched use of malloc/new/new[] vs free/delete/delete[]
* Some misuses of the POSIX pthreads API

These errors usually lead to program crashes.  Most of the time the crash occurs long after the offending code was executed.  
This is a situation where we need Valgrind. Valgrind works directly with the executables, with no need to recompile, relink or modify the program to be checked. Valgrind profiles the program and points out where in the code it has detected the "leak."

Valgrind simulates every single instruction your program executes. For this reason, Valgrind finds errors not only in your application, but also in all supporting dynamically-linked (.so-format) libraries, including the GNU C library, the X client libraries, Qt if you work with KDE, and so on. That often includes libraries, for example the GNU C library, which may contain memory access violations.

<img src="images/ldp.jpg" alt="Linux Documentation Project" WIDTH=120 ALIGN="left" style="margin-right:10px"/>
  
You can find some more useful information in the documentation from Linux Documentation Project for `valgrind` [https://tldp.org/HOWTO/Valgrind-HOWTO](https://tldp.org/HOWTO/Valgrind-HOWTO/index.html)

<hr>

###  Code Documentation and Style

Documentation of your source code will be part of your grade.  Documentation will need to include the following:

* Documentation:<br> Your code should be well-commented and give good explanations of
the complicated parts of your program.
* Legibility/Formatting:<br> Your style should be consistent and readable (e.g., make good use of whitespace). Also, if you don’t follow the submission format instructions, you will lose some points.

* Error Handling<br>
In your code, there are many places where system errors can arise (errors that are out of your control). In these places, you must always provide some sort of error checking. Typically, if a system call returns something negative, then this indicates an error, but you should check the man pages to be sure. If an error occurs, you should use the perror function to print the error to stderr as follows (Visit man page for `perror` more details):
```
          perror("some informative message");
```

<hr>

### In this assignment, you will need to understand the following concepts:
* dynamic allocation of data structures.
* process for cloning a new process.
* how to run a different program in a process.
* the standard input and output file descriptors used by a process (stdin, stdout, stderr).
* how to use a pipe for communications between processes. 
* how to verify that you have deallocated any dynamically allocated data structures.

### In this assignment, you will use at least the following system calls:
* malloc()
* realloc()
* free()

* fork()
* execv()
* wait(), waitpid()

* pipe()
* dup2()
* close()

<hr>

When you’re done, you should make sure that your shell is not leaking any memory.
Most of the time (but not always) you should have a matching free for every malloc, then you’re in the clear, but the tool `valgrind` will sniff out any memory leak should you have one. We will check for memory leaks, so be sure to run `valgrind` on your solution before you submit.

### Grading will review your solution code as well as your performance in an interview
The majority of the grade for your code will be based on the correctness of your program, but some will be based on your style of coding.  ***If your code in your remote repository does not compile, you cannot earn more that 25 points.***  Make sure your code is in working order in your remote repository.

| points | | feature |
|---|---|---|
| 5 | | Reading command line into dynamic buffer |
| 5 | | Built-in commands (done, cd) |
| 5 | | Parsing command line, generating parameter list |
| 5 | | Proper handling of all return values from system and library calls |
| 5 | | Proper `fork()` and `exec()` usage to create single new process running a new command|
|10 | | Proper `fork()` and `exec()` usage to handle multiple new processes running new commands|
|10 | | Handling the redirection for a single pipe |
|10 | | Handling the redirection for multiple pipes |
|10 | | Proper handling to guarantee there are no "zombie" processes |
|10 | | Proper memory handling to guarantee there are no memory leaks |
|10 | | Documentation of the source file(s) - well commented with good explainations of the functions and complex parts of the code |
|10 | | Legibility, Formatting - code must be consistant and readable, making good use of whitespace |
| 5 | | Elegance of your design.  Routines should not be needlessly compilcated, no usused variables, no redudant code.|

<hr>

### When you have completed the Assignment

Make sure to complete all the required elements of the assignment.  They are a combination of the labs and some additional functionality. 
The program you create will need to provide comments that describe the purpose and usage of the program, purpose and usage of each function, and comments with the functions describing the algorithm being used to solve the problem.

I will continue to provide frameworks for the individual recitation labs so that you have a good starting point to complete the intended training.  These templates should allow you to see the level of documentation expected and style of code I prefer to see.  They will also give you a starting point to create your own application.

***Make sure to `commit` to your local repository and `push` to the remote repository.*** 
Grading of your work will be based on the information that you have in your remote repository.
	
<img src="images/deliverable.png" alt="Deliverable Item" WIDTH=40 ALIGN="left" style="margin-right:10px" />
Although the grading of your code will be done by accessing your <br> remote repository,
you must submit the following to Moodle Assignment:

* Your name:
* CU ID: (4 letters - 4 digits)
* GitHub Username:
* hours to complete lab:

<hr><hr><hr>