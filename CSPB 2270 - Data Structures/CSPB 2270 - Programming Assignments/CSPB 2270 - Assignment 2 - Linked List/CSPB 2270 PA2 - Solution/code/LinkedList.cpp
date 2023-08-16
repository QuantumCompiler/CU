#include "LinkedList.h"

/*  Constructor - This constructor initializes our LinkedList class
*   Algorithm:
*     We first access the private data member: "top_ptr_", which is a smart pointer of the standard C++ class called shared_ptr
*     We then set this data member to a nullptr, essentially setting the head of our linked list to null
*/
LinkedList::LinkedList(){
  this->top_ptr_ = nullptr;
}

//deconstructor,
LinkedList::~LinkedList(){
}

/*  InitNode - This function takes in an integer data type and assigns that value to a "node" data type's "data" member
*   Input:
*     data - This is an integer data type that is later assigned to a "node" data type's "data" member
*   Algorithm:
*     shared_ptr<node> ret(new node); - This line creates a smart pointer of data type "node" named "ret"
*   Output:
*     ret - After setting "ret"'s data member to the input parameter "data"
*     The "next" data member of the "node" object is initially set to nullptr, indicating the absence of a next node
*/
shared_ptr<node> LinkedList::InitNode(int data){
  shared_ptr<node> ret(new node);
  ret->data = data;
  return ret;
}

/*  Report - This function returns a string of all the node objects data member "data"'s values
*   Input:
*     This function does not have any input parameters
*   Algorithm:
*     We first initialize a string by the name of "ret" to an empty string
*     We then create an empty vector of integers with the name "prtData", this is a vector of integers
*     that belong to our smart pointer "top_ptr_"
*     We create a pointer called "currPtr" and set it equal to the top_ptr_
*     We then check to see if the current top_ptr_ is empty, if it is, it enters the while loop stated below
*       We then grab the data member of top_ptr_ "data" and append it to the ptrData vector
*       After "data" is appended to our vector, we set currPtr to the next node in the linked list, this is done
*       with the following syntax: "currPtr = currPtr->next;"
*     After the while loop runs into a nullptr, we advance to the if statement below
*     If the vector "ptrData"'s size is greater than zero, we update the string value "ret" with a for loop
*       "ret" is updated with: "ret += to_string(ptrData.at(i)) + " ";"
*       Once we have iterated through all the integers of ptrData, we return "ret"
*     If the vector "ptrData" is empty, then we set "ret" to "" and return it
*   Output:
*     This function returns a string value "ret" after checking certain parameters as stated in the Algorithm section
*/
string LinkedList::Report(){
  string ret;
  vector<int> ptrData;
  shared_ptr<node> currPtr = top_ptr_;
  while (currPtr != nullptr) {
    ptrData.push_back(currPtr->data);
    currPtr = currPtr->next;
  }
  if (ptrData.size() > 0) {
    for (int i = 0; i < ptrData.size(); i++) {
      ret += to_string(ptrData.at(i)) + " ";
    }
    return ret;
  }
  else {
    ret = "";
    return ret;
  }
}

/*  AppendData - This function appends a new node object into a linked list with a given specific value
*   Input:
*     data - This is an integer data type that is used to set the data member "data" of our new node
*   Algorithm:
*     We first create a new smart pointer of object type node called "nxtPtr"
*     Then we set the data member "data" of nxtPtr to the input parameter "data"
*     After that we set the next node of "nxtPtr" to nullptr
*     We then check if the linked list is empty:
*       If the linked list is empty, set the "top_ptr_" of our class to the newly created node "nxtPtr"
*       If the linked list is not empty:
*         Create a new smart pointer of object type node called "currPtr" and set it to the top of our class
*         Traverse down the linked list to find the end of it using a while loop:
*           Check if the current node's next pointer is not nullptr
*         Once we reach the last node, set its next pointer to "nxtPtr" to append the new node to the list
*   Output:
*     This function does not return a value
*/
void LinkedList::AppendData(int data){
  shared_ptr<node> nxtPtr(new node);
  nxtPtr->data = data;
  nxtPtr->next = nullptr;
  if (top_ptr_ == nullptr) {
    SetTop(nxtPtr);
  }
  else {
    shared_ptr<node> currPtr = top_ptr_;
    while (currPtr->next != nullptr) {
      currPtr = currPtr->next;
    }
    currPtr->next = nxtPtr;
  }
}

