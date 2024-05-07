# GDB Tutorial
GDB is the Gnu Debugger, a program that helps you debug programs written in C, C++ and other programming languages.

This is the second of three tutorials. The topics of each tutorial are:
* Basic GDB and Debugging C programs at the source level
* Using GDB to examine memory and call C functions
* Debugging programs at the assembly / machine level

In this tutorial, we see how to access the detailed machine information using GDB. We assume you've gone through the other tutorials.

## Machine State
Let's restart our program execution, stopping at the breakpoint in `function_one()`. 

```
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/cs2400/gdb-tutorial 

Breakpoint 3, function_one () at gdb-tutorial.c:18
18	    int x = 10;
1: x = 0
```
In addition to program variabls and/or memory locations we can print out the *registers* on the machine:
```
(gdb) info reg
rax            0x0	0
rbx            0x0	0
rcx            0x0	0
rdx            0x7fffffffe598	140737488348568
rsi            0x7fffffffe588	140737488348552
rdi            0x1	1
rbp            0x7fffffffe490	0x7fffffffe490
rsp            0x7fffffffe480	0x7fffffffe480
r8             0x400910	4196624
r9             0x7ffff7de7ab0	140737351940784
r10            0x846	2118
r11            0x7ffff7a2d740	140737348032320
r12            0x4005a0	4195744
r13            0x7fffffffe580	140737488348544
r14            0x0	0
r15            0x0	0
rip            0x4006bd	0x4006bd <function_one+8>
eflags         0x202	[ IF ]
cs             0x33	51
ss             0x2b	43
ds             0x0	0
es             0x0	0
fs             0x0	0
gs             0x0	0
(gdb) 
```
The individual registers can be accessed using notations like `$rax` or `$r10`. 
```
(gdb) p $r10
$25 = 2118
(gdb)
```
One of important registers is the *program counter*, or `$pc`. The `$pc` variable is a pointer to the next instruction that will be executed. The `$pc` will be (almost) the first instruction in the `function_one()` function. We can use `x` to *disassemble* the instruction (i.e. print it as an instruction).
```
(gdb) p $pc
$26 = (void (*)()) 0x4006bd <function_one+8>
(gdb) x/i $pc
=> 0x4006bd <function_one+8>:	movl   $0xa,-0xc(%rbp)
```
We can disassemble a complete function using `diassemble`:
```
(gdb) disassemble function_one
Dump of assembler code for function function_one:
   0x00000000004006b5 <+0>:	push   %rbp
   0x00000000004006b6 <+1>:	mov    %rsp,%rbp
   0x00000000004006b9 <+4>:	sub    $0x10,%rsp
=> 0x00000000004006bd <+8>:	movl   $0xa,-0xc(%rbp)
   0x00000000004006c4 <+15>:	movl   $0x5,-0x8(%rbp)
   0x00000000004006cb <+22>:	mov    -0x8(%rbp),%edx
   0x00000000004006ce <+25>:	mov    -0xc(%rbp),%eax
   0x00000000004006d1 <+28>:	mov    %edx,%esi
   0x00000000004006d3 <+30>:	mov    %eax,%edi
   0x00000000004006d5 <+32>:	callq  0x4006f4 <function_sub>
   0x00000000004006da <+37>:	mov    %eax,-0x4(%rbp)
   0x00000000004006dd <+40>:	mov    -0x4(%rbp),%eax
   0x00000000004006e0 <+43>:	mov    %eax,%esi
   0x00000000004006e2 <+45>:	mov    $0x400928,%edi
   0x00000000004006e7 <+50>:	mov    $0x0,%eax
   0x00000000004006ec <+55>:	callq  0x400550 <printf@plt>
   0x00000000004006f1 <+60>:	nop
   0x00000000004006f2 <+61>:	leaveq 
   0x00000000004006f3 <+62>:	retq   
End of assembler dump.
(gdb)
```
We see that we've stopped at the 3rd instruction which is 8 bytes into the code for `function_one()`. By default, when we set a breakpoint for a function, it is set immediately after a *function prologoue* that sets up the function's frame pointer (we'll discuss this in class).

## Moving instruction-by-instruction

We can use the `nexti` and `stepi` commands to continue execution *by instruction* rather than *by line*. We'll use the `ni` and `si` short forms:
```
(gdb) si
19	    int y = 5;
1: x = 10
(gdb) x/i $pc
=> 0x4006c4 <function_one+15>:	movl   $0x5,-0x8(%rbp)
(gdb)
```
It's tiring to have to print out the current instruction each time. Let's use `display` to simplify that tasks:
```
(gdb) display/i $pc
2: x/i $pc
=> 0x4006c4 <function_one+15>:	movl   $0x5,-0x8(%rbp)
(gdb) si
22	    z = function_sub(x, y);
1: x = 10
2: x/i $pc
=> 0x4006cb <function_one+22>:	mov    -0x8(%rbp),%edx
(gdb) si
0x00000000004006ce	22	    z = function_sub(x, y);
1: x = 10
2: x/i $pc
=> 0x4006ce <function_one+25>:	mov    -0xc(%rbp),%eax
(gdb) si
0x00000000004006d1	22	    z = function_sub(x, y);
1: x = 10
2: x/i $pc
=> 0x4006d1 <function_one+28>:	mov    %edx,%esi
(gdb) si
0x00000000004006d3	22	    z = function_sub(x, y);
1: x = 10
2: x/i $pc
=> 0x4006d3 <function_one+30>:	mov    %eax,%edi
(gdb) si
0x00000000004006d5	22	    z = function_sub(x, y);
1: x = 10
2: x/i $pc
=> 0x4006d5 <function_one+32>:	callq  0x4006f4 <function_sub>
(gdb)
```
We're now single-stepping through the instructions in our program. We are about to execute a `callq` function which is used to implement a function call. If we use `ni`, we'll skip over the call (i.e. the call will be executed, but we won't follow that execution into `function_sub()`). If we use `si` we will *step into* the `function_sub` call. Let's do that:
```
(gdb) si
function_sub (a=0, b=0) at gdb-tutorial.c:27
27	{
2: x/i $pc
=> 0x4006f4 <function_sub>:	push   %rbp
(gdb) si
0x00000000004006f5	27	{
2: x/i $pc
=> 0x4006f5 <function_sub+1>:	mov    %rsp,%rbp
(gdb) si
0x00000000004006f8	27	{
2: x/i $pc
=> 0x4006f8 <function_sub+4>:	sub    $0x20,%rsp
(gdb) 
```
We can exmaine memory based on registers. For example, let's see the program stack:
```
(gdb) x/10wx $rsp
0x7fffffffe470:	0xffffe490	0x00007fff	0x004006da	0x00000000
0x7fffffffe480:	0x004008a0	0x0000000a	0x00000005	0x00000000
0x7fffffffe490:	0xffffe4a0	0x00007fff
(gdb)
```
The stack pointer has value `0x7fffffffe470` and the first entry on the stack is a pointer (8 bytes with value `0x00007ffffffe490`) and then an 8 byte value which is the *return address* `0xx00000000004006da`), which is the address of the instruction immediately after the `callq` instruction we executed earlier.

## Wrapping up and automating things

You now have all the tools you need to do the labs in this course, but there's more to GDB than we've covered. There are [complete tutorials online](https://sourceware.org/gdb/onlinedocs/gdb/index.html#Top) that should now be more accessible given the basics.

You can define your own GDB functions using `define`. This can be useful if you ahve a repeated sequence of commands (e.g. perhaps to display the stack in a certain format).

You can read in a series of commands using `source <filename>` -- this is most useful for reading in a series of `define`-d commands or common setup code.

By default, the `.gdbinit` file will be `source`-d when you start gdb. In Unix, files starting with `.` are not shown in file listings, so you may wan to a file name that's easier to find and then use `source` to load the file. In the example, I've provided a sample file called `gdbinit`.