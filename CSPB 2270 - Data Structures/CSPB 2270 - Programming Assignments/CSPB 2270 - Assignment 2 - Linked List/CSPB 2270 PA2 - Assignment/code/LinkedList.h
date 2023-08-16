#ifndef LINKEDLIST_H__
#define LINKEDLIST_H__

#include <string>
#include <memory>

using namespace std;

struct node {
  int data;               // data: the value of this node
  shared_ptr<node> next;  // next: pointer to the next node in the list, or NULL if this is the last node.
};

// Linked List Invariant: following the 'next' links in a linked list
// node must eventually lead to a NULL reference signifying the end of
// the list. (E.g. no circular references are allowed.)
class LinkedList {
public:
  // constructor, initialize class variables and pointers here if need.
  // Initially set top pointer to a null shared_ptr of node
  LinkedList();

  //deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~LinkedList();

  // init_node creates a new node structure from heap memory. It points
  // to NULL and holds the provided integer. The function returns a
  // pointer to that new node.
  shared_ptr<node> InitNode(int data);

  // report creates a space-separated string representing the contents
  // of the list, in the same order they are found beginning from the
  // top of the list. return that string object.  For example, this
  // might return "" (the empty string) if the list is empty, or it
  // might return "1 7 3 " (note the space at the end).
  string Report();

  // append_data adds a node onto the end of the list pointed to by
  // top. the resulting list is one element longer, and the newly
  // appended node has the given data value. consider using the 'append'
  // function to help.
  void AppendData(int data);

  // append is the same as append_data, except we're adding a node, rather
  // than a value. 
  void Append(shared_ptr<node> new_node);

  // insert_data inserts a new node that contains the given data value,
  // such that the new node occupies the offset indicated. Any nodes
  // that were already in the list at that offset and beyond are shifted
  // down by one. For example if the list contains 23, 74, 93, and we
  // insert 42 at index 1, the resulting list should be 23, 42, 74, 93.
  //
  // If an offset is beyond the end of the list, this function should
  // have no effect.
  //
  // Inserting at the end of the list should have the same effect as
  // appending.
  void InsertData(int offset, int data);

  // insert is the same as insert_data, except we're inserting a node,
  // rather than a value.
  void Insert(int offset, shared_ptr<node> new_node);

  // remove removes the node indicated by the given offset and frees its
  // memory. For example if our list contains 23, 74, 93, and we remove
  // offset 1, the resulting list should then contain 23, 93.
  //
  // If an invalid offset is given (e.g. negative or beyond the end of
  // the list), this function has no effect.
  void Remove(int offset);

  // size returns the number of nodes in the linked list reachable by
  // head before (but not including) the terminating NULL link. E.g., an
  // empty list has size 0, a list with one item has size 1, etc.
  int Size();

  // contains returns true if the linked list pointed to by head
  // contains a node with the specified value, false otherwise.
  bool Contains(int data);

  // This function is implemented for you
  // Returns the top pointer
  shared_ptr<node> GetTop();

  // This function is implemented for you
  // sets a given pointer as the top pointer
  void SetTop(shared_ptr<node> top_ptr);

  // you can add more public member variables and member functions here if you need

private:
  shared_ptr<node> top_ptr_;

  // you can add add more private member variables and member functions here if you need
};

#endif  // LINKEDLIST_H__