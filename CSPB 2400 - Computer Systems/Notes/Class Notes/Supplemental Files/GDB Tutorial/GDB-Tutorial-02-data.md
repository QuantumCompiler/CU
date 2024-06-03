
# GDB Tutorial
GDB is the Gnu Debugger, a program that helps you debug programs written in C, C++ and other programming languages.

This is the second of three tutorials. The topics of each tutorial are:
* Basic GDB and Debugging C programs at the source level
* Using GDB to examine memory and call C functions
* Debugging programs at the assembly / machine level

In this tutorial, we go through printing data an examining memory contents. We assume you've gone through the first tutorial.

## Printing data
Starting at the beginning of `function_one()`, let's try to `print` the value of variable `x`:
```
(gdb) print x
$1 = 0
(gdb) n
19	    int y = 5;
(gdb) p x
$2 = 10
(gdb) p/x x
$3 = 0xa
(gdb) p/o x
$4 = 012
(gdb) print/t x
$5 = 1010
(gdb) p/c x
$6 = 10 '\n'
(gdb)
```
At first, `x` has value `0` because we hadn't actually executed the statement `int x=10;`. When we `step` or `next` over that statement, we then set `x=10` and get to line #19, `int y=5;`.

By default, `print` will print in decimal, but we can also print in hexidecimal (/x), octal (/o), binary (/t) or as an ASCII character (/c) as shown.

Sometimes, we want to print values every time we come to the GBD command line without having to always enter `print`. We can use `display` to do this:
```
(gdb) display x
1: x = 10
(gdb) n
22	    z = function_sub(x, y);
1: x = 10
(gdb) n
I have computed q as 5
23	    printf("x-y is %d\n", z);
1: x = 10
(gdb)
```
We can also print expressions:
```
(gdb) print x-y
$7 = 5
(gdb)
```
In fact, you can actually call functions that are in your program:
```
(gdb) print strlen("hi mom")
$8 = 6
(gdb)
```
Notice that output values are of the form `$N = <value>` for some constant `N`. We can use those *number variables* in subsequent expressions. E.g.:
```
(gdb) print $7 * $8
$11 = 30
(gdb)
```
We'll see that these number variables are pretty useful later on when we need to "write down" long memory addresses and pointer values.

## Examining Memory

Up to now, we've printed named variables in our program, but we can also `x`-mine data at a memory location. For example, set a breakpoint for `function_two()` and continue execution:
```
(gdb) break function_two
Breakpoint 4 at 0x40072c: file gdb-tutorial.c, line 58.
(gdb) c
Continuing.
x-y is 5

Breakpoint 2, main () at gdb-tutorial.c:12
12	    function_two();
(gdb)
```
We had defined some global variables, and we can print those:
```
(gdb) p int_full
$12 = {-559038737, -1340212530, -268060143, 1554098974, -904811746, -1168197103, 
  14531089, -1331228499}
  (gdb) p/x int_full
$13 = {0xdeadbeef, 0xb01dface, 0xf005ba11, 0x5ca1ab1e, 0xca11ab1e, 0xba5eba11, 
  0xddba11, 0xb0a710ad}
(gdb) p/x int_full[2]
$14 = 0xf005ba11
(gdb)
```
We can also print the address of a specific location
```
(gdb) p &int_full[2]
$15 = (int *) 0x601088 <int_full+8>
```
This indicates that (on my system) the `int_full[2]` is stored in memory location `0x601088`. If we print out `$15`, we'll just print out that memory address again, but if we use `x` we will fetch the data from that memory location:
```
(gdb) p/x $15
$16 = 0x601088
(gdb) x/x $15
0x601088 <int_full+8>:	0xf005ba11
```
In other words, `$15` contains a *pointer* and using `x` causes us to de-reference the pointer or access the data that `$15` points to.

