#ifndef PRIORITYQUEUE_H__
#define PRIORITYQUEUE_H__

#include <memory>
#include <string>
#include <vector>

using namespace std;

// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
struct pq {
    // Vector to store strings and priority value
    vector<string> heapString;
    vector<float> heapPriority;

    /*  percolateUp - Pushes elements up in a vector based off of specific condtions
    *   Input:
    *       index - Integer value that represents the index of a where an element is supposed to start percolating
    *   Algorithm:
    *       * Begin iterating through the vector if the index is greater than zero
    *       * Calculate the parent index
    *       * Terminate the loop if the current elements priority is less than or equal to that of its parent
    *       * Otherwise, swap the elements at the current index with the parents index
    *   Output:
    *       This function does not return a value
    */
    void percolateUp(int index) {
        // Begin iterating through the vector
        while (index > 0) {
            // Calculate the parent index
            int parentIndex = (index - 1) / 2;
            // Terminate the loop if the current elements priority is less than or equal to the its parents priority
            if (this->heapPriority.at(index) <= this->heapPriority.at(parentIndex)) {
                return;
            }
            // Proceed to swap elements at current index and parent index, update index to parent index
            else {
                swap(this->heapString.at(index), this->heapString.at(parentIndex));
                swap(this->heapPriority.at(index), this->heapPriority.at(parentIndex));
                index = parentIndex;
            }
        }
    }
};


class PriorityQueue {
public:
    // constructor, you should set all values in array to zero
    PriorityQueue();

    //deconstructor, you don't need to add anything here since you are gonna use smart pointers
    ~PriorityQueue();

    // init_priority_queue allocates memory for a pq structure (which you
    // are responsble for defining above. It is
    // completely up to you how this should work.
    shared_ptr<pq> InitPriorityQueue();

    // insert adds the given text to the queue, using the specified
    // priority. If there is a tie, the given string should be placed at
    // the back of the group that it ties with, so all other strings with
    // this priority will be removed first.
    void Insert(shared_ptr<pq> queue, string text, float priority);

    // remove will access the highest priority element in the queue,
    // remove it from the queue, and return it. if the queue is empty it
    // should return the empty string.
    string Remove(shared_ptr<pq> queue);

    // ppek will access the highest priority element in the queue and
    // return it without modifying the queue. if the queue is empty it
    // should return the empty string.
    string Peek(shared_ptr<pq> queue);    

private:
    // you can add add more private member variables and member functions here if you need
};

#endif  // PRIORITYQUEUE_H__
