# CSPB 2400 - Computer Systems - Data Lab: Manipulating Bits

## Details

This README provides more details about the assignment and details on how to develop, debug and grade your work.

## Developing & Debugging Your Puzzle Solutions

There are five steps you need to go through. Each of those steps has a rule in the `Makefile` to lets you focus on that step:
 * Write valid puzzles (`make test-coding`)
 * Write correct puzzles (`make test-correctness`)
 * Only use allowed operations (`make test-ops`)
 * Figure out your score (`make test-score`)
 * Don't use too many operations (`make test-count`)

You can run all of these steps using `make grade` but the step-by-step methods are useful to sort out *why* your solution is having problems.

#### The `dlc` Compiler
`dlc` is a modified version of an ANSI C89 compiler from that you can use to check for compliance with the coding rules for each puzzle. The `dlc` program only understands the C89 standard and thus enforces a stricter form of C declarations than is the case for C++ or that is enforced by `gcc`.  Any declaration must appear in a block (what you enclose in curly braces) before any statement that is not a declaration.  For example, it will complain about the following code:

```
  int foo(int x)
  {
    int a = x;
    a *= 3;     /* Statement that is not a declaration */
    int b = a;  /* ERROR: Declaration not allowed here */
    b *= a;     // ERROR -- this comment style causes error
```

The program runs silently unless it detects a problem, such as an illegal operator, too many operators, or forbidden code (`if`, `while`, *etc*) code in the integer puzzles.

Don't include the `<stdio.h>` header file in your `bits.c` file, as it confuses `dlc` and results in some non-intuitive error messages. You will still be able to use `printf` in your `bits.c` file for debugging without including the `<stdio.h>` header, although `gcc` will print a warning that you can ignore.

## Grading

The autograding script produces a report about 'points' -- this doesn't align with what we've described above (which is what holds). This happens in part because of the presence of the extra problems.

#### `btest`
This program checks the functional correctness of the functions in `bits.c`. To build and use it, type the following two commands:

```
  unix> make
  unix> ./btest
```

Notice that you must rebuild `btest` each time you modify your `bits.c` file. 

You'll find it helpful to work through the functions one at a time, testing each one as you go.  You can use the `-f` flag to instruct `btest` to test only a single function:
```
  unix> ./btest -f bitOr
```
You can feed it specific function arguments using the option flags `-1`, `-2`, and `-3`. For example, the following specifies the first argument is `7` and the second is `0xf`.
```
  unix> ./btest -f bitOr -1 7 -2 0xf
```

Here are the command line options for btest:
```
  unix> ./btest -h
  Usage: ./btest [-hg] [-r <n>] [-f <name> [-1|-2|-3 <val>]*] [-T <time limit>]
    -1 <val>  Specify first function argument
    -2 <val>  Specify second function argument
    -3 <val>  Specify third function argument
    -f <name> Test only the named function
    -g        Format output for autograding with no error messages
    -h        Print this message
    -r <n>    Give uniform weight of n for all problems
    -T <lim>  Set timeout limit to lim
```
Examples:
```
  Test all functions for correctness and print out error messages:
  unix> ./btest

  Test all functions in a compact form with no error messages:
  unix> ./btest -g

  Test function foo for correctness:
  unix> ./btest -f foo

  Test function foo for correctness with specific arguments:
  unix> ./btest -f foo -1 27 -2 0xf
```
Btest does not check your code for compliance with the coding
guidelines.  Use `dlc` to do that.

#### `driver.pl`
This is a driver program that uses `btest` and `dlc` to compute the correctness and performance points for your solution. It takes no arguments:

```
  unix> ./driver.pl
```

Your instructors will use `driver.pl` to evaluate your solution.

## Helper program: ishow and fshow

We have included the ishow and fshow programs to help you decipher
integer and floating point representations respectively. Each takes a
single decimal or hex number as an argument. 

To build them type:
```
    unix> make ishow fshow
```
The included program `fshow` helps you understand the structure of floating point numbers.  You can use `fshow` to see what an arbitrary pattern  represents as a floating-point number:
```
  unix> ./fshow 15213243
    Floating point value 2.131829405e-38
    Bit Representation 0x00e822bb, sign = 0, exponent = 0x01, fraction = 0x6822bb
    Normalized.  +1.8135598898 X 2^(-126)
  
  unix> ./fshow 0x15213243
    Floating point value 3.255334057e-26
    Bit Representation 0x15213243, sign = 0, exponent = 0x2a, fraction = 0x213243
    Normalized.  +1.2593463659 X 2^(-85)
```
The `ishow` program behaves in a similar way for integer operations.

Example usages:
```
    unix> ./ishow 0x27
    Hex = 0x00000027,	Signed = 39,	Unsigned = 39

    unix> ./ishow 27
    Hex = 0x0000001b,	Signed = 27,	Unsigned = 27
``
