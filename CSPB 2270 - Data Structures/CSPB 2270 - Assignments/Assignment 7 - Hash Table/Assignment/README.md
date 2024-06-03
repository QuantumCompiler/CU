# CSCI 2270 – Data Structures - Assignment 7
## Overview

In this assignment you will implement a Hash Table. 

### What is a hash table? 
[https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/](https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/)

Hashing is a technique that is used to uniquely identify a specific object from a group of similar objects. Some examples of how hashing is used in our lives include:

In universities, each student is assigned a unique roll number that can be used to retrieve information about them.
In libraries, each book is assigned a unique number that can be used to determine information about the book, such as its exact position in the library or the users it has been issued to etc.
In both these examples the students and books were hashed to a unique number.

Assume that you have an object and you want to assign a key to it to make searching easy. To store the key/value pair, you can use a simple array like a data structure where keys (integers) can be used directly as an index to store values. However, in cases where the keys are large and cannot be used directly as an index, you should use hashing.

In hashing, large keys are converted into small keys by using hash functions. The values are then stored in a data structure called hash table. The idea of hashing is to distribute entries (key/value pairs) uniformly across an array. Each element is assigned a key (converted key). By using that key you can access the element in O(1) time. Using the key, the algorithm (hash function) computes an index that suggests where an entry can be found or inserted.

Ideally, the hash function will assign each key to a unique bucket (index), but most hash table designs employ an imperfect hash function, which might cause hash collisions where the hash function generates the same index for more than one key. Such collisions are typically accommodated in some way.

Hashing is implemented in two steps:

1. An element is converted into an integer by using a hash function. This element can be used as an index to store the original element, which falls into the hash table.
2. The element is stored in the hash table where it can be quickly retrieved using hashed key.

```
          hash = hashfunc(key)
          index = hash % array_size
```

In this method, the hash is independent of the array size and it is then reduced to an index (a number between&nbsp;0 and array_size&nbsp;−&nbsp;1) by using the modulo operator (%).

## Objectives
* Work with hashing functions
* Realtime analysis of data structure capacity
* Dynamic resizing of a data structure
<hr>

## Where to Start
After having accepted your assignment in GitHub Classroom, _clone_ your private repository to your development environment.  We recommend that you use JupyterHub as your coding environment.

You will need to run ```cmake``` from within the _build_ directory to create the rules for making the applications.  Next, run ```make``` to use those rules to actually build the executable from the source code.

There will be a local executable created that will localay run the same tests that will be used to grade your assignment.

Modify the given source code to provide the features described both in the document below and within the code.

## Hash Table
In this assignment you will implement a Hash Class.

Project has following folder tree:
```
.  
├── CMakeLists.txt  
├── CMakeLists.txt.in  
├── README.md  
├── app  
│   └── main.cpp  
├── build  
├── code  
│   ├── Hash.cpp  
│   └── Hash.h  
└── tests  
    └── test_Hash.cpp  
```

| File | Descrition |
|---|---|
| CMakeLists.txt      | Ignore this file - rules to build the Makefile for this project (used by cmake)|
| CMakeLists.txt.in   | Ignore this file - more rules to build the Makefile for this project (used by cmake) |
| __README.md__           | __Readme file you are viewing here__ |
| app\                | Application folder  
| &nbsp;&nbsp;&nbsp;main.cpp            | Application main file for your personal tests. you  can use this executable to debug your own classes.  | 
| build\              | Build folder to build the project. your executables are gonna be here eventually.  |
| code\               | all your code should be in this folder.  |
| &nbsp;&nbsp;&nbsp;Hash.cpp      | Hash class source file  |
| &nbsp;&nbsp;&nbsp;Hash.h        | Hash class heather file  |
| tests\              | Tests folder  |
| &nbsp;&nbsp;&nbsp;test_Hash.cpp | Tests implemented for you / your personal tests  |
<hr>

## About This Assignment

### We Provide you a Hashing Function
At the core of every Hash Table is the Hashing Function.  These functions should try to make sure that no two keys have the same hash value.  They should also make sure to distribute the hash values across all the possible values so you do not have collisions.  We have defined a hashing function for you.  It works well and you can complete the whole assignment by using that function.  But it may not be the best function you can create.   If you want to create your own hash function, see the reference in the code.

