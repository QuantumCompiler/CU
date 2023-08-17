#include "Huffman.h"

// constructor, initialize class variables and pointers here if need.
Huffman::Huffman(){
  // your code here
}

//deconstructor,
Huffman::~Huffman(){
}

/*  CreateLeaf - Creates a "freq_info" object and sets the data members to the input parameters
*   Input:
*     symbol - Character value that represents the character of the leaf object
*     count - Integer value that represents the count of the character
*   Algorithm:
*     * Create a "freq_info" object and initialize it on the heap
*     * Assign the data members of "ret" to the input parameters of "CreateLeaf"
*   Output:
*     ret - Smart pointer of object type "freq_info" that represents the leaf of a huffman tree
*/
shared_ptr<freq_info> Huffman::CreateLeaf(char symbol, int count) {
  // Create freq_info object
  shared_ptr<freq_info> ret(new freq_info);
  // Set data members equal to input parameters
  ret->symbol = symbol;
  ret->count = count;
  ret->left = nullptr;
  ret->right = nullptr;
  ret->is_leaf = true;
  return ret;
}

/*  CombineNodes - Creates a "freq_info" object and combines two leafs
*   Input:
*     left - Smart pointer of object type "freq_info" that represents the left node of "ret"
*     right - Smart pointer of object type "freq_info" that represents the right node of "ret"
*   Algorithm:
*     * Create a "freq_info" object and initialize it on the heap
*     * Assign the left and right nodes to that of "ret" and calculate the "count" data member
*   Output:
*     ret - Smart pointer of object type "freq_info" that represents the combined nodes of a Huffman tree
*/
shared_ptr<freq_info> Huffman::CombineNodes(shared_ptr<freq_info> left, shared_ptr<freq_info> right) {
  // Create freq_info object
  shared_ptr<freq_info> ret(new freq_info);
  // Assign the left and right nodes to that of "ret" and calculate the "count" data member
  ret->is_leaf = false;
  ret->count = left->count + right->count;
  ret->left = left;
  ret->right = right;
  return ret;
}

/*  IncrementLookup - Increments the count that represents the number of characters in a string
*   Input:
*     lookup - Map value that contains a character and an integer value
*     symbol - Symbol that is being fed into the map
*   Algorithm:
*     * Increment the integer value in the map when the symbol is found in the map
*   Output:
*     This function does not return a value, it modifies the map that is fed into it
*/
void Huffman::IncrementLookup(map<char, int>& lookup, char symbol) {
  lookup[symbol]++;
}

/*  LoadQueue - Creates a "freq_info" node from a lookup table and pushes the node to the queue
*   Input:
*     lookup - Constant map object that is passed by reference that contains a character and a frequency of said object
*     q - "tree_queue" priority queue object that is passed by reference that represents the priority queue where nodes are held
*   Algorithm:
*     * Iterate through the lookup table
*     * Create a node that is to be inserted into the priority queue "q"
*     * Assign the data members of the node to that of the lookup tables values
*     * Push the node to the priority queue
*   Output:
*     This function does not return a value, it appends nodes to a priority queue
*/
void Huffman::LoadQueue(const map<char, int>& lookup, tree_queue& q) {
  // Iterate through the lookup table
  for (const auto& pair : lookup) {
    // Create a new node that is to be pushed to the priority queue
    shared_ptr<freq_info> node(new freq_info);
    // Assign the data members of node to the elements in the lookup table
    node->symbol = pair.first;
    node->count = pair.second;
    node->is_leaf = true;
    // Push the node to the priority queue
    q.push(node);
  }
}

/*  BuildTree - Builds a Huffman tree using values contained in the priority queue "q"
*   Input:
*     q - "tree_queue" priority queue that is passed by reference that represents the huffman tree
*   Algorithm:
*     * Iterate through the priority queue "q"
*     * Grab the lowest frequency node and assign it to "left" and remove the top element of the queue
*     * Grab the next lowest frequency node and assign it to "right" and remove the top element of the queue
*     * Create a temporary node "tempNode" and assign its data members to that of "left" and "right"
*     * Push "tempNode" to the priority queue
*     * Once the priority queue has been completely traversed, return the top of the queue
*   Output:
*     q.top() - This is the root node of the tree that is being returned
*/
shared_ptr<freq_info> Huffman::BuildTree(tree_queue& q) {
  // Iterate through the priority queue
  while(q.size() > 1) {
    // Grab the top of the tree and create a node with its top element, call it left
    shared_ptr<freq_info> left = q.top();
    q.pop();
    // Grab the top of the tree and create a node with its top element, call it right
    shared_ptr<freq_info> right = q.top();
    q.pop();
    // Create a temporary node that will be pushed back into the tree
    shared_ptr<freq_info> tempNode(new freq_info);
    // Assign the data members of "tempNode" to that of the left and right nodes
    tempNode->count = left->count + right->count;
    tempNode->left = left;
    tempNode->right = right;
    // Push "tempNode" into the priority queue
    q.push(tempNode);
  }
  // Return the top of the priority queue
  return q.top();
}

