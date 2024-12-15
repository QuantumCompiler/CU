/*
    buffer.h - Custom buffer file that holds shared resources and other data for the project

    Author: Taylor Larrechea
    Date - 11/14/2024
    Class: CSPB 3753 Operating Systems
    Professor: Dr. David Knox

    Globals:
        BUFFER_SIZE - The size of the buffer in bytes
        buffer - The buffer that holds the information shared between converter and parser threads
        buffer_index - The index of the buffer that is being used
        buffer_mutex - Mutex that locks the buffer
        buffer_not_full - Condition variable that signals when the buffer is not full
        buffer_not_empty - Condition variable that signals when the buffer is not empty
        parsing_done - Flag that signals when parsing is complete
        file_idx - Index of the file being processed
        file_idx_mutex - Mutex that locks the file index
        log_mutex - Mutex that locks the log file

    Shared Resources:
        buffer - Shared between both the converter and parser threads, needs own mutex
        buffer_index - Shared between both the converter and parser threads
        file_idx - Shared between the parser threads, needs own mutex
        parsing_done - Shared between the converter and parser threads
*/
#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>

// Buffer size
#define BUFFER_SIZE 1024

// Buffer and Index
extern char* buffer[BUFFER_SIZE];
extern int buffer_index;

// Mutex and condition variables
extern pthread_mutex_t buffer_mutex;
extern pthread_mutex_t file_idx_mutex;
extern pthread_mutex_t log_mutex;
extern pthread_cond_t buffer_not_full;
extern pthread_cond_t buffer_not_empty;

// Parsing completion flag
extern int parsing_done;

// Shared resource data
extern int file_idx;

#endif // BUFFER_H