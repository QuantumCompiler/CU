#include "BST.h"

/*  Constructor - This constructor initializes the root of our tree to be a "nullptr"
*
*/
BST::BST(){
  SetRoot(nullptr);
}

//deconstructor,
BST::~BST(){
}

/*  InitNode - This function creates a node of a BST
*   Input:
*     data - Integer value that the data member of bst_node "data" is to be set to
*   Algorithm:
*     * Create a new smart pointer named "ret" to represent a new BST node (bst_node)
*     * Assign the input parameter "data" to the data member "data" of "ret" using the member access operator
*     * Initialize the left and right child pointers of "ret" to a null value with "nullptr"
*   Output:
*     ret - A smart pointer pointing to the newly created BST node (bst_node)
*/
shared_ptr<bst_node> BST::InitNode(int data){
  shared_ptr<bst_node> ret(new bst_node());
  ret->data = data;
  ret->left = nullptr;
  ret->right = nullptr;
  return ret;
}

/*  Insert - This function inserts a node into a BST
*   Input:
*     new_node - A smart pointer that represents a node in a BST
*   Algorithm:
*     * First, check if the root of our BST is null
*       * If it is, then assign the smart pointer "new_node" to the root of our BST using SetRoot()
*       * If it is not, then proceed to the next step
*     * We then create a dummy smart pointer "current_node" and assign it to the root of our tree
*     * The following while loop will run until the current node is null
*     * We then check what the value of our input parameter "new_node" is in comparison to our current node of the BST
*     * If "new_node"'s value is less than that of the current node in our BST, we do the following:
*       * We check if the left child of the current node is null
*         * If it is, then the left child of "current_node" is assigned to our "new_node" that is passed as an input parameter
*           "current_node" is then assigned to null to exit the above while loop
*         * If it is not, then the "current_node" is set to the left child of "current_node"
*     * If "new_node"'s value is greater than or equal to that of the current node in our BST, we do the following:
*       * We check if the right child of "current_node" is null
*         * If it is, then the right child of "current_node" is assigned to our "new_node" that is passed as an input parameter
*           "current_node" is then assigned to null to exit the above while loop
*         * If it is not, then the "current_node" is set to the right child of "current_node"
*   Output:
*     There is no output for this function
*   Reference:
*     The skeleton of this algorithm was referenced from the zyBooks Chapter 7.6
*/
void BST::Insert(shared_ptr<bst_node> new_node){
  if (GetRoot() == nullptr) {
    SetRoot(new_node);
  }
  else {
    shared_ptr<bst_node> current_node = GetRoot();
    while (current_node != nullptr) {
      if (new_node->data < current_node->data) {
        if (current_node->left == nullptr) {
          current_node->left = new_node;
          current_node = nullptr;
        }
        else {
          current_node = current_node->left;
        }
      }
      else {
        if (current_node->right == nullptr) {
          current_node->right = new_node;
          current_node = nullptr;
        }
        else {
          current_node = current_node->right;
        }
      }
    }
  }
}

