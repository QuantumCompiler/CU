# CSCI 2270 – Data Structures - Assignment 2
## Overview

In this assignment you'll implement a _Linked List_ data structure. 
In computer science  a linked list is a fundamental data structure and can be used to implement other common data structures.  It represents a linear collection of data items whose order is not given by their physical placement in memory.  An array keeps a linear set of items in order in contiguous memory order. Instead a _Linked List_ has each item in the list _point_ to the next. The _Linked List_ is a data structure consisting of a collection of nodes (objects) which together represent a sequence.

We've covered the data elements (_struct_) and the associated operations needed for a _Linked List_ in the video lectures.

## Objectives
* Use pointers to manage an ordered set of data objects
* Use shared pointers to safely manage memory
* Understand the complexity of inserting, deleting, and traversing a Linked List


## Where to Start
After having accepted your assignment in GitHub Classroom, _clone_ your private repository to your development environment.  We recommend that you use JupyterHub as your coding environment.

You will need to run ```cmake``` from within the _build_ directory to create the rules for making the applications.  Next, run ```make``` to use those rules to actually build the executable from the source code.

There will be a local executable created that will localay run the same tests that will be used to grade your assignment.

Modify the given source code to provide the features described both in the document below and within the code.

# LinkedList
In this assignment you will implement a Linked List Class

Project has following folder tree

```
.  
├── CMakeLists.txt  
├── CMakeLists.txt.in  
├── README.md  
├── app  
│   └── main.cpp  
├── build  
├── code  
│   ├── LinkedList.cpp  
│   └── LinkedList.h
└── tests  
    └── test_LinkedList.cpp
```
| File | Description |
|---|---|
| CMakeLists.txt      | Ignore this file - rules to build the Makefile for this project (used by cmake)|
| CMakeLists.txt.in   | Ignore this file - more rules to build the Makefile for this project (used by cmake) |
| __README.md__           | __Readme file you are viewing here__ |
| app\                | Application folder  
__main.cpp__            | __Application main file for your personal tests. you can use this executable to debug your own classes.__  |
| build\              | Build folder to build the project. your executables are gonna be here eventually.  |
| code\               | all your code should be in this folder.   
| __LinkedList.cpp__  | __LinkedList class source file__  |
| __LinkedList.h__    | __LinkedList class heather file__  |
| tests\              | Tests folder  |
| __test_LinkedList.cpp__ | __Tests implemented for you / your personal tests__  |

## About This homework

In this assignment you'll implement a linked list data
structure. We've covered the struct and associated operations in the
video lectures. Here's a summary:

* **LinkedList()** - LinkedList constructor, set top pointer to null when object is created.
* **~LinkedList()** - if not using smart pointers, make sure you remove heap memory here.
* **shared_ptr\<node> InitNode(int data)** - create a new node and return a shared pointer to it.
* **string Report()** - return a string representation of the list
* **void AppendData(int data)** - given data value, create a new node with that data and append to the end of list.
* **void Append(shared_ptr\<node> new_node)** - add given node to the end of the list.
* **void InsertData(int offset, int data)** - create a node with given data and insert to given offset position.
* **void Insert(int offset, shared_ptr\<node> new_node)** - insert given node into any spot in the list
* **void Remove(int offset)** - remove any index of list
* **int Size()** - return current number of nodes in the list.
* **bool Contains(int data)** - return true if the list contains a value
* **shared_ptr\<node> GetTop()** - Returns a shared_ptr for top of the list. (for testing purposes) (this is implemented for you)
* **void SetTop(shared_ptr\<node> top_ptr)** - Updates the Top pointer of the list to a new location given by top_ptr (for testing purposes) (this is implemented for you)

### Useful Tips
* to create dynamic memory of an struct (for example "node") you can do

```cpp
shared_ptr<node> mynode(new node);
```

* to re-assign a shared pointer to newly created memory do

```cpp
top_ptr_ = shared_ptr<node>(new node);
```

* to assign a shared pointer to null

```cpp
top_ptr_ = shared_ptr<node>(NULL);
```

* to check if shared_ptr is NULL or points to a valid address

```cpp
shared_ptr<node> a_pointer;
if(a_pointer){
    // this will run if a_pointer points to an address
} else {
    // this will run if a_pointer was NULL
}
```
# Completing the Assignment

1. After running the application, determine what is being tested for this assignment See the test cases in the code.
2. Make a modification to the code to __Pass__ the test. 
   * Each time you make changes to the code, be sure to save your edits to the code
   * ```make``` the application with the newly saved code
   * Test the resulting application
3. We suggest that you save your save the version of your code each time you get a test to pass. Make sure to save it both locally and on the GitHub server. 

4. Once you have solved one of the tests, _push_ your code to the server and access the Moodle page for the assignment.  Place your repository path into the field and sumbit to the Inginious auto-grader.
