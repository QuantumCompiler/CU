# GDB Tutorial - Basic GDB for C source
GDB is the Gnu Debugger, a program that helps you debug programs written in C, C++ and other programming languages.

This is the first of three tutorials. The topics of each tutorial are:
* Basic GDB and Debugging C programs at the source level
* Using GDB to examine memory and call C functions
* Debugging programs at the assembly / machine level

In this tutorial, we go through debugging a C program at the source level. We assume only limited background in using the C compiler and Linux shell.

You should have been given a program `gdb-tutorial.c` that contains the source code for the tutorial. You should also have access to a set of videos corresponding to each tutorial; you should download the source file and follow the tutorial videos, duplicating the actions take in those tutorial videos.

## Compiling your program for GDB
GDB needs certain information in the program executable to provide source level debugging information. This information can be provided by compiling using the `-g` compilation flag. For example:
```
$ cc -o gdb-tutorial -g gdb-tutorial.c
```
For our tutorial, we'll use the default optimization level. As we'll see later, when compilers improve your C program ("optimizing" it) it complicates the relationship between what the machine sees and your C code.

## Starting GDB and running your program
Start GDB by specifying the executable you wish to debug, e.g.  `gdb gdb-tutorial`. You will see a long banner explaining the warranty and other information. We'll only show that one time:
```
$ gdb gdb-tutorial 
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from gdb-tutorial...done.
(gdb)
```
You are now at the GDB prompt. You can enter `quit` and press enter or press `Ctrl-d` to exit. You can also get detailed help by entering `help` and pressing enter. This will give a high level list of topics.

GDB provide *auto completion* using TAB. For example, type `help break` and hit TAB. You'll have chioces between help on the `break` command and the `breakpoints` topic. You can enter `p` to select the longer option or hit Enter to select `break`. Try running `help break` -- the help system is extensive and useful once you've figured out the overall system.

