#include "BST.h"

// constructor, initialize class variables and pointers here if need.
BST::BST(){
  // Your code here
}

//deconstructor,
BST::~BST(){
}

shared_ptr<bst_node> BST::InitNode(int data){
  // Your code here
  shared_ptr<bst_node> ret;  
  return ret;
}

void BST::Insert(shared_ptr<bst_node> new_node){
  // Your code here
}

void BST::InsertData(int data){
  // Your code here
}

void BST::Remove(int data){
  // Your code here
}

bool BST::Contains(shared_ptr<bst_node> subt, int data){
  // Your code here
  return false;
}

shared_ptr<bst_node> BST::GetNode(shared_ptr<bst_node> subt, int data){
  // Your code here
  return shared_ptr<bst_node>(NULL);
}

int BST::Size(shared_ptr<bst_node> subt){
  // Your code here
  return 0;
}

void BST::ToVector(shared_ptr<bst_node> subt, vector<int>& vec){
  // Your code here
  // eventually fill in vec ex. vec[0] = 1;
}

// This function is implemented for you
// Returns the root pointer
shared_ptr<bst_node> BST::GetRoot(){
  return root_ptr_;
}

// This function is implemented for you
// sets a given pointer as the top pointer
void BST::SetRoot(shared_ptr<bst_node> root_ptr){
  root_ptr_ = root_ptr;
}