You must approach the assignment by developing an overall strategy before coding anything.
You must design how you are going to solve the problems.
You should create an algorithm for each problem solution (functions) and place that algorithm into your code as comments.
While creating the algorithms you may notice that there are repeated sub-problems in your algorithm.  These are prime candidates for helper functions.
Creating a careful plan of how you're going to work the problem, which functions need to be implemented first, 
what helper functions will be needed, will guide you to a successful assignment.
Once you have all these questions thought out, you can begin to implement and test your code.

I suggest that you begin testing your code by modifying the `main.cpp` code to make calls to your implementation.
Take a look at how the testing application creates the environment for a test of your program.
Create a known data structure format explicitly and use it test individual functions.
You should test each of these functions so that you know they will work in all conditions.
I strongly recommend writing tests for your helper functions before you even implement the functions themselves. This means you can write a function in the `main.cpp` file to call your helper functions to see if they return the correct values.

### Look at the unit tests
The unit tests that come along with the assignment are meant to be read. 
There are little hints strewn throughout them. 

### Look at the functions that are called in the unit tests
There is some code that would be useful in creating your own tests for this assignment.
Take a look at the code to test a hash table.  You can clone the code to explicitly test your own functions under different conditions.

Here is the main functions you will need to implement:
```
class Hash {
public:
  Hash();

  // deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~Hash();

  // InitTable creates and initializes a hash_table structure and
  // returns a pointer to it. see the hash_table documentation for
  // details on the fields and their expected default values.
  shared_ptr<hash_table> InitTable(unsigned int cap);

  // InitNode creates and initializes a hash_node that will occupy a
  // hash table bucket. see the hash_node documentation for more info.
  shared_ptr<hash_node> InitNode(std::string key, unsigned int hashcode, std::string val);

  // SetKVP establishes a mapping between the given key and value pair
  // in the provided hash table. if the key (as identified by its hash
  // code) is already in the hash table, its value is potentially
  // updated. otherwise a new key/value pair is added to the hash table.
  //
  // on exit, the size and occupancy of the hash table is increased if a
  // new key/value pair was added.
  //
  // if there is no room in the hash table, return false. do not resize
  // the table.
  //
  // the return value should be true unless there was no room in the
  // hash table.
  bool SetKVP(shared_ptr<hash_table> tbl, std::string key, std::string value);

  // Load returns a load factor describing how 'full' the table
  // is. because we are using linear probing, which leaves 'deleted'
  // hash nodes sitting around, it is reasonable to use occupied divided
  // by capacity. you can alternately use size divided by capacity,
  // which is a more canonical definition of hashtable load. either will
  // work with the unit tests.
  float Load(shared_ptr<hash_table> tbl);

  // GetVal returns the value associated with the provded key in the
  // table, or the empty string "" if no such mapping exists (or if
  // there is a mapping but it is deleted).
  std::string GetVal(shared_ptr<hash_table> tbl, std::string key);

  // Contains returns true if the table has a non-deleted node whose
  // hashcode matches the given key's hashcode.
  bool Contains(shared_ptr<hash_table> tbl, std::string key);

  // Remove marks as 'deleted' any existing non-deleted hash_node with
  // the same hashcode as the provided key's hashcode. if it finds such
  // a hash node, it decrements the table's size (but not occupancy) and
  // returns true. it returns false otherwise.
  bool Remove(shared_ptr<hash_table> tbl, std::string key);

  // Resize creates a new underlying backing array (tbl->table) with the
  // provided new capacity, rehashes the existing backing array into the
  // new array. on exit, the hash table's fields and functions
  // accurately reflect the hash table's current state.
  void Resize(shared_ptr<hash_table> tbl, unsigned int new_capacity);

  // PrintTable is a debugging function. It is implemented for you.
  // Feel free use or to change this for your debugging needs. It is not
  // unit tested.
  //
  // It might help you understand how the hash_table and hash_node
  // structs might be used in your code.
  void PrintTable(shared_ptr<hash_table> tbl);

  // you can add add more public member variables and member functions here if you need

private:
  // you can add add more private member variables and member functions here if you need
};
```
