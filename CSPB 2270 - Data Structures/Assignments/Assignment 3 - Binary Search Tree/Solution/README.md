# CSCI 2270 – Data Structures - Assignment 3
## Overview
In this assignment you'll implement a _Binary Search Tree_ data structure.
A Linked List is dynamic in length, but it is a single sequence that must be linearly searched for items in the list.  If we want to increase our abiltity to lookup items quickly with the set of data we have stored, we must make a more complex data structure.  The _Binary Search Tree_ is a data structure that lets us cut the amount of data to be searched with each comparison se make.  Each _node_ of the tree stores some data and has a pointer to data that is before it, and another pointer to data that follows the node's data.  Managing the pointers for a node when inserting, deleting, and traversing is more complex than a singly or doubly linked lists.

We've covered the data elements (_struct_) and the associated operations needed for a _Binary Search Tree_ in the video lectures.

## Where to Start
After having accepted your assignment in GitHub Classroom, _clone_ your private repository to your development environment.  We recommend that you use JupyterHub as your coding environment.

You will need to run ```cmake``` from within the _build_ directory to create the rules for making the applications.  Next, run ```make``` to use those rules to actually build the executable from the source code.

There will be a local executable created that will localay run the same tests that will be used to grade your assignment.

Modify the given source code to provide the features described both in the document below and within the code.

## BinarySearchTree (BST)
In this assignment you will implement a Binary Search Tree

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
│   ├── BST.cpp  
│   └── BST.h  
└── tests  
    └── test_BST.cpp  
```

| File | Descrition |
|---|---|
| CMakeLists.txt      | Ignore this file - rules to build the Makefile for this project (used by cmake)|
| CMakeLists.txt.in   | Ignore this file - more rules to build the Makefile for this project (used by cmake) |
| __README.md__           | __Readme file you are viewing here__ |
| app\                | Application folder  
| main.cpp            | Application main file for your personal tests. you  can use this executable to debug your own classes.  | 
| build\              | Build folder to build the project. your executables are gonna be here eventually.  |
| code\               | all your code should be in this folder.   
| BST.cpp      | BST class source file  |
| BST.h        | BST class heather file  |
| tests\              : Tests folder  |
| test_BST.cpp | Tests implemented for you / your personal tests  |




## About This homework

In this assignment you'll implement a _Binary Search Tree_ data structure.
We've covered the data elements (_struct_) and the associated operations needed for a _Binary Search Tree_ in the video lectures.

You will implment the constructor, destructor, and support methods to manage the tree nodes and their pointers.
Here is the class definition for ___BST___:

```
#ifndef BST_H__
#define BST_H__

#include <string>
#include <memory>
#include <vector>

using namespace std;

  // bst_node is the binary search tree node structure.
  struct bst_node {
    int data;
    shared_ptr<bst_node> left;
    shared_ptr<bst_node> right;
  };

  // Binary search tree:
  //
  // From any subtree node t, the left subtree's data values must be
  // less than t's data value. The right subtree's data values must be
  // greater than or equal to t's data value.
class BST {
public:
  // constructor, initialize class variables and pointers here if need.
  // Initially set root_ptr_ to a null shared_ptr of node
  BST();

  // deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~BST();

  // init_node initializes a new bst_node from the heap using the given
  // data, and two NULL children, and returns a pointer to it.
  shared_ptr<bst_node> InitNode(int data);

  // insert places the new_node in a proper location in the tree
  // while obeying the invariant. On return, root_ptr_
  // points to the root of the tree.
  void Insert(shared_ptr<bst_node> new_node);

  // insertData creates a new node with the given data value and
  // inserts it similarly to insert().
  void InsertData(int data);

  // remove removes a node from the tree whose data value matches the
  // input. If no node in the tree contains the given data, this function
  // has no effect.
  void Remove(int data);

  // contains returns true if any node in the subtree pointed to by t
  // contains the given data value, false otherwise.
  bool Contains(shared_ptr<bst_node> subt, int data);

  // get_node searches through the subtree pointed to by subt for a node that
  // contains the given data value. If such a node is found, a pointer
  // to it is returned. Otherwise this function returns NULL.
  shared_ptr<bst_node> GetNode(shared_ptr<bst_node> subt, int data);

  // size returns the number of nodes in the subtree pointed to by subt. If
  // the tree is empty (t is NULL), it returns zero.
  int Size(shared_ptr<bst_node> subt);

  // ToVector fills an integer vector to reflect the contents of the
  // subtree pointed to by subt. Size of the filled array will be the same as the
  // subtree's size (found with the size() function), and the order of
  // the array elements are the same that is found during an INORDER
  // traversal of the subtree.
  //
  // Note: the vector "vec" will be passed to this function as an empty vector
  // and you can add elements to it by using push_back() member function of vector
  // class. for example to add an integer stored at variable "a" you can do vec.push_back(a);
  // vector<int> is a cpp class which defines a vector of type int.
  // for example one can define an empty vector like:
  // vector<int> my_vec;
  // and pass that vector by reference to ToArray function to be filled like:
  // ToVector(somesharedpointer, my_vec)
  void ToVector(shared_ptr<bst_node> subt, vector<int>& vec);

  // This function is implemented for you
  // Returns the root pointer
  shared_ptr<bst_node> GetRoot();

  // This function is implemented for you
  // sets a given pointer as the top pointer
  void SetRoot(shared_ptr<bst_node> root_ptr);

  // you can add add more public member variables and member functions here if you need

private:
  // this pointer always will point to root of the tree
  shared_ptr<bst_node> root_ptr_;
  // you can add add more private member variables and member functions here if you need
};

#endif  // BST_H__

```