/*  Append - This function appends a new node to the end of a linked list
*   Input:
*     new_node - A smart pointer to a node object that will be appended to the list
*   Algorithm:
*     We first nitialize the data members of the new node object to appropriate values
*     Then we check if the current linked list is empty:
*       If the linked list is empty, set the top of the linked list to the input parameter "new_node"
*     If the linked list is not empty:
*       We create a new smart pointer called "currPtr" and set it equal to the top of the linked list
*       Then we traverse down the linked list until reaching the last node (When the next node is nullptr):
*         If the next node is not nullptr, move to the next node in the list
*       Once at the end of the linked list, set the next pointer of the current node to "new_node"
*   Output:
*     This function does not return a value
*/
void LinkedList::Append(shared_ptr<node> new_node){
  new_node->data;
  new_node->next = nullptr;
  if (top_ptr_ == nullptr) {
    SetTop(new_node);
  }
  else {
    shared_ptr<node> currPtr = top_ptr_;
    while (currPtr->next != nullptr) {
      currPtr = currPtr->next;
    }
    currPtr->next = new_node;
  }
}

/*  InsertData - This function inserts a new node into a linked list at the specified offset for a given value
*   Input:
*     offset - An integer that is the offset at which the new node should be inserted
*     data - An integer for the data value to be stored in the new node
*   Algorithm:
*     First we create a new smart pointer called "insertPtr" and allocate memory for a new node object
*     Then we create a new smart pointer called "currPtr" and set it equal to the top of the linked list
*     After that we create a vector called "ptrs" to store the smart pointers to each node in the linked list
*     Then we traverse the linked list and add each node's smart pointer to the "ptrs" vector
*     We then set the data value of the "insertPtr" node to the provided "data" argument
*     After that, we check if the offset is zero:
*       If it is zero, set the next pointer of the "insertPtr" node to the current top_ptr_
*       Set the top_ptr_ to the "insertPtr" node, making it the new first node in the linked list
*     If the offset is not zero:
*       Reset "currPtr" to the top_ptr_ and iterate through the "ptrs" vector
*       When the current index matches the offset - 1, set the next pointer of "insertPtr" to currPtr->next
*       Update the next pointer of "currPtr" to "insertPtr", inserting it at the desired offset
*   Output:
*     This function does not return a value
*/
void LinkedList::InsertData(int offset, int data){
  shared_ptr<node> insertPtr(new node);
  shared_ptr<node> currPtr = top_ptr_;
  vector<shared_ptr<node>> ptrs;
  while (currPtr != nullptr) {
    ptrs.push_back(currPtr);
    currPtr = currPtr->next;
  }
  insertPtr->data = data;
  insertPtr->next = nullptr;
  if (offset == 0) {
    insertPtr->next = top_ptr_;
    SetTop(insertPtr);
  }
  else {
    currPtr = top_ptr_;
    for (int i = 0; i < ptrs.size(); i++) {
      if (i == offset - 1) {
        insertPtr->next = currPtr->next;
        currPtr->next = insertPtr;
      }
      else {}
      currPtr = currPtr->next;
    }
  }
}

