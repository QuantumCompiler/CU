#ifndef NODE_H__
#define NODE_H__

#include <iostream>
#include <memory>

using namespace std;

// Node colors are described at the bottom of the file.
#define WHITE 1
#define GRAY 2
#define BLACK 3

class Node {
private:
  string data;
  int color;           // WHITE, GRAY, or BLACK.
  int discovery_time;  // clock value when the node was discovered by search.
  int completion_time; // clock value when node was completely finished.
  int rank;            // Number of steps from source node in a BFS. 0
                       // means it was the source node.
  shared_ptr<Node> predecessor; // The predecessor node in the spanning tree.

public:
  // Public Node members in this block are implemented for you.
  Node(string s);
  ~Node();
  string getData();
  void setData(string s);
  void setRank(int rank);

  // Have you ever wondered when you say cout << "hello world!" << endl; what <<
  // means? how is it implemented? these are operator methods that you can
  // define for your classes. Bellow is an example on how you can define <<
  // operator for this class and here we choose to define it as passing the data
  // of current node in string formate to the stream, which could later be like
  // Node mynode;
  // cout << mynode;
  // and that would print the data of the node.
  // you can define similar operators like +,-,* for you classes and define what
  // it means to sum two of this class's objects.
  friend std::ostream &operator<<(std::ostream &out, Node node);

  // Public Node methods to implement are below here.

  // clear sets the color to WHITE, the discovery/finish time and rank
  // to -1, and sets the predecessor to NULL.
  void clear();

  // setColor sets the 'color' of a node. Be sure to set the
  // appropriate time variable depending on what the new color is: set
  // discovery_time if the node is now GRAY, and completion_time if
  // the node is now BLACK. If it is now WHITE, this should be
  // equivalent to calling clear().
  void setColor(int search_color, int time);

  // getDiscoveryInformation gets the color, discovery time, and
  // finish time to 'color', 'disco_time', 'finish_time', and
  // 'bfs_rank' respectively.
  //
  // 'disco_time' and 'finish_time' are only meaningful if the search
  // was dfs (though there is no reason to not use these for debugging
  // purposes).
  //
  // 'bfs_rank' is only meaningful if bfs was the most recent search.
  //
  // By the way, these parameters are called 'output parameters', or
  // 'out params' because they serve as the output of the function.
  void getDiscoveryInformation(int &thecolor, int &disco_time, int &finish_time,
                               int &bfs_rank);

  // in this function if you start from "this" node and traverse the
  // predecessor list backwards, if you were able to reach the "other" node
  // then the function returns a true or returns false otherwise.
  // for example say we have a graph like A->B->C where 'B' is child of 'A'
  // and 'C' is child of 'B' then if we call C->isAncestor(A); the question
  // is asking "is A ancestor of C?" to find this out you start from C and
  // traverse the graph backwards and if you get to A then function returns
  // true. It is like searching through a linked list. You can do this
  // iteratively (with a cursor) or recursively by calling isAncestor on
  // non-null predecessors. Try it both ways and impress your friends.
  bool isAncestor(shared_ptr<Node> other);

  // Sets the predecessor node in the spanning tree. The predecessor
  // node was the node that we were exploring when we first discovered
  // a node (e.g. it was WHITE when we found it).
  void setPredecessor(shared_ptr<Node> other);
};

#endif // NODE_H__

/*

  Node color tells us if we have discovered a node, if we're in the
  middle of finishing a node, or if we've finished a node. They are:

  WHITE: Node has not yet been reached by the search.

  GRAY: Node has been reached by the search but is not yet complete.

  BLACK: Node has been completely explored.
 */
