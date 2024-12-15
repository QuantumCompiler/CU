/*
    write.c - This file contains the implementation of the custom_writer function for a shared resource
*/

#include "includes.h"
#include <unistd.h>

extern dispatch_semaphore_t resource_access; // Semaphore for write access

/*  custom_writer - Writes to a shared resource
        Input:
            arg - The thread id
        Algorithm:
            * Get the thread ID
            * Simulate time passing
            * Acquire the turnstile semaphore so that no new readers can enter
            * Acquire the resource_access semaphore so that no other writers can write
            * Release the turnstile semaphore so that new readers can enter
            * Acquire the read_mutex semaphore so that the read count can be updated
            * Get the current read count
            * Release the read_mutex semaphore so that other readers can update the read count
            * Print the current writer and reader count
            * Simulate time passing
            * Print that the writer has finished writing
            * Release the resource_access semaphore so that other writers can write
        Output:
            This function writes to a shared resource
*/
void *custom_writer(void *arg) {
    // Get the thread id
    long thread_id = (long)arg;
    // Simulate time passing
    sleep(rand() % 5 + 1);
    // Acquire the turnstile semaphore
    dispatch_semaphore_wait(turnstile, DISPATCH_TIME_FOREVER);
    // Acquire the resource_access semaphore
    dispatch_semaphore_wait(resource_access, DISPATCH_TIME_FOREVER);
    // Release the turnstile semaphore
    dispatch_semaphore_signal(turnstile);
    // Acquire the read_mutex semaphore
    dispatch_semaphore_wait(read_mutex, DISPATCH_TIME_FOREVER);
    // Get the current read count
    int current_read_count = read_count;
    // Release the read_mutex semaphore
    dispatch_semaphore_signal(read_mutex);
    // Print the current writer and reader count
    printf("Writer %ld is currently writing a critical section\n", thread_id);
    printf("Current reader count: %d\n", current_read_count);
    // Simulate time passing
    sleep(rand() % 5 + 1);
    // Print that the writer has finished writing
    printf("Writer %ld has finished writing the critical section\n", thread_id);
    // Release the resource_access semaphore
    dispatch_semaphore_signal(resource_access);
    pthread_exit(NULL);
    return NULL;
}