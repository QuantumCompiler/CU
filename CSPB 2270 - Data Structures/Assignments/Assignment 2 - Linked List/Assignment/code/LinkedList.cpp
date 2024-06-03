#include "LinkedList.h"

// constructor, initialize class variables and pointers here if need.
LinkedList::LinkedList(){
  // Your code here
}

//deconstructor,
LinkedList::~LinkedList(){
}


shared_ptr<node> LinkedList::InitNode(int data){
  shared_ptr<node> ret(new node);
  // Your code here
  return ret;
}

string LinkedList::Report(){
  string ret;
  // Your code here
  return ret;
}

void LinkedList::AppendData(int data){
  // Your code here
}

void LinkedList::Append(shared_ptr<node> new_node){
  // Your code here
}

void LinkedList::InsertData(int offset, int data){
  // Your code here
}

void LinkedList::Insert(int offset, shared_ptr<node> new_node){
  // Your code here
}

void LinkedList::Remove(int offset){
  // Your code here
}

int LinkedList::Size(){
  int ret;
  // Your code here
  return ret;
}

bool LinkedList::Contains(int data){
  bool ret;
  // Your code here
  return ret;
}

// This function is implemented for you
// It returns the top pointer
shared_ptr<node> LinkedList::GetTop(){
  return top_ptr_;
}

// This function is implemented for you
// It sets a given pointer as the top pointer
void LinkedList::SetTop(shared_ptr<node> top_ptr){
  top_ptr_ = top_ptr;
}
