#include "BTree.h"

// https://www.programiz.com/dsa/insertion-into-a-b-tree

// constructor, initialize class variables and pointers here if need.
BTree::BTree(){
}

//deconstructor,
BTree::~BTree(){
}

void BTree::insert(shared_ptr<btree>& root, int key) {
  setRoot(root);
  shared_ptr<btree> foundNode = find(root, key);
  if (foundNode == root && root->num_keys == 0) {
    root->keys[0] = key;
    root->num_keys++;
    root->is_leaf = true;
  }
  else if (foundNode == root && root->num_keys < 4) {
    insertNonfull(root, key);
  }
  else if (foundNode == root && root->num_keys == 4) {
    shared_ptr<btree> newRoot = splitRoot(root, key);
    root = newRoot;
  }
  else if (foundNode != root && foundNode->num_keys < 4) {
    insertNonfull(foundNode, key);
  }
  else {}
}

void BTree::remove(shared_ptr<btree>& root, int key) {
  setRoot(root);
  shared_ptr<btree> foundNode = find(root, key);
  if (foundNode->num_keys == 0) {
    return;
  }
  else {
    if (foundNode == root && root->num_keys <= 4) {
      removeFromLeaf(root, key);
    }
    else if (foundNode != root && foundNode->num_keys <= 4) {
      removeFromLeaf(foundNode, key);
    }
  }
}

/*  find - Function that searches for if a key exists in a B-Tree
*   Input:
*     root - Smart pointer of object type "btree" that represents the root of our tree
*     key - Integer value that represents the key that is being searched for in the tree
*   Algorithm:
*     * First check to see if the root is null, if it is, return null
*     * Otherwise, traverse the tree looking for the key in the tree
*       * Traverse through the current level of the tree to see if the key exists or where we should look next for the key
*       * Check to see if the key exists in the current level, if it does, return the node
*       * If the key is not found, then we return the node
*       * If all else fails above, we recursively call the "find" function on the correct key to look in its subtree
*   Output:
*     This function returns a node depending on certain cases if they are met
*   Reference:
*     https://www.geeksforgeeks.org/introduction-of-b-tree-2/
*/
shared_ptr<btree> BTree::find(shared_ptr<btree>& root, int key){
  // Check if the root is null, if so, return a nullptr
  if (root == nullptr) {
    return shared_ptr<btree>(NULL);  
  }
  // Otherwise, traverse the tree to determine if the key is in the tree
  else {
    int i = 0;
    // Traverse through the current level of the tree to determine which key to look for the value
    while (i < root->num_keys && key > root->keys[i]) {
      i++;
    }
    // If the key is found in the current level, return the node for where the key is located
    if (i < root->num_keys && key == root->keys[i]) {
      return root;
    }
    // If the key is not found, then just return the node
    else if (root->is_leaf) {
      return root;
    }
    // Otherwise, recursively call find on the correct subtree to find the keys
    else {
      return find(root->children[i], key);
    }
  }
}

/*  count_nodes - Function that counts the number of nodes in a B-Tree
*   Input:
*     root - Smart pointer of object type "btree", this is the root of the tree
*   Algorithm:
*     * Create a counter that keeps track of the number of nodes in a B-Tree
*     * Check to see if the root of the tree is null, if so, return 0
*     * Otherwise, traverse the tree, counting each node of each subtree
*       * Count the number of nodes in each subtree with a for loop
*       * Recursively call the "count_nodes" function on the children nodes
*       * Return the value "nodes"
*   Output:
*     nodes - Integer value that keeps track of the number of nodes in the tree
*   Reference:
*     https://www.tutorialspoint.com/data_structures_algorithms/b_trees.htm    
*/
int BTree::count_nodes(shared_ptr<btree> root){
  // Create a counter for the number of nodes
  int nodes = 0;
  // Check if the root is null, if so, return 0
  if (root == nullptr) {
    return nodes;
  }
  // Otherwise, traverse the tree
  else {
    nodes = 1;
    // Traverse the tree, counting the number of nodes in each subtree
    for (int i = 0; i <= root->num_keys; i++) {
      // Recursively call the function to count the total number of nodes in each subtree
      nodes += count_nodes(root->children[i]);
    }
    return nodes;
  }
}

