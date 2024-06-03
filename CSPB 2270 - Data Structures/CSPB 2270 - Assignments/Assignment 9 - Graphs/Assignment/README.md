# CSCI 2270 - Data Structures - Assignment 9 
## Overview 
In this assignment, you will implement an ADT graph and run Breadth-First Search and Depth-First Search algorithms. Graphs are versatile data structures that model relationships between things, so a generic graph data structure has nodes connected by edges. Adjacency matrices and adjacency lists are common ways to implement a graph. This week's video lectures cover various ways to implement graphs, design decisions regarding storing metadata, and common graph algorithms.  

## Objectives 
* Implement an adjacency list ADT graph 
* Utilize coupled metadata 
* Implement key graph algorithms including BFS and DFS

## Where to Start
After having accepted your assignment in GitHub Classroom, _clone_ your private repository to your development environment.  We recommend that you use JupyterHub as your coding environment.

You will need to run ```cmake``` from within the _build_ directory to create the rules for making the applications.  Next, run ```make``` to use those rules to actually build the executable from the source code.

There will be a local executable created that will localay run the same tests that will be used to grade your assignment.

Modify the given source code to provide the features described both in the document below and within the code.

# Graph 
In this assignment you will implement Graph, Edge, and Node classes. 
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
│   ├── Edge.cpp  
│   ├── Edge.h  
│   ├── Node.cpp  
│   ├── Node.h  
│   ├── Graphs.cpp  
│   └── Graphs.h  
└── tests  
    └── test_Graphs.cpp  

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
| __Node.cpp__  | __Node class source file__  |
| __Node.h__    | __Node class header file__  |
| __Edge.cpp__  | __Edge class source file__  |
| __Edge.h__    | __Edge class header file__  |
| __Graphs.cpp__  | __Graph class source file__  |
| __Graphs.h__    | __Graph class header file__  |
| tests\              | Tests folder  |
| __test_Graphs.cpp__ | __Tests implemented for you / your personal tests__  |

You will make changes to the Graphs.cpp, Node.cpp, and Edge.cpp files. Any other changes in other folders will be ignored in grading process but feel free to change them if you want to test/debug something.


## About This homework
Check Graphs.h, Edge.h, and Node.h file comments for detailed information for each function.
In this assignment, you'll implement a graph data structure, BFS, and DFS. 

Here's a summary of the **Edge class**:
* **void setType(int edge_type)** - set the edge type to the given value (see edge type #define statements)- this should only be one line long. 

Here's a summary of the **Graph class**:
* **void clear()** - resets nodes to WHITE, discovery, finish times, and rank to -1, edges to UNDISCOVERED_EDGE, graph clock to 0.
* **void dfs(shared_ptr\<node> start)** - runs a depth-first search from indicated start node, exploring all reachable nodes. 
* **void bfs(shared_ptr\<node> start)** - runs a breadth-first search starting from given node, exploring all reachable nodes. 
* **void bfs(shared_ptr\<node> start, shared_ptr\<node> finish)** - runs a breadth-first search like other version of BFS; this version stops when the target node is reached. 
	
Here's a summary of the **Node class**:
* **void clear()** - sets private variables to a default state. 
* **void setColor(int search_color, int time)** - sets the 'color' of a node according to its discovery state; be sure to set the appropriate time variable based on the new color. White is not(yet) discovered. Grey is discovered but not(yet) finished. Black is finished. 
* **void getDiscoveryInformation(int& thecolor, int& disco\_time, int& finish\_time, int& bfs_rank)** - uses four pass-by-reference variables for you to set to appropriate values. Technically returns void but used to access four state variables at one time.
* **bool isAncestor(shared_ptr\<node> other)** - gives information about the spanning tree formed during a DFS; an ancestor is a predecessor or any of our predecessor's predecessors.
* **void setPredecessor(shared_ptr\<node> other)** - gives informaation about the spanning tree formed during a DFS; the predecessor is the node we were on when our node was discovered. 
	

## Useful Tips 	   
This assignment is very detail-oriented, so refer to the lecture videos and slides as needed.

### Go in order

It is recommended that you implement the functions in the same order that
they appear in the test file.

### Pseudocode

This is the pseudocode to get you going. You'll need to augment it
(e.g. by setting ancestors, incrementing the clock, classifying edges,
and so on).

```
bfs(start):
  clear graph
  mark start gray
  Q = empty queue
  add start to Q
  while Q has stuff in it:
    v = popped element from Q
    mark v black
    visit v
    for each unmarked neighbor w
        mark w gray
        add w to Q
```

```
\# clear graph before initial call
dfs(node): 
  mark node gray
  visit node
  E = edges related to node
  for all edges e in E:
    a = end of e that isn't node
    if a is white:
      dfs(a)
  mark node black
```

### Two versions of bfs

There are two signatures for bfs. If you implement the two-arg version fully, then you can have the one-arg version simply call the two-arg version with a target that doesn't exist in the graph.

Remember: laziness is one of the three virtues of a great programmer.

### Use a queue, maybe

The header file includes vectors to store nodes and edges during a
search. You can use these if you like, or ignore them and use
something else instead.

One possible implementation: an iterative BFS using a queue (so,
`#include <queue>` atop implementation file), and a recursive DFS
using the `getAdjacentEdges` set.

### The auto keyword

The `auto` keyword can make life easier when iterating through a
collection. It leverages the compiler to 'figure out' what type would be
assigned for you (this only works for assignment, you cannot use `auto` for
example in function parameters). Also note that it is NOT like Python's dynamic
types, the type must still be known at compile time.

You can use `auto` to cleanly iterate over C++ collections:
```cpp
for (auto n : nodes) {
  // N right here will be a single node, one at a time.
}
```

A more correct way to handle iteration (which forces const and that the value is
iterated by reference resulting in zero-copy):
```cpp
for (const auto& n : nodes) {
  // N right here will be a single node, one at a time.
}
```

### Use `make_dot`

Check out the `tick` and `make_dot` functions provided for you
in the implementation file. If you call `tick` after each interesting
event (start, end, and every time you increment the clock) you can use
this to watch the progress of your dfs or bfs.

### Make helper functions

You'll likely want to create and use helper functions. The details are
up to you. For example, I made an `otherEnd` function that returned the
start/end of an edge that wasn't the node I was looking at.

Helpers aren't strictly necessary but they will make your life easier
and reduce the volume of code where bugs can lurk.

# Completing the Assignment

1. After running the application, determine what is being tested for this assignment See the test cases in the code.
2. Make a modification to the code to __Pass__ the test. 
   * Each time you make changes to the code, be sure to save your edits to the code
   * ```make``` the application with the newly saved code
   * Test the resulting application
3. We suggest that you save your save the version of your code each time you get a test to pass. Make sure to save it both locally and on the GitHub server. 

4. Once you have solved one of the tests, _push_ your code to the server and access the Moodle page for the assignment.  Place your repository path into the field and sumbit to the Inginious auto-grader.