Because "bits is bits", we can use the pointer to interpret the contents of memory in any way we like. For example, in the following sequence we will examine the memory location as a `g`iant word (8 bytes) `w`ord (4 bytes), `h`alf-word (2 bytes) or `b`yte. 
```
gdb) x/gx $15
0x601088 <int_full+8>:	0x5ca1ab1ef005ba11
(gdb) x/gx $15
0x601088 <int_full+8>:	0xf005ba11
(gdb) x/hx $15
0x601088 <int_full+8>:	0xba11
(gdb) x/bx $15
0x601088 <int_full+8>:	0x11
```
By default, `x` will use the last format specified, so you may want to go back to specifying `w`:
```
(gdb) x/x $15
0x601088 <int_full+8>:	0x11
(gdb) x/wx $15
0x601088 <int_full+8>:	0xf005ba11
(gdb) 
```
We can also print out multiple memory locations in the same format:
```
(gdb) x/3wx int_full
0x601080 <int_full>:	0xdeadbeef	0xb01dface	0xf005ba11
(gdb)
```
The full syntax is `x/N[g/w/h/b] [x/o/t/d/c]` where `N` is an optional number of output entries follow followed by a size (`g/w/h/b`) and format (`x/o/t/d/c`).

Again, because "bits is bits", you can interpret the same memory location as a float or string, even if that isn't meaningful for the program.
```
(gdb) x/f $15
0x601088 <int_full+8>:	1.6437896942065213e+138
(gdb) x/s $15
0x601088 <int_full+8>:	"\021\272\005\360\036\253\241\\\036\253\021\312\021\272^\272\021\272", <incomplete sequence \335>
(gdb) 
```

## Getting back to debugging...

Recall that our program dies for some reason. Let's single-step the program until we get to the `printf` using `str_ptr`. We'll use `next` to avoid stepping into the functions `memcpy` and `printf`:
```
(gdb) n
First, let's copy the full to the empty
59	    memcpy(int_empty, int_full, sizeof(int) * N);
(gdb) n
61	    printf("Now, let's compare the two\n");
(gdb) n
Now, let's compare the two
62	    printf("The result is %d\n", memcmp(int_empty, int_full, sizeof(int) * N));
(gdb) n
The result is 0
64	    printf("Length of initialized string is %ld\n", strlen(str_init_ptr));
(gdb) 
Length of initialized string is 25
65	    printf("Length of un-initialized string is %ld\n", strlen(str_ptr));
(gdb) p str_ptr
$17 = 0x0
(gdb)
```
We see that the `str_ptr` variable is `NULL`. So, we've identified the problem, but our program is going to blow up at this point because of the access to the `NULL` pointer.

Let's set `str_ptr` to some value so that it doesn't blow up and let's us continue. We'll set it to value of the existing pointer `str_init_ptr`:
```
(gdb) p str_init_ptr
$18 = 0x40094c "this is a constant string"
(gdb) set str_ptr = str_init_ptr
(gdb) p str_ptr
$19 = 0x40094c "this is a constant string"
(gdb) n
Length of un-initialized string is 25
66	    printf("Size of str_ptr is %ld\n", sizeof(str_ptr));
(gdb)
```
This lets us continue execution:
```
(gdb) n
Size of str_ptr is 8
68	    strncpy(str_buffer, str_init_ptr, sizeof(char) * STRBUF);
(gdb) n
69	    printf("String is now %s\n", str_buffer);
(gdb) n
String is now this is a constant string
```
Let's now finish the execution of `function_two()`:
```
(gdb) finish
Run till exit from #0  function_two () at gdb-tutorial.c:71
0x00000000004006ae in main () at gdb-tutorial.c:12
12	    function_two();
(gdb)
```
## Tracking down pointers....
By finishing `function_two()` we've created a linked-list data structure with `root` as a pointer to the first element. Let's examine that:
```
(gdb) p root
$20 = (struct LinkedList *) 0x6024a0
(gdb) p *root
$21 = {data = 3, next = 0x602480}
(gdb) p root -> next
$22 = (struct LinkedList *) 0x602480
(gdb) p *(root -> next)
$23 = {data = 2, next = 0x602460}
(gdb)
```
We can also use `x` to examine the memory that makes up a LinkedList structure:
```
(gdb) x/4x root
0x6024a0:	0x00000003	0x00000000	0x00602480	0x00000000
(gdb) 
```
Each LinkedList element is an integer (4 bytes) an a pointer (8 bytes on this machine). We see that the contents match the output of `$21` from above.