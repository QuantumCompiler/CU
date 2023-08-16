#ifndef EDGE_H__
#define EDGE_H__

#include <memory>
#include "Node.h"

using namespace std;

// Edge types are described at the bottom of the file.
#define UNDISCOVERED_EDGE 9
#define TREE_EDGE 10
#define BACK_EDGE 11
#define FORWARD_EDGE 12
#define CROSS_EDGE 13

class Edge {
private:
  shared_ptr<Node> a;  // start node
  shared_ptr<Node> b;  // end node
  int type; // one of the edge types defined in graph.hpp
public:
  Edge(shared_ptr<Node> n1, shared_ptr<Node> n2);
  ~Edge();
  int getType();
  shared_ptr<Node> getStart();
  shared_ptr<Node> getEnd();
  void setWeight(float val);
  friend std::ostream &operator << (std::ostream& out, Edge edge);

  // Set the edge type to the given value (see edge type #define
  // statements).
  void setType(int edge_type);
  
};

#endif  // EDGE

/*
  Edge type tells us information about how the path was discovered
  during a depth-first search, and it also might give us valuable
  information about the shape of the graph. There are four kinds of
  edges, though it is not necessary to use all of them all of the
  time. They are:

  TREE: A tree edge from A to B indicates that B was discovered via A.

  BACK: A back edge from C to A indicates that A was discovered before
  C, and C was discovered while A was still being explored.

  FORWARD: A forward edge from A to C indicates that C was completely
  examined when we found it, and A is an ancestor of C in the DFS
  spanning tree.

  CROSS: A cross edge from A to C indicates the C was completely
  examined when we found it, and A is NOT an ancestor of C in the DFS
  spanning tree.

  These edge types are summarized graphically at
  http://en.wikipedia.org/wiki/Depth-first_search and does a much
  better job than words can do.

  To determine edge types, you need to use both the discovery
  information (the color of the ending node) and the predecessor
  information (to distinguish between Cross and Forward edges).

  Tree edges are when the end node is white.

  Back edges are when the end node is gray.

  Forward and cross edges are when the end node is black. If the start
  node is an ancestor of the end node, it is a forward edge. Otherwise
  it is a cross edge.

 */