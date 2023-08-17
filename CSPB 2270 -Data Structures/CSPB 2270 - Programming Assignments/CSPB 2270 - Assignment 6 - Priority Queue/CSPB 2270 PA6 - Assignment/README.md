# CSCI 2270 – Data Structures - Assignment 6

## Overview 
In this assignment you will be implementing a _Priority Queue_.
There are different kinds of queues in the world where people line up to get service.  A normal queue is where each individual is processed in the order they entered the queue (e.g. a queue at a bank waiting for a teller).   Other times there is a main queue and there is a special line for high priority people.  For example  consider the security checks, flight check-in, or baggage drop off queues at the airport.  For most of us, we get into the main queue and shuffle along until it is our turn.
However, there is also a line for high priority people who are placed at the front of the queue to be serviced quicker and more often.
They take priority over the rest of the people waiting in the main queue. 
We can recreate this type of queue in an abstract data type.

In computer science, a _priority queue_ is an abstract data-type similar to a regular queue or stack data structure in which each element additionally has a "priority" associated with it. In a priority queue, an element with high priority is served before an element with low priority. In some implementations, if two elements have the same priority, they are served according to the order in which they were enqueued; in other implementations ordering of elements with the same priority remains undefined.

In the lectures, we  have covered the different types of queues and the associated operations that can be performed on these data types.
The lectures have also covered data structures that can be used to implement these types of data structures.


## Objectives
* Use a low level data structure to implment a more complex data structure
* Understand the differences in behaviour of different types of queues


## Where to Start
After having accepted your assignment in GitHub Classroom, _clone_ your private repository to your development environment.  We recommend that you use JupyterHub as your coding environment.

You will need to run ```cmake``` from within the _build_ directory to create the rules for making the applications.  Next, run ```make``` to use those rules to actually build the executable from the source code.

There will be a local executable created that will localay run the same tests that will be used to grade your assignment.

Modify the given source code to provide the features described both in the document below and within the code.

# Priority Queue
In this assignment you will implement a Priority Queue Class.

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
│   ├── PriorityQueue.cpp  
│   └── PriorityQueue.h  
└── tests  
    └── test_PriorityQueue.cpp  
```


| File | Descrition |
|---|---|
| CMakeLists.txt      | Ignore this file - rules to build the Makefile for this project (used by cmake)|
| CMakeLists.txt.in   | Ignore this file - more rules to build the Makefile for this project (used by cmake) |
| __README.md__           | __Readme file you are viewing here__ |
| app\                | Application folder  
| &nbsp;&nbsp;&nbsp;main.cpp            | Application main file for your personal tests. ** You  can use this source file to debug your own classes. **  | 
| build\              | Build folder to build the project. your executables are gonna be here eventually.  |
| code\               | all your code should be in this folder.   
| &nbsp;&nbsp;&nbsp;PriorityQueue.cpp      | Priority Queue class source file  |
| &nbsp;&nbsp;&nbsp;PriorityQueue.h        | Priority Queue class header file  |
| tests\              | Tests folder  |
| &nbsp;&nbsp;&nbsp;test_PriorityQueue.cpp | Tests implemented for you / your personal tests  |

## About this Assignment
This programming assignment is about implementing  an abstract data type for a _Priority Queue_.  

***Binary Heap*** is generally preferred for priority queue implementation because _heaps_ provide better performance compared to solutions with _arrays_ or _linked list_.  We have covered _heaps_ in lectures and would suggest that you use one to implement your assignment.

| Time Complexity |       insert() |  remove() |  peek() |
| --- | --- | --- | --- |
| Binary Heap     |       O(log n) |  O(log n) |    O(1) |
| Linked List     |       O(n)     |  O(1)     |    O(1) |
| Arrays          |       O(1)     |  O(n)     |    O(n) |

However, we are not measuring the performance.
Your implementation can use any data structure to store the data. The `linked list` assignment is also a reasonable starting point for this assignment.
You will have to modify the node structure so it includes a priority value 
and you will need to keep the list organized. 


### How can your ADT be tested?

Since our testing framework has no knowledge about how your implementation is structured, 
it can only interact with your code via the _Priority Queue_ interface. 

A _Priority Queue_ has a simple set of operations:

- Insert element with some numeric priority
- Remove the highest priority element
- Peek at the highest priority element

These operations are defined in `PriorityQueue.h`.
There is also an empty structure `pq` in the `PriorityQueue.h` file, 
which you will populate with information needed to support the set of operations.

As a result of you defining the data of the structure, it is not possible to test your functions independently.
Testing `Insert`, `Peek` and `Remove` all require `InitPriorityQueue` to be working before the other functions can be used.
There are additional dependencies for our testing, that can be seen by examining the unit tests.
You should implement support routines to assit you in testing your code.  You can write your own tests, which can examine the data within the `pq` structure to determine if your code is working as you intended.

I recommend you implement your functions in this order:

1. `InitPriorityQueue`
2. `Peek`
3. `Insert`
4. `Remove`


You will implment the constructor and  destructor for the __PriorityQueue__ class, as well as the algorithms for the operations and any support methods needed to perform each of the operations.
Below is the class definition for __PriorityQueue__:
```
class PriorityQueue {
public:
    // constructor, you should set all values in array to zero
    PriorityQueue();

    //deconstructor, you don't need to add anything here since you are gonna use smart pointers
    ~PriorityQueue();

    // init_priority_queue allocates memory for a pq structure (which you
    // are responsble for defining above. It is
    // completely up to you how this should work.
    shared_ptr<pq> InitPriorityQueue();

    // insert adds the given text to the queue, using the specified
    // priority. If there is a tie, the given string should be placed at
    // the back of the group that it ties with, so all other strings with
    // this priority will be removed first.
    void Insert(shared_ptr<pq> queue, string text, float priority);

    // remove will access the highest priority element in the queue,
    // remove it from the queue, and return it. if the queue is empty it
    // should return the empty string.
    string Remove(shared_ptr<pq> queue);

    // ppek will access the highest priority element in the queue and
    // return it without modifying the queue. if the queue is empty it
    // should return the empty string.
    string Peek(shared_ptr<pq> queue);    

private:
    // you can add add more private member variables and member functions here if you need
};

```