For now, enter the `run` command to actually execute the `gdb-tutorial` program. You should see output similar to
```
(gdb) run
Starting program: /home/cs2400/gdb-tutorial 
I have computed q as 5
x-y is 5
First, let's copy the full to the empty
Now, let's compare the two
The result is 0
Length of initialized string is 25

Program received signal SIGSEGV, Segmentation fault.
strlen () at ../sysdeps/x86_64/strlen.S:106
106	../sysdeps/x86_64/strlen.S: No such file or directory.
(gdb) 
```
This program has an error (we didn't initialize a pointer and then tried to de-reference it). Your execution of the program may or may not give the same error message before returning to the GDB prompt.

## Setting breakpoints and controlling execution

We're going to set a *breakpoint* in function `main` and run the program again:
```
(gdb) break main
Breakpoint 1 at 0x40069a: file gdb-tutorial.c, line 11.
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/cs2400/gdb-tutorial 

Breakpoint 1, main () at gdb-tutorial.c:11
11	    function_one();
(gdb) 
```
The program is now running but has been stopped immediately prior to the execution of the `function_one()` call. Enter the command `tui enable`. This will enable a `terminal user interface`. You should see something like this:
```
   ┌──gdb-tutorial.c──────────────────────────────────────────────────────────────┐
   │1       #include <stdio.h>                                                    │
   │2       #include <string.h>                                                   │
   │3       #include <stdlib.h>                                                   │
   │4                                                                             │
   │5       extern void function_one();                                           │
   │6       extern int function_sub(int a, int b);                                │
   │7       extern void function_two();                                           │
   │8                                                                             │
   │9       int main()                                                            │
   │10      {                                                                     │
B+>│11          function_one();                                                   │
   │12          function_two();                                                   │
   │13      }                                                                     │
   │14                                                                            │
   │15      /*********************************************************************│
   │16      void function_one()                                                   │
   │17      {                                                                     │
   │18          int x = 10;                                                       │
   │19          int y = 5;                                                        │
   │20          int z;                                                            │
   │21                                                                            │
   │22          z = function_sub(x, y);                                           │
   │23          printf("x-y is %d\n", z);                                         │
   │24      }                                                                     │
   └──────────────────────────────────────────────────────────────────────────────┘
native process 4061 In: main                                    L11   PC: 0x40069a 
(gdb) 
```
This display will be refreshed as you execute subsequent commands. It's useful when debugging programs where you have C source code available. It's less useful for machine level debugging. You can disable the UI by entering `tui disable`. For now, you can either leave it enabled or not -- we won't show the interface in our outputs below. You'll find that the program output will screw up the program text - you can refresh the display by pressing "Ctrl-l", *i.e.* by holding down control and pressing the "L" key.

### Next and Step

Our program has paused immediately prior to executing the `function_one()` call. At this point we could execute any of the following commands:
* `cont` - continue execution as if we hadn't stopped, continuing to the next breakpoint or until the program exits.
* `finish` - continue execution until the current function (`main`) finishes and then drop back to the GDB command line
* `next` -  execute the call to `function_one()` and stop on the `next` line
* `step` - continue execution and "`step` into" the function `function_one()`.

For now, let's `step` into the function. You should see something like this:
```
(gdb) step
function_one () at gdb-tutorial.c:18
18	    int x = 10;
(gdb) 
```
We are now in `function_one()`. Enter `step` again or just `s` (GDB accepts unique prefixes of commands)
```
(gdb) s
19	    int y = 5;
(gdb)
```
Now, just hit ENTER -- GDB will execute the last command by default.
```
(gdb) 
22	    z = function_sub(x, y);
(gdb)
```
We dont' want to `step` into `function_sub` -- instead, we want to go to the next line, allowing `function_sub` to do whatever it needs to do. Enter `next`:
```
(gdb) next
I have computed q as 5
23	    printf("x-y is %d\n", z);
(gdb)
```
At this point, we could `cont`-inue execution or `finish` the execution of the function.  Let's `finish`:
```
(gdb) finish
Run till exit from #0  function_one () at gdb-tutorial.c:23
x-y is 5
main () at gdb-tutorial.c:12
12	    function_two();
(gdb) 
```
We're back in `main()` and about to call `function_two()` (which will have an error).

### Setting another breakpoint
Assume we want to come back to this point again without having to single step through the program. We can do this by setting another breakpoint. We'll do this one the file:line method and then re-start the program to get back to this same point:
```
(gdb) break gdb-tutorial.c:12
Breakpoint 2 at 0x4006a4: file gdb-tutorial.c, line 12.
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/cs2400/gdb-tutorial 

Breakpoint 1, main () at gdb-tutorial.c:11
11	    function_one();
(gdb) c
Continuing.
I have computed q as 5
x-y is 5

Breakpoint 2, main () at gdb-tutorial.c:12
12	    function_two();
(gdb)
```
We now have two breakpoints set and can delete the first one (in function `main`)
```
(gdb) info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000040069a in main at gdb-tutorial.c:11
	breakpoint already hit 1 time
2       breakpoint     keep y   0x00000000004006a4 in main at gdb-tutorial.c:12
	breakpoint already hit 1 time
(gdb) del 1
(gdb) info break
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x00000000004006a4 in main at gdb-tutorial.c:12
	breakpoint already hit 1 time
(gdb)
```
If we run again, we'll stop at line 12
```
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/cs2400/gdb-tutorial 
I have computed q as 5
x-y is 5

Breakpoint 2, main () at gdb-tutorial.c:12
12	    function_two();
(gdb)
```
We can also set a breakpoint in `function_one()` -- that breakpoint will trigger when we enter `function_one()`, just as our earlier breakpoint in `main()`.
```
(gdb) break function_one
Breakpoint 3 at 0x4006bd: file gdb-tutorial.c, line 18.
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/cs2400/gdb-tutorial 

Breakpoint 3, function_one () at gdb-tutorial.c:18
18	    int x = 10;
(gdb)
```
When we're in a function, we can use `where` to see the function calls that got us here:
```
(gdb) where
#0  function_one () at gdb-tutorial.c:18
#1  0x00000000004006a4 in main () at gdb-tutorial.c:11
(gdb) 
```
The `next`, `step`, `cont` and `finish` commands are the most common "navigation" commands when combined with setting (and removing) breakpoints. 