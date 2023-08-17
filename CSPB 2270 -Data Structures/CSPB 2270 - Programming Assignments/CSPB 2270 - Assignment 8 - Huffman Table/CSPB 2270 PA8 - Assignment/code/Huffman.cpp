#include "Huffman.h"

// constructor, initialize class variables and pointers here if need.
Huffman::Huffman(){
  // your code here
}

//deconstructor,
Huffman::~Huffman(){
}

shared_ptr<freq_info> Huffman::CreateLeaf(char symbol, int count) {
  // TODO
  return shared_ptr<freq_info>(NULL);
}

shared_ptr<freq_info> Huffman::CombineNodes(shared_ptr<freq_info> left, shared_ptr<freq_info> right) {
  // TODO
  return shared_ptr<freq_info>(NULL);
}

void Huffman::IncrementLookup(map<char, int>& lookup, char symbol) {
  // TODO
}

void Huffman::LoadQueue(const map<char, int>& lookup, tree_queue& q) {
  // TODO
}

shared_ptr<freq_info> Huffman::BuildTree(tree_queue& q) {
  // TODO
  return NULL;
}

map<char, string> Huffman::BuildEncodingTable(shared_ptr<freq_info> root) {
  // TODO
  return map<char, string>();
}

string Huffman::Encode(map<char, string> enc_table, string input) {
  // TODO
  return "";
}

string Huffman::Decode(shared_ptr<freq_info> root, string input) {
  // TODO
  return "";
}