/*  InsertData - This function inserts a node into a BST with a given value
*   Input:
*     data - Integer value that represents the data member "data" of our node to be inserted into our BST
*   Algorithm:
*     * First, we create a new smart pointer with the name "insert_node" that is the node (bst_node) to be inserted into our BST
*     * We then assign the data member "data" of "insert_node" to the input parameter "data"
*     * Then we initialize the left and right children of this new node to be null
*     * Next, check if the root of our BST is null
*       * If it is, then assign the smart pointer "insert_node" to the root of our BST using SetRoot()
*       * If it is not, then proceed to the next step
*     * We then create a dummy smart pointer "current_node" and assign it to the root of our tree
*     * The following while loop will run until the current node is null
*     * We then check what the value of our input parameter "insert_node" is in comparison to our current node of the BST
*     * If "insert_node"'s value is less than that of the current node in our BST, we do the following:
*       * We check if the left child of the current node is null
*         * If it is, then the left child of "current_node" is assigned to our "insert_node" that is passed as an input parameter
*           "current_node" is then assigned to null to exit the above while loop
*         * If it is not, then the "current_node" is set to the left child of "current_node"
*     * If "insert_node"'s value is greater than or equal to that of the current node in our BST, we do the following:
*       * We check if the right child of "current_node" is null
*         * If it is, then the right child of "current_node" is assigned to our "insert_node" that is passed as an input parameter
*           "current_node" is then assigned to null to exit the above while loop
*         * If it is not, then the "current_node" is set to the right child of "current_node"
*   Output:
*     There is no output for this function
*/
void BST::InsertData(int data){
  shared_ptr<bst_node> insert_node(new bst_node);
  insert_node->data = data;
  insert_node->left = nullptr;
  insert_node->right = nullptr;
  if (GetRoot() == nullptr) {
    SetRoot(insert_node);
  }
  else {
    shared_ptr<bst_node> current_node = GetRoot();
    while (current_node != nullptr) {
      if (insert_node->data < current_node->data) {
        if (current_node->left == nullptr) {
          current_node->left = insert_node;
          current_node = nullptr;
        }
        else {
          current_node = current_node->left;
        }
      }
      else {
        if (current_node->right == nullptr) {
          current_node->right = insert_node;
          current_node = nullptr;
        }
        else {
          current_node = current_node->right;
        }
      }
    }
  }
}