/*  count_keys - Function that counts the number of keys in the tree
*   Input:
*     root - Smart pointer of object type "btree", this is the root of our tree
*   Algorithm:
*     * Create a counter for the number of keys that are in the tree
*     * Check to see if the root is null, if it is, return 0
*     * Otherwise, begin traversing the tree
*       * Count the number of keys in the present node
*       * Traverse the subtree of current node, counting the number of keys in each child node
*       * Recursively call the function to count the total number of keys in each child node
*   Output:
*     keys - Integer value representing the total number of keys in the B-Tree
*   Reference:
*     https://www.tutorialspoint.com/data_structures_algorithms/b_trees.htm  
*/
int BTree::count_keys(shared_ptr<btree> root){
  // Create a counter for the number of keys
  int keys = 0;
  // Check if the root is null, if so, return 0
  if (root == nullptr) {
    return keys;
  }
  // Otherwise, traverse the tree
  else {
    // Count the number of keys that are in the present node
    keys += root->num_keys;
    // Traverse the tree, counting the number of keys in each child node
    for (int i = 0; i <= root->num_keys; i++) {
      // Recursively call the function to count the total number of keys in each child node
      keys += count_keys(root->children[i]);
    }
    return keys;
  }
}

// General Algorithms

void BTree::bubblesort(shared_ptr<btree> input){
  for (int i = 0; i < input->num_keys - 1; i++) {
    for (int j = 0; j < input->num_keys - i - 1; j++) {
      if (input->keys[j] > input->keys[j+1]) {
        int temp_val = input->keys[j];
        input->keys[j] = input->keys[j+1];
        input->keys[j+1] = temp_val;
      }
    }
  }
}

shared_ptr<btree> BTree::initNode() {
  shared_ptr<btree> newNode(new btree);
  newNode->num_keys = 0;
  newNode->is_leaf = true;
  return newNode;
}

void BTree::printKeys(shared_ptr<btree> root) {
  if (root != nullptr) {
    int i;
    for (i = 0; i <= root->num_keys; i++) {
      printKeys(root->children[i]);
      cout << root->keys[i] << " ";
    }
    printKeys(root->children[i]);
  }
}

void BTree::setRoot(shared_ptr<btree>& input) {
  treeRoot = input;
}

shared_ptr<btree> BTree::getRoot() const {
  return treeRoot;
}

// Insert Algorithms

void BTree::insertNonfull(shared_ptr<btree> input, int key) {
  input->keys[input->num_keys] = key;
  input->num_keys++;
  bubblesort(input);
}

shared_ptr<btree> BTree::splitRoot(shared_ptr<btree> initRoot, int key) {
  setRoot(initRoot);
  if (!initRoot->is_full()) {
    return nullptr;
  }
  else {
    shared_ptr<btree> tempNode(new btree);
    for (int i = 0; i < initRoot->num_keys; i++) {
      tempNode->keys[i] = initRoot->keys[i];
      tempNode->num_keys++;
    }
    insertNonfull(tempNode, key);
    int mid_idx = tempNode->num_keys / 2;
    shared_ptr<btree> leftChild(new btree);
    for (int i = 0; i < mid_idx; i++) {
      leftChild->keys[i] = tempNode->keys[i];
      leftChild->num_keys++;
    }
    leftChild->is_leaf = true;
    shared_ptr<btree> rightChild(new btree);
    for (int i = mid_idx + 1; i < tempNode->num_keys; i++) {
      rightChild->keys[i - (mid_idx + 1)] = tempNode->keys[i];
      rightChild->num_keys++;
    }
    rightChild->is_leaf = true;
    shared_ptr<btree> parent(new btree);
    insertNonfull(parent, tempNode->keys[mid_idx]);
    parent->children[0] = leftChild;
    parent->children[1] = rightChild;
    parent->is_leaf = false;
    return parent;
  }
}

// Remove Algorithms

void BTree::removeFromLeaf(shared_ptr<btree>& input, int key) {
  int index = 0;
  while (index < input->num_keys && key > input->keys[index]) {
    index++;
  }
  for (int i = index; i < input->num_keys; i++) {
    int temp_val = input->keys[i + 1];
    input->keys[i] = temp_val;
    input->num_keys--;
  }
}