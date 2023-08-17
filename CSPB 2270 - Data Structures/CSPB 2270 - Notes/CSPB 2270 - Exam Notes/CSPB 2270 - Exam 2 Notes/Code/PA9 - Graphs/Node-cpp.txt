#include "Node.h"

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

/*  clear - Clears the private data members of a node to their default values
*   Input:
*     This function does not have any input parameters
*   Algorithm:
*     * Set all the respective data members to their default values
*   Output:
*     This function does not return a value, it resets all private data members of a node
*/
void Node::clear() {
  // Reset all private data members to their default values
  this->color = WHITE;
  this->discovery_time = -1;
  this->completion_time = -1;
  this->rank = -1;
  this->predecessor = nullptr;
}

/*  setColor - Sets the private data member "color" to "search_color" and respective time data members to "time"
*   Input:
*     search_color - Integer value that indicates the color that the private data member "color" is going to be set to
*     time - Integer value that indicates the time variable that the private data member "time" is going to be set to
*   Algorithm:
*     * Handle the case if the color is WHITE (see comments)
*     * Handle the case if the color is GRAY (see comments)
*     * Handle the case if the color is BLACK (see comments)
*   Output:
*     This function does not return a value, it modifies private data members of a node
*/
void Node::setColor(int search_color, int time) {
  // Determine which color is attempting to be set
  switch (search_color) {
    // If "search_color" is "WHITE", set the private data member "color" to "search_color" and call "clear()"
    case WHITE:
      this->color = search_color;
      this->clear();
      break;
    // If "search_color" is "GRAY", set the private data member "color" to "search_color" and "discovery_time" to "time"
    case GRAY:
      this->color = search_color;
      this->discovery_time = time;
      break;
    // If "search_color" is "BLACK", set the private data member "color" to "search_color" and "completion_time" to "time"
    case BLACK:
      this->color = search_color;
      this->completion_time = time;
      break;
    // Don't do anything otherwise
    default:
      break;
  }
}

/*  getDiscoveryInformation - Retrieves select private data members of a node
*   Input:
*     thecolor - Integer value that is passed by reference that represents the color of the node that is being retrieved
*     disco_time - Integer value that is passed by reference that represents the discovery time of the node that is being retrieved
*     finish_time - Integer value that is passed by reference that represents the completion time of the node that is being retrieved
*     bfs_rank - Integer value that is passed by reference that represents the rank of the node that is being retrieved
*   Algorithm:
*     * Set the input parameters of the node to that of input parameters
*   Output:
*     This function does not return any values, it modifies the input parameters of the function to that of the private data members of a node
*/
void Node::getDiscoveryInformation(int& thecolor, int& disco_time, int& finish_time, int& bfs_rank) {
  // Set the input parameters to that of the nodes private data member
  thecolor = this->color;
  disco_time = this->discovery_time;
  finish_time = this->completion_time;
  bfs_rank = this->rank;
}

/*  isAncestor - Checks to see if the node "other" is an ancestor of "this"
*   Input:
*     other - Smart pointer of object type Node. This is the node that we are checking if "other" is an ancestor of "this"
*   Algorithm:
*     * Check if "this" has the same memory address of "other", if so, return true
*     * Check if "this"'s predecessor is null, if so, return false
*     * Otherwise, recursively call isAncestor() on "this->predecessor" with "other"
*   Output:
*     This function returns a boolean value determining if "other" is an ancestor of "this"
*/
bool Node::isAncestor(shared_ptr<Node> other) {
  // Check if the node that is being checked against has the same memory address of "other"
  if (this == other.get()) {
    return true;
  }
  // Check if the current node doesn't have a predecessor node
  if (this->predecessor == nullptr) {
    return false;
  }
  // Recursive call on the predecessor of the current node
  return this->predecessor->isAncestor(other);
}

/*  setPredecessor - Sets the predecessor of "this" to that of "other"
*   Input:
*     other - Smart pointer of object type Node that is being set as the predecessor of "this"
*   Algorithm:
*     * Set the private data member "predecessor" to that of "other"
*   Output:
*     This function does not return a value, it modifies the private data member "predecessor" of "this"
*/
void Node::setPredecessor(shared_ptr<Node> other) {
  this->predecessor = other;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}
