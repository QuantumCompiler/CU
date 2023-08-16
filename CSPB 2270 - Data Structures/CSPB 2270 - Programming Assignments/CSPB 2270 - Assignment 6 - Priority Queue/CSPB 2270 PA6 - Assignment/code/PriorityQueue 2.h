#ifndef PRIORITYQUEUE_H__
#define PRIORITYQUEUE_H__

#include <memory>
#include <string>

using namespace std;

// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
struct pq {
    // First implement this struct
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
