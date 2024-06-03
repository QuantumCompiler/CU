#include "Edge.h"

Edge::Edge(shared_ptr<Node> n1, shared_ptr<Node> n2) {
  // DONE FOR YOU
  a = n1;
  b = n2;
}

Edge::~Edge() {
  // DONE FOR YOU
}


shared_ptr<Node> Edge::getStart() {
  // DONE FOR YOU
  return a;
}

shared_ptr<Node> Edge::getEnd() {
  // DONE FOR YOU
  return b;
}

int Edge::getType() {
  // DONE FOR YOU
  return type;
}

/*  setType - Sets the private data member "type" to that of the input parameter "edge_type"
*   Input:
*     edge_type - Integer value that defines the type of edge that is being set
*   Algorithm:
*     * Assign the private data member "type" to that of the input parameter "edge_type"
*   Output:
*     This function does not return a value, it modifies a the private data member of "type"
*/
void Edge::setType(int edge_type) {
  this->type = edge_type;
}

// overloading operator << lets you put an Edge object into an output
// stream.
ostream &operator << (std::ostream& out, Edge edge) {
  // DONE FOR YOU
  out << *edge.a << " -- " << *edge.b;
  return out;
}