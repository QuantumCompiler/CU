# CSCI 2270 – Data Structures - Assignment 4
## Overview

In this assignment you'll implement a _Sorting_ algorithms. 
In computer science having your data in sorted order can effect the speed at which information can be found within the data or in adding new data. Sorting is a fundamental procedure used throughout Computer Science.

We've covered the vector data type and the associated operations that can be performed.  Your sorting algorithms will be given a vector of data elements that need to be sorted.  The ending vector will have all elements in non-descending order.  Non-descending means that the next value in the vector is always greater than or equal to this value.  

The different algorithms have been covered in video lectures.  Now you need to implment each of the algorithms to perform the sorting of the vector data.  You can access the vector as if it is an array of values.  Your mission is to rearrange the position of the values so they are in the correctly sorted order using quick sort, bubble sort, and merge sort, plus one other algorithm.


## Objectives
* Implement different sorting algorithms for sorting data 
* Manage the data within previously defined data structures
* Understand the complexity of moving and traversing the data


## Where to Start
After having accepted your assignment in GitHub Classroom, _clone_ your private repository to your development environment.  We recommend that you use JupyterHub as your coding environment.

You will need to run ```cmake``` from within the _build_ directory to create the rules for making the applications.  Next, run ```make``` to use those rules to actually build the executable from the source code.

There will be a local executable created that will localay run the same tests that will be used to grade your assignment.

Modify the given source code to provide the features described both in the document below and within the code.

# Sorting
In this assignment you will implement a Sorting Class.

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
│   ├── Sorting.cpp  
│   └── Sorting.h  
└── tests  
    └── test_Sorting.cpp  
```


| File | Descrition |
|---|---|
| CMakeLists.txt      | Ignore this file - rules to build the Makefile for this project (used by cmake)|
| CMakeLists.txt.in   | Ignore this file - more rules to build the Makefile for this project (used by cmake) |
| __README.md__           | __Readme file you are viewing here__ |
| app\                | Application folder  
| &nbsp;&nbsp;&nbsp;main.cpp            | Application main file for your personal tests. you  can use this executable to debug your own classes.  | 
| build\              | Build folder to build the project. your executables are gonna be here eventually.  |
| code\               | all your code should be in this folder.   
| &nbsp;&nbsp;&nbsp;Sorting.cpp      | Sorting class source file  |
| &nbsp;&nbsp;&nbsp;Sorting.h        | Sorting class heather file  |
| tests\              | Tests folder  |
| &nbsp;&nbsp;&nbsp;test_BST.cpp | Tests implemented for you / your personal tests  |

## About This homework

In this assignment you'll implement a 4 different sorting algorithms.  
We've covered the sorting algorithms and the associated operations needed to move the data  in the video lectures.

You will implment the constructor and  destructor for the __Sorting__ class, as well as the algorithm and support methods needed to perform each of the sorting algorithm.
Here is the class definition for ___Sorting___:

```
class Sorting {
public:
  // constructor, initialize class variables and pointers here if need.
  Sorting();

  // deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~Sorting();

  // quicksort is the entry point for the quicksort routine. It should
  // use the quicksort_partition function. It is also recursive, so you
  // will call quicksort from inside the quicksort function.
  // 
  // data: The input is a vector of integers. You can use this in a very
  // similar manner to arrays, but without a lot of the pointer
  // brain-damage. Note that the ampersand in front of the parameter
  // name indicates this is passed by _reference_, which means whatever
  // you do to this vector inside the quicksort function will be visible
  // outside as well.
  //
  // low_idx and high_idx: these are the current indices for the
  // quicksort algorithm, and are normal pass-by-value parameters. Both
  // of these indices are inclusive: they refer to an addressable
  // element of the data vector.
  void quicksort(vector<int>& data, int low_idx, int high_idx);

  // quicksort_partition is the helper function for quicksort. Input
  // parameters have same semantics as for quicksort.
  //
  // The pivot index is returned.
  int quicksort_partition(vector<int>& data, int low_idx, int high_idx);

  // bubblesort is probably the easiest sorting algorithm to conceive
  // of. It is unfortunately not all that fast. Here's your chance to
  // write really inefficient code! There are no related helper
  // functions. 
  void bubblesort(vector<int>& data);

  // mergesort is another classic O(n log n) sorting algorithm. This
  // uses the helper function 'merge'.
  void mergesort(vector<int>& data);

  // mystery_sort is any other sorting function that you choose to
  // implement. You may write any additional sorting function you wish,
  // and call it 'mystery_sort'.
  // 
  // See http://en.wikipedia.org/wiki/Sorting_algorithm for a list.
  //
  // Only rules are: (1) it has to have the following signature, and the
  // calling code will expect 'data' to be in non-decreasing order when
  // it returns, and (2) you have to write something new---no relying on
  // the other functions you've implemented.
  //
  // Also, write a comment somewhere near the top that explains which
  // sorting algorithm you're implementing.
  void mystery_sort(vector<int>& data);
  
  // you can add add more public member variables and member functions here if you need

private:
  // merge is the helper function for mergesort. It returns a vector
  // containing the merged contents of the two input vectors.
  // you must first define an empty vector and pass to result, once this
  // function returns, merged content will be in that vector (hence pass by reference).
  void merge(vector<int>& left, vector<int>& right, vector<int>& result);

  // you can add add more private member variables and member functions here if you need
};
```