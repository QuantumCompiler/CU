#ifndef HUFFMAN_H__
#define HUFFMAN_H__

#include <string>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

const string LEFT_CHAR = ".";
const string RIGHT_CHAR = "^";

// freq_info is a a node in the Huffman codec tree. It could be an
// internal node (is_leaf is false), or a leaf node with symbol data.
struct freq_info {
  char symbol;
  int count;
  shared_ptr<freq_info> left;
  shared_ptr<freq_info> right;
  bool is_leaf;
  // the operator here is what lets freq_info instances be used in a
  // priority queue without any other special effort. it returns true
  // if a->count is greater than b-> count. This establishes an
  // ordering.
  bool operator() (shared_ptr<freq_info> a, shared_ptr<freq_info> b) {
    return (a->count) > (b->count);
  }
};

// typedef'ed the priority queue type to simply 'tree_queue'.
//
// This is used to build the Huffman codec tree using a frequency
// lookup table.

// The template parameters (in the angle brackets) are:
//
// (1) shared_ptr<freq_info>: the type of element the pq manages.
//
// (2) vector<shared_ptr<freq_info>>: the type of backing store the pq uses.
//
// (3) freq_info: an object that can be used as a comparator, which
//     the pq uses to determine the order items are kept.
typedef priority_queue<shared_ptr<freq_info>, vector<shared_ptr<freq_info>>, freq_info> tree_queue;

class Huffman {
public:
  Huffman();

  // deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~Huffman();

  // CreateLeaf initializes a freq_info from heap memory and returns a
  // pointer to it. the returned object's symbol and count fields are
  // set to those provided; left and right child pointers are NULL, and
  // it is flagges as a leaf node.
  shared_ptr<freq_info> CreateLeaf(char symbol, int count);

  // CombineNodes initializes a freq_info from the heap and returns a
  // pointer to it. The new node has left and right pointers set to the
  // values given. The symbol data for this node is undefined (since it
  // is an internal node), and is_leaf is false.
  shared_ptr<freq_info> CombineNodes(shared_ptr<freq_info> left, shared_ptr<freq_info> right);

  // IncrementLookup will add one to the value associated with the
  // symbol, or if the symbol is not yet a key in the map, it will
  // create a mapping lookup[symbol] = 1.
  void IncrementLookup(map<char, int>& lookup, char symbol);

  // LoadQueue turns each key/value pair in the lookup table into a
  // freq_info pointer, and pushes it into the provided priority queue
  // (use q.push(node)).
  //
  // When accessing items from the queue, use top() to read it, and
  // pop() to remove it.
  //
  // The first item removed should form a left node, the second item
  // should form the right. That's for unit testing purposes.
  void LoadQueue(const map<char, int>& lookup, tree_queue& q);

  // BuildTree creates a Huffman codec tree using the values contained
  // in the provided priority queue. it returns a pointer to the root
  // node.
  shared_ptr<freq_info> BuildTree(tree_queue& q);

  // BuildEncodingTable creates a lookup table for the encoding
  // process. it maps each symbol in the Huffman codec tree to a string
  // composed of LEFT_CHAR and RIGHT_CHAR.
  //
  // root is the root node of a Huffman codec tree.
  map<char, string> BuildEncodingTable(shared_ptr<freq_info> root);

  // Encode returns an encoded string using the provided encoding lookup
  // table on the input string.
  string Encode(map<char, string> enc_table, string input);

  // Decode returns a decoded string using the provided Huffman codec
  // tree and input string.
  string Decode(shared_ptr<freq_info> root, string input);

  // you can add add more public member variables and member functions here if you need

private:
  // you can add add more private member variables and member functions here if you need
};

#endif  // HUFFMAN_H__