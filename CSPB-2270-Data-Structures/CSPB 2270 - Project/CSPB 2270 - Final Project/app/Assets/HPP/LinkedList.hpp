// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/LinkedList.h"

/*  LinkedList - Constructor for LinkedList class
*   Input:
*       This constructor does not have any input parameters
*   Algorithm:
*       * Create null nodes for root and tails of list
*       * Assign default values to private data members of the list
*/
template <typename customType> LinkedList<customType>::LinkedList() {
    // Create node objects for the initial root and tail of list
    std::shared_ptr<node<customType>> initRoot = nullptr;
    std::shared_ptr<node<customType>> initTail = nullptr;
    // Assign default values to the private data members of the class
    this->SetRoot(initRoot);
    this->SetTail(initTail);
    this->SetSize();
}

// ~LinkedList - Deconstructor for LinkedList class
template <typename customType> LinkedList<customType>::~LinkedList() {}

/*  AppendNode - Adds a node to the end of a list
*   Input:
*       input - Node object of type "customType" that is passed by reference that is to be appended to the list
*   Algorithm:
*       * Check if the root of the list is null, if so:
*           * Assign the next and previous nodes of "input" to be empty (or null)
*           * Assign the root and tail of the list to be that of "input"
*       * Check if the root is not null, if so:
*           * Retrieve the root of the list
*           * Traverse to the end of the list, updating "current" on the way
*           * Set the next node of the current tail to "input"
*           * Set the previous node of "input" to the current node
*           * Set the next node of the "input" to be null
*           * Set the tail of the list to be that of "input"
*       * Calculate the size of the list
*   Output:
*       This function does not return a value, it appends a node to the end of the current list
*/
template <typename customType> void LinkedList<customType>::AppendNode(std::shared_ptr<node<customType>>& input) {
    // Check if the root is null
    if (this->GetRoot() == nullptr) {
        // Assign next and previous nodes of "input" to null
        input->previousNode = nullptr;
        input->nextNode = nullptr;
        // Assign root and tail of list to "input"
        this->SetRoot(input);
        this->SetTail(input);
    }
    // Root is not null
    else {
        // Retrieve the root of the list
        std::shared_ptr<node<customType>> current = this->GetRoot();
        // Traverse to the end of the list
        while (current->nextNode != nullptr) {
            current = current->nextNode;
        }
        // Set the next node of the current tail "input"
        current->nextNode = input;
        // Assign next and previous nodes to their respective values
        input->previousNode = current;
        input->nextNode = nullptr;
        // Set the tail of the list to that of "input"
        this->SetTail(input);
    }
    // Calculate the size of the list
    this->SetSize();
}

/*  ClearList - Clears a linked list of all the elements and sets the size to be zero
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Retrieve the root of the current list
*       * Traverse the list until the end of the list is reached
*       * Update the current node to be empty
*       * Set the root and tail to be null, set the size to be zero
*/
template <typename customType> void LinkedList<customType>::ClearList() {
    // Retrieve the root of the current list
    std::shared_ptr<node<customType>> current = this->GetRoot();
    // Traverse the list until one reaches the end of the list
    while (current != nullptr) {
        // Create a temporary node set to that of the current node
        std::shared_ptr<node<customType>> temp = current;
        // Update the current node to that of the next node
        current = current->nextNode;
        // Clear the temporary node
        temp = nullptr;
    }
    // Set the root and tail of the list, calculate the size of the list
    this->SetRoot(nullptr);
    this->SetTail(nullptr);
    this->SetSize();
}

/*  InitNode - Initializes a node to that of a custom data type
*   Input:
*       input - Constant custom data type that is passed by reference to be assigned to a node
*   Algorithm:
*       * Generate a new node of custom type "customType" on the heap
*       * Assign the data members of the node
*   Output:
*       ret - Smart pointer of object type node of custom data type customType
*/
template <typename customType> std::shared_ptr<node<customType>> LinkedList<customType>::InitNode(const customType& input) {
    // Generate a new node on the heap
    std::shared_ptr<node<customType>> ret(new node<customType>);
    // Assign the data members of the node to that of "input" and null
    ret->data = input;
    ret->nextNode = nullptr;
    ret->previousNode = nullptr;
    return ret;
}

/*  Overloaded InitNode - Initializes a node to that of a custom data type
*   Input:
*       input - Smart pointer of object type customType that is passed by reference
*   Algorithm:
*       * Generate a new node of custom type "customType" on the heap
*       * Assign the data members of the node
*   Output:
*       ret - Smart pointer of object type node of custom data type customType
*/
template <typename customType> std::shared_ptr<node<customType>> LinkedList<customType>::InitNode(std::shared_ptr<customType>& input) {
    // Generate a new node on the heap
    std::shared_ptr<node<customType>> ret(new node<customType>);
    // Assign the data members of the node to that of "input" and null
    ret->data = *input;
    ret->nextNode = nullptr;
    ret->previousNode = nullptr;
    return ret;
}