/*  Remove - This function removes a node in a BST for a given integer value "data"
*   Input:
*     data - Integer value that is to be searched for and removed from our BST
*   Algorithm:
*     * We first begin by creating three separate nodes (bst_node) and initialize them to specific values
*       * current_node - This node is set to the root of our BST
*       * parent_node - This node is the parent node of our current node in our BST
*       * successor_node - This node is the succeeding node of our current node
*     * We then begin searching our BST by first looking at the root of our BST
*     * The first condition that is checked for is if the current node matches the input parameter "data"
*       * We then have four different checks to make according to the child nodes of the current node
*       * Remove Leaf Node - This occurs when the children of the current node are both null
*         * We then have three conditions to check for inside of this current condition
*           * If the parent node is null, then we set the root node to be null
*             This is the condition where the node that is being removed is the current root of the tree
*           * If the left child of the parent node is the current node, then we set the left child of the parent node
*             to be null, we are removing "current_node" from the tree
*           * Otherwise, if the right child of the parent node is the current node, then we set the right child of the
*             parent node to be null, we are removing "current_node" from the tree
*       * Remove Left Child - This occurs when the right child of the current node is null
*         * We then have three conditions to check for inside of this current condition
*           * If the parent node is null, then we set the root node to be the left child of the current node
*             In this scenario, the current node is the root of the tree and the only remaining node is the left child
*             of the current node, this is why it is set to the root of the tree
*           * If the left child of the parent node is the current node, then we set the left child of the parent node
*             to be the left child of the current node, this replaces the current node with its left child after being removed
*           * If the right child of the parent node is the current node, then we set the right child of the parent node
*             to be the left child of the current node, this replaces the current node with its left child after being removed
*       * Remove Right Child - This occurs when the left child of the current node is null
*         * We then have three conditions to check for inside of this current condition
*           * If the parent node is null, then we set the root node to be the right child of the current node
*             In this scenario, the current node is the root of the tree and the only remaining node is the right child
*             of the current node, this is why it is set to the root of the tree
*           * If the left child of the parent node is the current node, then we set the left child of the parent node
*             to be the right child of the current node, this replaces the current node with its right child after being removed
*           * If the right child of the parent node is the current node, then we set the right child of the parent node
*             to be the right child of the current node, this replaces the current node with its right child after being removed
*       * Remove Node With Two Children - This occurs when the node to be removed has two children attached to it
*         * In this scenario, we set the successor node to be the right child of the current node
*         * We then set the successor node to be its left child until its left child is null, effectively searching the leftmost
*           sub tree until the appropriate successor is found
*         * We then create a copy of this value, and assign it to the integer value "SuccessorData"
*         * Then, a recursive call of "Remove" is made on the "successor_node"'s "data" member, this is done so that we can remove
*           the successor of the current node and put it in the place of the current node
*         * The current node's "data" member is then assigned to the integer value "SuccessorData", effectively placing the successor
*           node in the position of the current node
*     * If the key is not found, then we check if the current nodes data member "data" is less than that of the input parameter "data"
*       * If this is the case, then the parent node is set to that of the current node and the current node is set to its right child
*         We are effectively searching the right sub tree of our BST
*     * If the key is not found, then we check if the current nodes data member "data" is greater than that of the input parameter "data"
*       * If this is the case, then the parent node is set to that of the current node and the current node is set to its left child
*         We are effectively searching the left sub tree of our BST
*     * If neither of the above conditions are met, then that means that the value being searched for does not exist in our BST
*   Output:
*     This function does not return a value
*   Reference:
*     The sekelton of this algorithm was referenced from the zyBooks chapter 7.7 
*/
void BST::Remove(int data) {
  shared_ptr<bst_node> current_node = GetRoot();
  shared_ptr<bst_node> parent_node = nullptr;
  shared_ptr<bst_node> successor_node = nullptr;
  while (current_node != nullptr) {
    // Node found
    if (current_node->data == data) {
      // Remove a leaf node
      if (current_node->left == nullptr && current_node->right == nullptr) {
        if (parent_node == nullptr) {
          SetRoot(nullptr);
        }
        else if (parent_node->left == current_node) {
          parent_node->left = nullptr;
        }
        else {
          parent_node->right = nullptr;
        }
      }
      // Remove left child only
      else if (current_node->right == nullptr) {
        if (parent_node == nullptr) {
          SetRoot(current_node->left);
        }
        else if (parent_node->left == current_node) {
          parent_node->left = current_node->left;
        }
        else {
          parent_node->right = current_node->left;
        }
      }
      // Remove right child only
      else if (current_node->left == nullptr) {
        if (parent_node == nullptr) {
          SetRoot(current_node->right);
        }
        else if (parent_node->left == current_node) {
          parent_node->left = current_node->right;
        }
        else {
          parent_node->right = current_node->right;
        }
      }
      // Remove node with two children
      else {
        successor_node = current_node->right;
        while (successor_node->left != nullptr) {
          successor_node = successor_node->left;
        }
        int SuccessorData = successor_node->data;
        Remove(successor_node->data);
        current_node->data = SuccessorData;
      }
      break;
    }
    // Search to the right
    else if (current_node->data < data) {
      parent_node = current_node;
      current_node = current_node->right;
    }
    // Search to the left
    else {
      parent_node = current_node;
      current_node = current_node->left;
    }
  }
}

/*  Contains - This function checks to see if a specific value is present in our BST
*   Input:
*     subt - A smart pointer pointing to a (bst_node) node in a BST
*     data - An integer whose value is being searched for in a BST
*   Algorithm:
*     * We first check to see if the current node in the tree is null, if it is, we return false
*     * We then check if the current nodes data member "data" is equal to the input parameter "data"
*       * If it is equal to it, we return true, indicating this value exists in our tree
*     * If neither of the two previous conditions are met, then we search through the subtrees of this BST
*       using a recursive call to "Contains"
*       * We then return the boolean value after searching through each subtree
*         * If both are false, then false is returned
*         * If atleast one of these are true, then we return true
*   Output:
*     We return a boolean value indicating whether or not a value is present in a BST
*   Reference:
*     The skeleton of this algorithm was referenced from the zyBooks chapter 7.11
*/
bool BST::Contains(shared_ptr<bst_node> subt, int data){
  if (subt == nullptr) {
    return false;
  }
  else if (subt->data == data) {
    return true;
  }
  else {
    return Contains(subt->left, data) || Contains(subt->right, data);
  }
}