/*  Insert - This function inserts a new node into a linked list at the specified offset
*   Input:
*     offset - An integer that is the offset at which the new node should be inserted
*     new_node - A smart pointer of object node that is to be inserted into the linked list
*   Algorithm:
*     First we create a new smart pointer called "currPtr" and set it equal to the top of the linked list
*     After that we create a vector called "ptrs" to store the smart pointers to each node in the linked list
*     Then we traverse the linked list and add each node's smart pointer to the "ptrs" vector
*     After that, we check if the offset is zero:
*       If it is zero, set the next pointer of the "new_node" node to the current top_ptr_
*       Set the top_ptr_ to the "new_node" node, making it the new first node in the linked list
*     If the offset is not zero:
*       Reset "currPtr" to the top_ptr_ and iterate through the "ptrs" vector
*       When the current index matches the offset - 1, set the next pointer of "new_node" to currPtr->next
*       Update the next pointer of "currPtr" to "insertPtr", inserting it at the desired offset
*   Output:
*     This function does not return a value
*/
void LinkedList::Insert(int offset, shared_ptr<node> new_node){
  shared_ptr<node> currPtr = top_ptr_;
  vector<shared_ptr<node>> ptrs;
  while (currPtr != nullptr) {
    ptrs.push_back(currPtr);
    currPtr = currPtr->next;
  }
  new_node->data;
  new_node->next = nullptr;
  if (offset == 0) {
    new_node->next = top_ptr_;
    SetTop(new_node);
  }
  else {
    currPtr = top_ptr_;
    for (int i = 0; i < ptrs.size(); i++) {
      if (i == offset - 1) {
        new_node->next = currPtr->next;
        currPtr->next = new_node;
      }
      else {}
      currPtr = currPtr->next;
    }
  }
}

/*  Remove - This function removes a node from a linked list at the specified offset
*   Input:
*     offset - An integer that is the offset of the node to be removed from our linked list
*   Algorithm:
*     First we create a new smart pointer called "currPtr" and set it equal to the top of the linked list
*     Then we create a vector called "ptrs" to store the smart pointers to each node in the linked list
*     After that we iterate through the linked list and add each node's smart pointer to the "ptrs" vector
*     Then we heck if the offset is zero.
*       If it is zero, set the next pointer of the top node to the node after it
*     Otherwise, reset "currPtr" to the top node and iterate through the "ptrs" vector
*       When the current index matches the offset - 1, set the next pointer of "currPtr" to the node after it
*       Break out of the for loop to avoid segmentation faults
*     Output:
*       This function does not return a value.
*/
void LinkedList::Remove(int offset){
  shared_ptr<node> currPtr = top_ptr_;
  vector<shared_ptr<node>> ptrs;
  while (currPtr != nullptr) {
    ptrs.push_back(currPtr);
    currPtr = currPtr->next;
  }
  if (offset == 0) {
    SetTop(top_ptr_->next);
  }
  else {
    currPtr = top_ptr_;
    for (int i = 0; i < ptrs.size(); i++) {
      if (i == offset - 1) {
        currPtr->next = currPtr->next->next;
        break;
      }
      else {}
      currPtr = currPtr->next;
    }
  }
}

/*  Size - This function counts how many nodes are present in our linked list
*   Algorithm:
*     We first create a smart pointer called "currPtr" and set it equal to our "top_ptr_" in our linked list
*     We initialize the return value "ret" to zero
*     Then we enter a while loop that increments "ret" by one until it runs into the tail of the list
*     Advance the current pointer object using "currPtr = currPtr->next;"
*   Output:
*     ret - Integer value that represents the number of nodes that are present in our linked list
*/
int LinkedList::Size(){
  shared_ptr<node> currPtr = top_ptr_;
  int ret = 0;
  while (currPtr != nullptr) {
    ret++;
    currPtr = currPtr->next;
  }
  return ret;
}

/*  Contains - This function determines if an element is present inside a linked list
*   Input:
*     data - This is an integer that is being searched for in our linked list
*   Algorithm:
*     First, create a smart pointer called "currPtr" and initialize it to the head of our linked list
*     Initialize the return value "ret" to false, so that if a value is not found we do not need to change it to false
*     Traverse through the linked list with the use of a while loop and check if the current nodes "data" member matches
*     the input parameter "data"
*       If the two are a match, change the value of "ret" to true, otherwise, leave it as false
*   Output:
*     ret - Boolean value indicating if a value was found in the linked list
*/
bool LinkedList::Contains(int data){
  shared_ptr<node> currPtr = top_ptr_;
  bool ret = false;
  while (currPtr != nullptr) {
    if (currPtr->data == data) {
      ret = true;
    }
    else {}
    currPtr = currPtr->next;
  }
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
