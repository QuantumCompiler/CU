/*
    * read.c - This file contains the implementation of the custom_reader function
*/

#include "includes.h"
#include <unistd.h>

/* custom_reader - Reads from a shared resource
    Input:
        arg - The thread id
    Algorithm:
        * Get the thread id
        * Simulate time passing
        * Acquire the turnstile so that no new readers can enter
        * Release the turnstile so that new readers can enter
        * Acquire the read mutex so that the read count can be updated
        * Increment the read count
        * If this is the first reader, acquire the resource access
        * Print the information of the reader
        * Release the read mutex so that other readers can update the read count
        * Simulate time passing
        * Acquire the read mutex so that the read count can be updated
        * Decrement the read count
        * Print the information of the reader
        * If this is the last reader, release the resource access
        * Release the read mutex so that other readers can update the read count
        * Exit the thread
    Output:
        This function simulates a reader reading from a shared resource
*/
void *custom_reader(void *arg) {
    // Get the thread id
    long thread_id = (long)arg;
    // Simulate time passing
    sleep(rand() % 5 + 1);
    // Acquire the turnstile
    dispatch_semaphore_wait(turnstile, DISPATCH_TIME_FOREVER);
    // Release the turnstile
    dispatch_semaphore_signal(turnstile);
    // Acquire the read mutex
    dispatch_semaphore_wait(read_mutex, DISPATCH_TIME_FOREVER);
    // Increment the read count
    read_count++;
    // If this is the first reader, acquire the resource access
    if (read_count == 1) {
        // Acquire the resource access
        dispatch_semaphore_wait(resource_access, DISPATCH_TIME_FOREVER);
    }
    // Print the information of the reader
    printf("Reader %ld is currently reading a critical section\n", thread_id);
    printf("Current reader count: %d\n", read_count);
    // Release the read mutex
    dispatch_semaphore_signal(read_mutex);
    // Simulate time passing
    sleep(rand() % 5 + 1);
    // Acquire the read mutex
    dispatch_semaphore_wait(read_mutex, DISPATCH_TIME_FOREVER);
    // Decrement the read count
    read_count--;
    // Print the information of the reader
    printf("Reader %ld has finished reading the critical section\n", thread_id);
    printf("Remaining reader count: %d\n", read_count);
    // If this is the last reader, release the resource access
    if (read_count == 0) {
        // Release the resource access
        dispatch_semaphore_signal(resource_access);
    }
    // Release the read mutex
    dispatch_semaphore_signal(read_mutex);
    pthread_exit(NULL);
    return NULL;
}