/*  TableHelper - This function creates a code for a given character that is found by traversing a Huffman tree
*   Input:
*     node - Smart pointer of object type "freq_info" that represents a node in a huffman tree
*     code - String value that represents the code for a given character 
*     lookup - Map object that is passed by reference that represents the table that is being updated with the code
*   Algorithm:
*     * Check if the current node is a leaf node, if it is, assign the "code" value to the character of "node->symbol"
*     * If the node is not a leaf, traverse the left and right subtrees of the node
*       * Add the character "." to "code" if it traverses left
*       * Add the character "^" to "code" if it traverses right
*   Output:
*     This function does not return a value, it updates a key value pair in lookup after traversing a priority queue
*/
void Huffman::TableHelper(shared_ptr<freq_info> node, string code, map<char, string>& lookup) {
  // Check if the current node is a leaf node
  if (node->is_leaf) {
    lookup[node->symbol] = code;
  }
  // If it isn't recursively traverse the left and right subtrees of the node
  else {
    // Add the character "." to the code value if it traverses left
    if (node->left) {
      TableHelper(node->left, code + ".", lookup);
    }
    // Add the character "^" to the code value if it traverses right
    if (node->right) {
      TableHelper(node->right, code + "^", lookup);
    }
  }
}

/*  BuildEncodingTable - Creates a lookup table for given character in a Huffman tree associated with a specific code
*   Input:
*     root - Smart pointer of object type "freq_info" that represents the root node of a Huffman tree
*   Algorithm:
*     * Create a lookup table to store the code for the given character in a Huffman tree
*     * Call the TableHelper() function to traverse the Huffman tree and update the code
*     * Return the lookup table after a leaf node has been found
*   Output:
*     lookup - Map object that represents a code for a given character in a Huffman tree
*/
map<char, string> Huffman::BuildEncodingTable(shared_ptr<freq_info> root) {
  // Create lookup table and update it with TableHelper()
  map<char, string> lookup;
  TableHelper(root, "", lookup);
  // Return lookup table
  return lookup;
}

/*  Encode - Produces an encoded string for a given input string
*   Input:
*     enc_table - Map that represents the encoded lookup table 
*     input - String value that represents the given string to be encoded
*   Algorithm:
*     * Create an empty string for the encoded value of "input"
*     * Update "code" by appending characters with the huffman code corresponding to character "c"
*     * Return the encoded string
*   Output:
*     code - String value that represents the encoded string of "input"
*/
string Huffman::Encode(map<char, string> enc_table, string input) {
  // Create empty string for encoded string
  string code;
  // Update the string with its correct encoded characters
  for (char c : input) {
    code += enc_table[c];
  }
  // Return the encoded string
  return code;
}

/*  Decode - Decodes an encoded string and returns the decoded string
*   Input:
*     root - Smart pointer of object type "freq_info" that represents the root of a priority queue
*     input - String value that represents the encoded string that needs to be decoded
*   Algorithm:
*     * Create a string value to represent the decoded string value
*     * Create a node object to represent the current position in the tree
*     * Iterate through the encoded string
*       * If the current character is ".", move to the left subtree
*       * If the current character is "^", move to the right subtree
*       * If the current node is a leaf node, add the symbol of current node to "decode" and return to the root of the tree
*       * Return the decoded string after all characters have been traversed
*   Output:
*     decode - String value that represents the decoded string value that came from "input"
*/
string Huffman::Decode(shared_ptr<freq_info> root, string input) {
  // Create a string object for the decoded string value
  string decode;
  // Create a node to keep track of where we are in the tree, assign it to root initially
  shared_ptr<freq_info> cur = root;
  // Iterate through the characters of the encoded string
  for (char c : input) {
    // Move to left node if the current character is "."
    if (c == '.') {
      cur = cur->left;
    }
    // Move to the right node if the current character is "^"
    else if (c == '^') {
      cur = cur->right;
    }
    // If the current node is a leaf node, add the symbol of "cur" to "decode" and move back to the root
    if (cur->is_leaf) {
      decode += cur->symbol;
      cur = root;
    }
  }
  // Return decoded string
  return decode;
}