#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {}

PriorityQueue::~PriorityQueue() {}

/*  InitPriorityQueue - Initialization of priority queue
 *   Input:
 *       This function does not require an input
 *   Algorithm:
 *       * Create a pq object and initialize its data members to empty
 *   Output:
 *       queue - This function returns a priority queue object (pq) after being initialized
 */
shared_ptr<pq> PriorityQueue::InitPriorityQueue()
{
    // Create a pq object and initialize its data members to be empty
    shared_ptr<pq> queue(new pq);
    queue->heapString.clear();
    queue->heapPriority.clear();
    // Return the priority queue (queue)
    return queue;
}

/*  Insert - Inserts a string and float value into their respective vectors and places them in the appropriate positions
 *   Input:
 *       queue - Smart pointer of object type (pq) that represents the priority queue to be inserted into
 *       text - String that is to be inserted into the (heapString) vector
 *       priority - Float that indicates the priority of the element being inserted into (heapString)
 *   Algorithm:
 *       * Insert the (text) and (priority) elements into their respective vectors at the back
 *       * Calculate the index of the last element in the (heapString) vector
 *       * Percolate the elements to their respective correct positions in their vectors
 *   Output:
 *       This function does not return a value, it modifies the priority queue (queue)
 */
void PriorityQueue::Insert(shared_ptr<pq> queue, string text, float priority)
{
    // Insert the (text) and (priority) elements to the back of their respective vectors
    queue->heapString.push_back(text);
    queue->heapPriority.push_back(priority);
    // Calculate the index value of the last element in the (heapString) vector and percolate the object up the heap
    int currentIndex = queue->heapString.size() - 1;
    queue->percolateUp(currentIndex);
}

/*  Remove - Removes an element from the priority queue (queue)
 *   Input:
 *       queue - Smart pointer of object type (pq) that represents the priority queue who's element is to be removed from
 *   Algorithm:
 *       * Create a default string value to represent the return value
 *       * Set the return string value to empty if the queue is empty
 *       * Search for the highest priority element in the queue
 *       * Set the return value to the highest priority element in the queue
 *       * Delete the values from their respective vectors
 *       * Return the element that has been removed
 *   Output:
 *       returnVal - This function returns the highest priority string value in the queue that has been removed
 */
string PriorityQueue::Remove(shared_ptr<pq> queue)
{
    // Create a default string value to return
    string returnVal;
    // Handle the case where the heap is empty and set the string (returnVal) to empty
    if (queue->heapString.size() == 0)
    {
        returnVal = "";
    }
    // Otherwise search for the highest priority element in the queue
    else
    {
        // Create empty max priority value and index of value
        float maxVal = 0;
        int index = 0;
        // Search for the max priority element and find its index
        for (int i = 0; i < queue->heapString.size(); i++)
        {
            if (maxVal <= queue->heapPriority.at(i))
            {
                maxVal = queue->heapPriority.at(i);
                index = i;
            }
        }
        // Update the return value to the element at the index in (heapString)
        returnVal = queue->heapString.at(index);
        // Delete the priority value and text value from their respective vectors
        queue->heapString.erase(queue->heapString.begin() + index);
        queue->heapPriority.erase(queue->heapPriority.begin() + index);
    }
    // Return string value that is removed from priority queue
    return returnVal;
}

/*  Peek - Returns the top element of the queue
 *   Input:
 *       queue - Smart pointer of object type (pq) that represents the priority queue
 *   Algorithm:
 *       * Create an empty return element that will represent the top of the queue
 *       * Update the afforementioned value to the top of the queue
 *       * Return the top of the queue
 *   Output:
 *       headVal - String value that represents the top of the queue
 */
string PriorityQueue::Peek(shared_ptr<pq> queue)
{
    // Create return element that represents the top of the queue
    string headVal;
    // Handle the case where the queue is empty and set (headVal) to empty if it is empty
    if (queue->heapString.size() == 0)
    {
        headVal = "";
    }
    // Grab the top element of the queue and set it equal to (headVal)
    else
    {
        headVal = queue->heapString.at(0);
    }
    // Return the value (headVal) that represents the top of the queue
    return headVal;
}