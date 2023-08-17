# Huffman Codes
We often work with storing or transporting data. If we can compress
this data in a lossless way, we save money and time on disk space and
network traffic. _Huffman Encoding_ is a neat process where we reduce
the number of bits required to store individual components from some
alphabet, when the frequency those components appear is not evenly
distributed.

In English, there are common letters (e, m, s, t) and less common
letters (x, z, q). Huffman codes exploit this by letting us use short
bit patterns for common letters and longer ones for uncommon letters.

The examples you'll read about unanimously talk about encoding written
human languages, but it could just as easily be applied to _any_
system of communication where there is some alphabet of symbols (such
as the instructions used in a program).

The Wikipedia page on Huffman Encoding is good. So is
[this thing by Alex Allain](http://www.cprogramming.com/tutorial/computersciencetheory/huffman.html). There's
really no shortage of good resources.

Project has following folder tree

.  
├── CMakeLists.txt  
├── CMakeLists.txt.in  
├── README.md  
├── app  
│   └── main.cpp  
├── build  
├── code  
│   ├── Huffman.cpp  
│   └── Huffman.h  
└── tests  
    └── test_Huffman.cpp  

CMakeLists.txt      : Ignore this file  
CMakeLists.txt.in   : Ignore this file  
README.md           : Readme file  
app\                : Application folder  
main.cpp            : Application main file for your personal tests. you can use this executable to debug your own classes.  
build\              : Build folder to build the project. your executables are gonna be here eventually.  
code\               : all your code should be in this folder.   
Huffman.cpp         : Huffman class source file  
Huffman.h           : Huffman class heather file  
tests\              : Tests folder  
test_Huffman.cpp    : Tests implemented for you / your personal tests  



For your final submission you submitt Huffman.cpp and Huffman.h files. Any other changes in other folders will be ignored in grading process but feel free to change them if you want to test/debug something.

## Where to Start
Open a terminal window in Jupytherhub(recommended) or your personal linux/mac machine (no windows platforms). First pull the this repository by
```console
jovyan@jupyter-yourcuid:~$ git clone https://github.com/Colorado-CompSci-Ugrad/Huffman.git
```
### If you want to use vscode environment
Then open the VScode app through JupyterHub and open Huffman folder from vscode.

Now your environment is set up, change Huffman.cpp and Huffman.h files and eventually press CTRL+SHIFT+B to compile your code.

Open a terminal window in vscode and go into ''build'' folder and run tests by
```console
jovyan@jupyter-yourcuid:~$ ./run_tests
```
debugger is also set up for you, go to debug tab on the left column and select **Run Tests** in drop-down menu and press the green play button to run the debugger. if you have any implementation in **app/main.cpp** you can also debug that code by first choosing **Run App** in drop-down menu and pressing green play button.

### If you want to use linux terminal for comilation
Make sure you have the dependecies installed (ckeck dependencies in this document)
go into your project folder, then build folder
```console
jovyan@jupyter-yourcuid:~$ cd Huffman
jovyan@jupyter-yourcuid:~$ cd build
```
run cmake to create make file for your project
```console
jovyan@jupyter-yourcuid:~$ cmake ..
```
run make to compile your code
```console
jovyan@jupyter-yourcuid:~$ make
```
once done, you can run tests by 
```console
jovyan@jupyter-yourcuid:~$ ./run_tests
```
app executable is also in this folder, you can run it by
```console
jovyan@jupyter-yourcuid:~$ ./run_app
```
you can debug in terminal using gdb

## Dependencies
you need **gcc** and **cmake** installed to be able to compile this code.

if you are using vscode environment in JupyterHub, you just need to make sure you have C/C++ extension installed.

## About This homework
Check Huffman.h file comments for detailed information for each function.

## A Note About Bits

Rather that encode strings as proper bits (low-level zero and one),
we're going to fake it using the strings "." and "^". This is mostly
because going all low-level requires a bit of explaination that is
really besides the point, and would just needlessly complicate things.

But do be aware that a proper implementation of any compression scheme
would likely go all the way down to a bit-level representation.

## What To Do For This Assignment

The header file documents everything for you to do. There aren't any
extra credit functions this time.

You'll likely need to create your own helper functions. In my solution
I made a recursive one to build the encoding table and just adding
`LEFT_CHAR` or `RIGHT_CHAR` to a string whenever I recursed.

## Tests

The tests are fairly well decoupled so you should be able to implement
your functions in whatever order you want, except for [build tree]
which depends on `load_queue`.

There is a unit test called [Full] that you can run manually from the
command line:

```
$ ./run_tests --gtest_filter=test_Huffman.Full
```

If you've done everything correctly you'll see some gratifying output
there, like this:

```
Using corpus from 'pkd.txt'
Original: These pretzels are making me thirsty
Encoded:  ^.^.^^.^^^^.....^^^.^...^^..^.^..^^^^^...^..^^.^^^^^..^....^...^^^^.^^^..^^.^^^^^...^^.^.^.^..^^.^........^^.^..^.^^..^^.^.^.^....^^.^..^^^^....^^^^^^^^^^.^^..^.^.^.^
Decoded:  These pretzels are making me thirsty
Compression ratio (higher is better): 1.73494
```

## Typedef for Priority Queue

There is a line that might look unfamiliar to you:

```
typedef priority_queue<shared_ptr<freq_info>, vector<shared_ptr<freq_info>>, freq_info> tree_queue;
```

This is called a typedef, and it is used to say "the thing on the left
can be written with the shorthand on the right". So everywhere you see
`tree_queue`, imagine it is expanded with that horrible, awful long
thing, the `priority_queue< ... blah ...>`.

Not only does this improve legibility, it also makes the coding job
easier. Remember Larry Wall's first virtue of great programmers...

## Maps

There are a few function signatures that call for maps. A `map` in C++
is a standard data structure that implements the Map abstract data
type, though (in my opinion) in a really awkward way.

Example usage:

```c++
m['c'] = 0; // map value 0 to key 'c'
cout << "value of c is: " << m['c]] << endl; // // read value associated with 'c'

// does m contain key 'c'?
bool present = m.find('c') != m.end();

// iterate over the key/value pairs. the 'auto' thing is a recent C++ keyword.
// the cbegin and cend are 'constant iterator' values.
for (auto it = m.cbegin(); it != m.cend(); ++it) {
  char k = (*it).first;
  int v =  (*it).second;
  // now do something with key k and value v
}
```

## Streams

It will also help you in a couple places to use string streams.

```c++
// be sure to include the header
#include <sstream>
#include <iostream>

using namespace std;

stringstream fake; // make a new string stream for a fake file
fake << "this is fake file data!"; 
char ch; // make a landing spot for reading characters
while (fake >> noskipws >> ch) { // read a character into ch, and don't skip whitespace.
  // do something with ch
}
cout << fake.str(); // this is how you get a string from a stringstream
```