#include "Graph.h"

#include <iostream>
#include <sstream>

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<shared_ptr<Node>> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<shared_ptr<Edge>> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  edges.push_back(e);
}

void Graph::removeNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}

void Graph::removeEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin();
      it != edges.end(); 
      it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<shared_ptr<Edge>> Graph::getAdjacentEdges(shared_ptr<Node> n) {
  // DONE FOR YOU
  set<shared_ptr<Edge>> ret;
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) {
    shared_ptr<Edge> edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

/*  clear - Clears a graph of all nodes and edges
*   Input:
*     This function does not have any input parameters
*   Algorithm:
*     * Clear all nodes by iterating over them and calling "clear()" from Node.cpp
*     * Set all edges to "UNDISCOVERED_EDGE" by iterating over them and calling "setType()" from Edge.cpp
*     * Reset clock to zero
*   Output:
*     This function does not return a value, it modifies private data members of Graph.cpp
*/
void Graph::clear() {
  // Clear all nodes
  for (int i = 0; i < this->nodes.size(); i++) {
    this->nodes.at(i)->clear();
  }
  // Set all edges to "UNDISCOVERED_EDGE"
  for (int i = 0; i < this->edges.size(); i++) {
    this->edges.at(i)->setType(UNDISCOVERED_EDGE);
  }
  // Reset clock to zero
  this->clock = 0;
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

/*  dfs - Performs a depth first search on a graph
*   Input:
*     start - Smart pointer of object type Node that represents where the depth first search will begin
*   Algorithm:
*     * Clear the vector "search_edges"
*     * Set the current nodes color to GRAY
*     * Retrieve the current nodes information
*     * Retrieve the current nodes adjacent edges
*     * Iterate over the adjacent edges
*       * Get the end edge and set this as the adjacent node
*       * Retrieve the information of the adjacent node
*       * Set the predecessor of the adjacent node to that of start
*       * If the adjacent nodes color is WHITE
*         * Set the edge type to TREE_EDGE and recursively search the adjacent node
*       * IF the adjacent nodes color is GRAY
*         * Set the edge type to BACK_EDGE
*       * Otherwise, if adjacent nodes color is BLACK
*         * If the discovery time of adjacent node is greater than that of start, set the edge type to FORWARD_EDGE
*         * Otherwise, set the edge type to CROSS_EDGE
*     * Set the current nodes color to BLACK
*   Output:
*     This function does not return a value, it searches through a graph using depth first search
*/
void Graph::dfs(shared_ptr<Node> start) {
  // Clear the search edges of the current node
  this->search_edges.clear();
  // Set the current node color to GRAY
  start->setColor(GRAY, this->clock++);
  // Retrieve the information of the current node
  int strColor, strDiscoTime, strCompTime, strRank;
  start->getDiscoveryInformation(strColor, strDiscoTime, strCompTime, strRank);
  // Retrieve the current adjacent edges of the current node
  set<shared_ptr<Edge>> adjacent_edges = getAdjacentEdges(start);
  // Iterate over the adjacent edges 
  for (const auto& edge : adjacent_edges) {
    // Retrieve the adjacent node as the end of the current node
    shared_ptr<Node> adjacentNode = edge->getEnd();
    // Retrieve the information of the adjacent node
    int adjColor, adjDiscoTime, adjCompTime, rank;
    adjacentNode->getDiscoveryInformation(adjColor, adjDiscoTime, adjCompTime, rank);
    // Set the predecessor of the adjacent node to start
    adjacentNode->setPredecessor(start);
    // If the adjacent node's color is WHITE, set the edge type to TREE_EDGE and recursively search that node
    if (adjColor == WHITE) {
      edge->setType(TREE_EDGE);
      dfs(adjacentNode);
    }
    // If the adjacent node's color is GRAY, set the edge type to BACK_EDGE
    else if (adjColor == GRAY) {
      edge->setType(BACK_EDGE);
    }
    // Otherwise
    else {
      // If the discovery time of adjacent node is greater than that of start, set the edge type to FORWARD_EDGE
      if (adjDiscoTime > strDiscoTime) {
        edge->setType(FORWARD_EDGE);
      }
      // Otherwise, set the edge type to CROSS_EDGE
      else {
        edge->setType(CROSS_EDGE);
      }
    }
  }
  // Set the color of the node to BLACK
  start->setColor(BLACK, this->clock++);
}

/*  bfs - Performs a breadth first search on a graph
*   Input:
*     start - Smart pointer of object type Node that represents the start of our search in the graph
*   Algorithm:
*     * Set the start nodes color to GRAY and its rank to zero
*     * Retrieve the informaiton of the start node
*     * Create a queue for nodes to be stored in
*     * While the queue is not empty
*       * Pop the front node out of the queue
*       * Set the color of the node to BLACK
*       * Retrieve the information of the node
*       * Retrieve the adjacent edges of the node
*       * Iterate over the adjacent edges of the node
*         * Retrieve the end edges node and call this adjacent node
*         * Retrieve the information of the adjacent node
*         * If the adjacent nodes color is WHITE
*           * Set the edge type to TREE_EDGE
*           * Set the color to GRAY
*           * Push this node to the queue
*           * Increment the rank of the adjacent node
*   Output:
*     This function does not return a value, it performs a breadth first search on a graph
*/
void Graph::bfs(shared_ptr<Node> start) {
  // Set the start nodes color to GRAY and the rank to 0
  start->setColor(GRAY, this->clock++);
  start->setRank(0);
  // Retrieve the information of the current node
  int strColor, strDiscoTime, strCompTime, strRank;
  start->getDiscoveryInformation(strColor, strDiscoTime, strCompTime, strRank);
  // Create a queue for nodes to be stored in
  queue<shared_ptr<Node>> Q;
  Q.push(start);
  // While the queue is not empty
  while (!Q.empty()) {
    // Pop the top node out of the front of the queue
    shared_ptr<Node> poppedNode = Q.front();
    Q.pop();
    // Set the color of the node to BLACK
    poppedNode->setColor(BLACK, this->clock++);
    // Retrieve the information for the node
    int popColor, popDiscoTime, popCompTime, popRank;
    poppedNode->getDiscoveryInformation(popColor, popDiscoTime, popCompTime, popRank);
    // Retrieve the adjacent edges of the node
    set<shared_ptr<Edge>> adjacent_edges = getAdjacentEdges(poppedNode);
    // Iterate over the adjacent edges of the popped node
    for (const auto& edge : adjacent_edges) {
      // Retrieve the end node and call this adjacent node
      shared_ptr<Node> adjacentNode = edge->getEnd();
      // Retrieve the information of the adjacent node
      int adjColor, adjDiscoTime, adjCompTime, adjRank;
      adjacentNode->getDiscoveryInformation(adjColor, adjDiscoTime, adjCompTime, adjRank);
      // If the adjacent nodes color is white
      if (adjColor == WHITE) {
        // Set the edge type to "TREE_EDGE", set the color to "GRAY", push to the queue and increment the rank
        edge->setType(TREE_EDGE);
        adjacentNode->setColor(GRAY, this->clock++);
        Q.push(adjacentNode);
        adjacentNode->setRank(popRank + 1);
      }
    }
  }
}

/*  bfs - Performs a breadth first search on a graph
*   Input:
*     start - Smart pointer of object type Node that represents the start of our search in the graph
*   Algorithm:
*     * Set the start nodes color to GRAY and its rank to zero
*     * Retrieve the informaiton of the start node
*     * Retrieve the information of the finish node
*     * Create a queue for nodes to be stored in
*     * Create a boolean to flag if the current node is not the finish
*     * While the queue is not empty and the node is not the end
*       * Pop the front node out of the queue
*       * Set the color of the node to BLACK
*       * Retrieve the information of the node
*       * Retrieve the adjacent edges of the node
*       * Iterate over the adjacent edges of the node
*         * Retrieve the end edges node and call this adjacent node
*         * Retrieve the information of the adjacent node
*         * If the adjacent nodes color is WHITE
*           * Set the edge type to TREE_EDGE
*           * Set the color to GRAY
*           * Push this node to the queue
*           * Increment the rank of the adjacent node
*           * Check if the adjacent node is the finish node
*             * If it is, set finished to true and set the rank to 1 if the graph is undirected
*   Output:
*     This function does not return a value, it performs a breadth first search on a graph
*/
void Graph::bfs(shared_ptr<Node> start, shared_ptr<Node> finish) {
  // Set the start nodes color to GRAY and the rank to 0
  start->setColor(GRAY, this->clock++);
  start->setRank(0);
  finish->setRank(0);
  // Retrieve the information of the start node
  int strColor, strDiscoTime, strCompTime, strRank;
  start->getDiscoveryInformation(strColor, strDiscoTime, strCompTime, strRank);
  // Retrieve the information of the finish node
  int finColor, finDiscoTime, finCompTime, finRank;
  finish->getDiscoveryInformation(finColor, finDiscoTime, finCompTime, finRank);
  // Create a queue for nodes to be stored in
  queue<shared_ptr<Node>> Q;
  Q.push(start);
  // Create a boolean to flag if the current node is not the finish
  bool finished = false;
  // While the queue is not empty and the node is not the end
  while (!Q.empty() && !finished) {
    // Pop the top node out of the front of the queue
    shared_ptr<Node> poppedNode = Q.front();
    Q.pop();
    // Set the color of the node to BLACK
    poppedNode->setColor(BLACK, this->clock++);
    // Retrieve the information for the node
    int popColor, popDiscoTime, popCompTime, popRank;
    poppedNode->getDiscoveryInformation(popColor, popDiscoTime, popCompTime, popRank);
    // Retrieve the adjacent edges of the node
    set<shared_ptr<Edge>> adjacent_edges = getAdjacentEdges(poppedNode);
    // Iterate over the adjacent edges of the popped node
    for (const auto& edge : adjacent_edges) {
      // Retrieve the end node and call this adjacent node
      shared_ptr<Node> adjacentNode = edge->getEnd();
      // Retrieve the information of the adjacent node
      int adjColor, adjDiscoTime, adjCompTime, adjRank;
      adjacentNode->getDiscoveryInformation(adjColor, adjDiscoTime, adjCompTime, adjRank);
      // If the adjacent nodes color is white
      if (adjColor == WHITE) {
        // Set the edge type to "TREE_EDGE", set the color to "GRAY", push to the queue and increment the rank
        edge->setType(TREE_EDGE);
        adjacentNode->setColor(GRAY, this->clock++);
        Q.push(adjacentNode);
        adjacentNode->setRank(popRank + 1);
        // Check if the adjacent node is the finish node
        if (adjacentNode == finish) {
          finished = true;
          // If graph is undirected, set rank to 1
          if (this->directed == false){
            finish->setRank(1);
          }
          break;
        }
      }
    }
  }
}


// overloading operator << lets you put a Graph object into an output
// stream.
ostream &operator << (ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<shared_ptr<Node>>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    shared_ptr<Node> n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<shared_ptr<Edge>>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    shared_ptr<Edge> e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness. 
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<shared_ptr<Node>> nodes = g->getNodes();
  vector<shared_ptr<Edge>> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    shared_ptr<Node> n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }
  
  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    shared_ptr<Edge> e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}