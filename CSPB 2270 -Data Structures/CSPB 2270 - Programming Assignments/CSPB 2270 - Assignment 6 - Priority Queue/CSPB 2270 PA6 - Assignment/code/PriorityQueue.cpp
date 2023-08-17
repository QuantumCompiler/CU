#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(){
    // YOUR CODE HERE
}

PriorityQueue::~PriorityQueue(){
    // You don't need to add anything here
}

// Implement this after defining struct in .h file
shared_ptr<pq> PriorityQueue::InitPriorityQueue(){
    // YOUR CODE HERE
    return shared_ptr<pq>(NULL);    // replace this line with your own code
}

// Implement this second
void PriorityQueue::Insert(shared_ptr<pq> queue, string text, float priority){
    // YOUR CODE HERE
}

// Implement this third
string PriorityQueue::Remove(shared_ptr<pq> queue){
    // YOUR CODE HERE
    return "reuslt";    // replace this line with your own code
}

// Implement this last
string PriorityQueue::Peek(shared_ptr<pq> queue){
    // YOUR CODE HERE
    return "reuslt";    // replace this line with your own code
}