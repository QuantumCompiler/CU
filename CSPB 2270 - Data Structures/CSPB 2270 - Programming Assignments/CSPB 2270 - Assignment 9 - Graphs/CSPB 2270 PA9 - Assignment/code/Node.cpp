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

void Node::clear() {
  // TODO
}

void Node::setColor(int search_color, int time) {
  // TODO
}

void Node::getDiscoveryInformation(int& thecolor, int& disco_time, 
				   int& finish_time, int& bfs_rank) {
  // TODO
}

bool Node::isAncestor(shared_ptr<Node> other) {
  // TODO
  return false;
}

void Node::setPredecessor(shared_ptr<Node> other) {
  // TODO
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}
