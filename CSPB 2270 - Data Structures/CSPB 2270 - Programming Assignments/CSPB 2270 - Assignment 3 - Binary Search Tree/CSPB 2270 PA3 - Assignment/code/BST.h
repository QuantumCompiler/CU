#ifndef BST_H__
#define BST_H__

#include <string>
#include <memory>
#include <vector>

using namespace std;

  // bst_node is the binary search tree node structure.
  struct bst_node {
    int data;
    shared_ptr<bst_node> left;
    shared_ptr<bst_node> right;
  };

  // Binary search tree:
  //
  // From any subtree node t, the left subtree's data values must be
  // less than t's data value. The right subtree's data values must be
  // greater than or equal to t's data value.
class BST {
public:
  // constructor, initialize class variables and pointers here if need.
  // Initially set root_ptr_ to a null shared_ptr of node
  BST();

  // deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~BST();

  // init_node initializes a new bst_node from the heap using the given
  // data, and two NULL children, and returns a pointer to it.
  shared_ptr<bst_node> InitNode(int data);

  // insert places the new_node in a proper location in the tree
  // while obeying the invariant. On return, root_ptr_
  // points to the root of the tree.
  void Insert(shared_ptr<bst_node> new_node);

  // insertData creates a new node with the given data value and
  // inserts it similarly to insert().
  void InsertData(int data);

  // remove removes a node from the tree whose data value matches the
  // input. If no node in the tree contains the given data, this function
  // has no effect.
  void Remove(int data);

  // contains returns true if any node in the subtree pointed to by t
  // contains the given data value, false otherwise.
  bool Contains(shared_ptr<bst_node> subt, int data);

  // get_node searches through the subtree pointed to by subt for a node that
  // contains the given data value. If such a node is found, a pointer
  // to it is returned. Otherwise this function returns NULL.
  shared_ptr<bst_node> GetNode(shared_ptr<bst_node> subt, int data);

  // size returns the number of nodes in the subtree pointed to by subt. If
  // the tree is empty (t is NULL), it returns zero.
  int Size(shared_ptr<bst_node> subt);

  // ToVector fills an integer vector to reflect the contents of the
  // subtree pointed to by subt. Size of the filled array will be the same as the
  // subtree's size (found with the size() function), and the order of
  // the array elements are the same that is found during an INORDER
  // traversal of the subtree.
  //
  // Note: the vector "vec" will be passed to this function as an empty vector
  // and you can add elements to it by using push_back() member function of vector
  // class. for example to add an integer stored at variable "a" you can do vec.push_back(a);
  // vector<int> is a cpp class which defines a vector of type int.
  // for example one can define an empty vector like:
  // vector<int> my_vec;
  // and pass that vector by reference to ToArray function to be filled like:
  // ToVector(somesharedpointer, my_vec)
  void ToVector(shared_ptr<bst_node> subt, vector<int>& vec);

  // This function is implemented for you
  // Returns the root pointer
  shared_ptr<bst_node> GetRoot();

  // This function is implemented for you
  // sets a given pointer as the top pointer
  void SetRoot(shared_ptr<bst_node> root_ptr);

  // you can add add more public member variables and member functions here if you need

private:
  // this pointer always will point to root of the tree
  shared_ptr<bst_node> root_ptr_;
  // you can add add more private member variables and member functions here if you need
};

#endif  // BST_H__