/*  InsertNode - Inserts a node into a list at a given index
*   Input:
*       input - Smart pointer of object type node of custom type "customType" that is passed by reference that is to be inserted into a list
*       index - Integer value that represents the index where a node is to be inserted into the list
*   Algorithm:
*       * Handle the logic for where the node is going to be inserted (see inline comments)
*   Output:
*       This function does not return a value, it inserts a node into a linked list
*/
template <typename customType> void LinkedList<customType>::InsertNode(std::shared_ptr<node<customType>>& input, int index) {
    // Search for the node in the list
    std::shared_ptr<node<customType>> foundNode = this->RetrieveNode(index);
    // Node is being inserted at root of list
    if (foundNode == this->GetRoot()) {
        // Root is not null
        if (this->GetRoot()) {
            // Next node of the found node is not null
            if (foundNode->nextNode) {
                input->previousNode = nullptr;
                input->nextNode = foundNode;
                foundNode->previousNode = input;
                this->SetRoot(input);
            }
            // Next node of the found node is null
            else {
                input->previousNode = this->GetRoot();
                input->nextNode = nullptr;
                this->GetRoot()->nextNode = input;
                this->SetTail(input);
            }
        }
        // Root is null
        else {
            this->SetRoot(input);
            this->SetTail(input);
        }
    }
    // Found node is tail or in between
    else {
        // Insert node, update pointers
        input->nextNode = foundNode;
        input->previousNode = foundNode->previousNode;
        foundNode->previousNode->nextNode = input;
        foundNode->previousNode = input;
        // Found node is the tail
        if (foundNode == this->GetTail()) {
            this->SetTail(foundNode);
        }
        // Found node is in between
        else {
            this->SetSize();
        }
    }
}

/*  PopNode - Remove the last node in a linked list and return that node
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Allocate a new node to be returned
*       * Process the logic for the correct condition (see inline comments)
*   Output:
*       returnNode - Smart pointer of object type node of custom type "customType"
*/
template <typename customType> std::shared_ptr<node<customType>> LinkedList<customType>::PopNode() {
    // Allocate a new node on the heap
    std::shared_ptr<node<customType>> returnNode(new node<customType>);
    // Root is null (list is empty), return a null pointer
    if (this->GetRoot() == nullptr) {
        this->SetSize();
        returnNode = nullptr;
        return returnNode;
    }
    // Only the root exists
    else if (this->GetRoot()->previousNode == nullptr && this->GetRoot()->nextNode == nullptr) {
        // Assign "returnNode" to the root of the list
        returnNode = GetRoot();
        // Set the root and tail of the list to be null
        this->SetRoot(nullptr);
        this->SetTail(nullptr);
    }
    // List has two or more elements
    else {
        // Retrieve the root of the current list
        std::shared_ptr<node<customType>> current = this->GetRoot();
        // Iterate to the end of the list
        while (current->nextNode != nullptr) {
            current = current->nextNode;
        }
        // Assign "returnNode" to the tail of the list
        returnNode = current;
        // Assign the current nodes previous next node to be null
        current->previousNode->nextNode = nullptr;
        // If the current nodes previous previous node is null, assign it to be the root
        if (current->previousNode->previousNode == nullptr) {
            this->SetRoot(current->previousNode);
        }
        // Assign the current nodes previous node to be the tail
        this->SetTail(current->previousNode);
    }
    // Calculate the size of the list
    this->SetSize();
    // Return the node that is being removed
    return returnNode;
}

/*  PrintList - Prints the memory address of a list
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Retrieve the root of the list
*       * Check if the current root is null
*       * Iterate through the list, printing the addresses of the nodes
*       * Output the size of the list  
*   Output:
*       This function does not return a value, it prints the memory address of elements in a list
*/
template <typename customType> void LinkedList<customType>::PrintList() {
    // Retrieve the root of the list
    std::shared_ptr<node<customType>> current = this->GetRoot();
    // Root is null, output that the list is empty
    if (current == nullptr) {
        std::cout << "Empty list." << std::endl;
    }
    // Iterate through the elements in a list, print the memory address of the previous, next and current node
    while (current != nullptr) {
        std::cout << "Previous: " << current->previousNode << ", Current: " << current << ", Next: " << current->nextNode << " | ";
        current = current->nextNode;
    }
    // Output the size of the list
    std::cout << " Size: " << this->GetSize() << std::endl;
}