/*  GetNode - This function returns a pointer if a node is present in a BST
*   Input:
*     subt - A smart pointer pointing to a (bst_node) in a BST
*     data - An integer whoe value is being searched for in a BST
*   Algorithm:
*     * We first check to see if the current node in the BST is null, if it is, return NULL
*     * If the current node is not null, we check to see if the current nodes "data" member matches the
*       input parameter "data", if it does, we return the current pointer of the node
*     * If neither of the two conditions are met, we make a recursive call to the left and right subtrees
*       of the BST
*     * We then iterate through the previous steps of the algorithm to determine if a data value is present
*       in our BST
*   Output:
*     We return a pointer to our node depending on if prior conditions are met when searching for a value
*/
shared_ptr<bst_node> BST::GetNode(shared_ptr<bst_node> subt, int data){
  if (subt == nullptr) {
    return shared_ptr<bst_node>(nullptr);
  }
  else if (subt->data == data) {
    return subt;
  }
  else {
    if (GetNode(subt->left, data)) {
      return GetNode(subt->left, data);
    }
    else {
      return GetNode(subt->right, data);
    }
  }
}

/*  Size - This function counts the number of nodes that are present in a given BST
*   Input:
*     subt - A smart pointer that points to a "bst_node" object representing a BST
*   Algorithm:
*     * We first check if the input parameter "subt" is a null, if it is, then we return a value of zero
*     * If the current node, "subt", is not null, then:
*       * We add 1 to our total, and the recursively call "Size" on the left and right child of "subt"
*       * This process will repeat over and over until the end of the tree is reached for both subtrees
*   Output:
*     This function returns an integer value representing the number of nodes in a BST
*/
int BST::Size(shared_ptr<bst_node> subt){
  if (subt == nullptr) {
    return 0;
  }
  else {
    return 1 + Size(subt->left) + Size(subt->right);
  }
}

/*  ToVector - This function appends values to a vector that are present in a BST
*   Input:
*     subt - A smart pointer of the node that belongs to our BST that we are appending data from
*     vec - A vector that integer values are to be appended to from our BST
*   Algorithm:
*     * We first begin by setting the root of our BST to the input parameter "subt"
*     * We then check to see if the root is null, if it is, we return from the function
*     * If the root is not null, then we do the following:
*       * We make a recursive call to the left subtree with "ToVector", to find the leftmost value of our BST
*       * We then append this data to the input parameter "vec"
*       * We then make a recursive call this time to the right subtree with "ToVector", to then find the left most
*         value of the right subtree
*   Output:
*     This function does not return a value
*/
void BST::ToVector(shared_ptr<bst_node> subt, vector<int>& vec){
  SetRoot(subt);
  if (GetRoot() == nullptr) {
    return;
  }
  else {
    ToVector(subt->left, vec);
    vec.push_back(subt->data);
    ToVector(subt->right, vec);
  }
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

/*  InOrder - This function traverses a binary search tree in order
*   Input:
*     subt - A smart pointer pointing to a node in BST
*   Algorithm:
*     * We first check to see if the node that we are looking at is null, if it is, then we return that node
*     * If the node that we are examining is not null, then we proceed to checking each sub tree
*       * If the left child of "subt" is not null, then we recursively call `InOrder` on the left child to 
*         find the leftmost node in the left subtree, the above process will repeat until a null pointer is 
*         found, indicating we have reached the leftmost node of this subtree
*       * If the left child of "subt" is null, we move to the right child and recursively call `InOrder` on the right
*         child to find the leftmost node in the right subtree, the above process will repeat until a null pointer is 
*         found, indicating we have reached the leftmost node of this subtree
*   Output:
*     This function returns a smart pointer to the leftmost node in our BST
*   Reference:
*     The skeleton of this algorithm was referenced from the zyBooks chapter 7.8
*/
shared_ptr<bst_node> BST::InOrder(shared_ptr<bst_node> subt) {
  if (subt == nullptr) {
    return subt;
  }
  else {
    if (InOrder(subt->left)) {
      return InOrder(subt->left);
    }
    else {
      return InOrder(subt->right);
    }
  }
}