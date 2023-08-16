// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "../HPP/BloomFilter.hpp"

// ----- ----- ----- ----- ----- ----- ----- References ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// https://www.geeksforgeeks.org/templates-cpp/

/*  Structure node - Element (or node) of a linked list
*   Data Members:
*       data - Data member of a custom data type (can be any data type)
*       nextNode - Smart pointer pointing to the next node in a linked list
*       previousNode - Smart pointer pointing to the previous node in a linked list
*/
template <typename customType> struct node {
    customType data; // Custom data member element
    std::shared_ptr<node<customType>> nextNode; // Next node pointer of a given node
    std::shared_ptr<node<customType>> previousNode; // Previous node pointer of a given node
};

template <typename customType> class LinkedList {
public:
    // ---- ---- ---- Constructors ---- ---- ---- //
    LinkedList();
    ~LinkedList();
    // ---- ---- ---- Member Functions ---- ---- ---- //
    void AppendNode(std::shared_ptr<node<customType>>& input); // Appends a node to the end of a list
    void ClearList(); // Clears list
    std::shared_ptr<node<customType>> InitNode(const customType& input); // Initializes a node
    std::shared_ptr<node<customType>> InitNode(std::shared_ptr<customType>& input); // Overload for initializing a node
    void InsertNode(std::shared_ptr<node<customType>>& input, int index); // Inserts a node into a list
    std::shared_ptr<node<customType>> PopNode(); // Removes a node from the end of a list
    void PrintList(); // Prints the contents of a list
    void RemoveNode(int index); // Removes a node from a list
    std::shared_ptr<node<customType>> RetrieveNode(int index); // Retrieves a node from a list
    // ---- ---- ---- Mutator Functions ---- ---- ---- //
    // Getter Functions
    std::shared_ptr<node<customType>>& GetRoot(); // Retrieves "rootNode"
    int& GetSize(); // Retrieves "listSize"
    std::shared_ptr<node<customType>>& GetTail(); // Retrieves "tailNode"
    // Setter Functions
    void SetRoot(std::shared_ptr<node<customType>> input); // Mutates "rootNode"
    void SetSize(); // Mutates "listSize"
    void SetTail(std::shared_ptr<node<customType>> input); // Mutates "tailNode"
private:
    std::shared_ptr<node<customType>> rootNode; // Root node of a linked list
    std::shared_ptr<node<customType>> tailNode; // Tail node of a linked list
    int listSize = 0; // Size of a linked list
};

#endif