/*  RemoveNode - Removes a node from a linked list at a given index of the list
*   Input:
*       index - Integer value that represents the index of the element to be removed
*   Algorithm:
*       * Handle the logic for what node is to be removed (see inline comments)
*   Output:
*       This function does not return a value, it removes a node from a linked list
*/
template <typename customType> void LinkedList<customType>::RemoveNode(int index) {
    // Search for the node in the list
    std::shared_ptr<node<customType>> foundNode = this->RetrieveNode(index);
    // Found node is the root of a list
    if (foundNode == this->GetRoot()) {
        // Root is not null
        if (this->GetRoot() != nullptr) {
            // Next node of the found node is not null
            if (foundNode->nextNode) {
                // Set the root to be the next node of the found node
                this->SetRoot(foundNode->nextNode);
                // Set the previous node of the current node to be null
                this->GetRoot()->previousNode = nullptr;
                // If the next node of the root is null, set it to be the tail
                if (this->GetRoot()->nextNode == nullptr) {
                    this->SetTail(this->GetRoot());
                }
            }
            // Next node of the found node is null
            else {
                // Set the root and tail to be null
                this->SetRoot(nullptr);
                this->SetTail(nullptr);
            }
        }
        // Root is null
        else {
            // Set root and tail to be the found node
            this->SetRoot(foundNode);
            this->SetTail(foundNode);
        }
    }
    // Found node is the tail of the list
    else if (foundNode == this->GetTail()) {
        // Previous node of the tail is not null
        if (this->GetTail()->previousNode) {
            // Set the previous next node of the tail to be null
            this->GetTail()->previousNode->nextNode = nullptr;
            // Set the tail of the list to be the previous node of the tail
            this->SetTail(this->GetTail()->previousNode);
            // Set the root of the list to be the tail of the list if both previous and next are null
            if (this->GetTail()->previousNode == nullptr && this->GetTail()->nextNode == nullptr) {
                // Set the root of the list to be the tail
                this->SetRoot(this->GetTail());
            }
            this->GetTail()->nextNode = nullptr;
        }
        // Previous node of the tail is null
        else {
            // Set the tail to be null
            this->SetTail(nullptr);
        }
    }
    // Found node is in between the root and tail of the list
    else {
        if (foundNode->nextNode) {
            foundNode->previousNode->nextNode = foundNode->nextNode;
            foundNode->nextNode->previousNode = foundNode->previousNode;
            this->SetSize();
        }
        else {
            this->SetTail(foundNode);
        }
    }
}

/*  RetrieveNode - Retrieves a node at a current index of the list
*   Input:
*       index - Integer value that represents the index of the element that is to be retrieved
*   Algorithm:
*       * Allocate a node on the heap
*       * Search for the node in the list according to the input parameter "index"
*       * Return either the root or tail if the index is 0, -1, or greater than the size of the list
*       * Iterate through the list until the index of the list is reached
*       * Return the node at the given index
*   Output:
*       ret - Smart pointer of object type node of custom type "customType"
*/
template <typename customType> std::shared_ptr<node<customType>> LinkedList<customType>::RetrieveNode(int index) {
    // Allocate a node on the heap
    std::shared_ptr<node<customType>> ret(new node<customType>);
    // Node is the root, return it
    if (index == 0) {
        ret = this->GetRoot();
    }
    // Node is the tail, return it
    else if (index == -1 || index >= this->GetSize()) {
        ret = this->GetTail();
    }
    // Node is found in between the root and tail
    else {
        // Retrieve the root of the list
        std::shared_ptr<node<customType>> current = this->GetRoot();
        // Keep track of the index
        int indexTracker = 0;
        // Traverse until "indexTracker" is equal to that of "index"
        while (current != nullptr && indexTracker < index) {
            current = current->nextNode;
            indexTracker++;
        }
        // Assign "ret" to that of "current"
        ret = current;
    }
    // Return the node from the list
    return ret;
}

// ----- ----- ----- ----- ----- ----- ----- Mutators ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetRoot - Retrieves the private data member "rootNode"
template <typename customType> std::shared_ptr<node<customType>>& LinkedList<customType>::GetRoot() {
    return this->rootNode;
}

// GetSize - Retrieves the private data member "listSize"
template <typename customType> int& LinkedList<customType>::GetSize() {
    return this->listSize;
}

// GetTail - Retrieves the private data member "tailNode"
template <typename customType> std::shared_ptr<node<customType>>& LinkedList<customType>::GetTail() {
    return this->tailNode;
}

// SetRoot - Mutates the private data member "rootNode"
template <typename customType> void LinkedList<customType>::SetRoot(std::shared_ptr<node<customType>> input) {
    this->rootNode = input;
    this->SetSize();
}

// SetSize - Mutates the private data member "listSize"
template <typename customType> void LinkedList<customType>::SetSize() {
    this->listSize = 0;
    std::shared_ptr<node<customType>> current = this->GetRoot();
    while (current != nullptr) {
        this->listSize++;
        current = current->nextNode;
    }
}

// SetTail - Mutates the private data member "tailNode"
template <typename customType> void LinkedList<customType>::SetTail(std::shared_ptr<node<customType>> input) {
    this->tailNode = input;
    this->SetSize();
}