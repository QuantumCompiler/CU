///////////////////////////////////////////////////////////////////////////////
// Header file for shared_api.c
//
// Author: Taylor Larrechea
// Date: 10/21/2024
//
// Usage: None
///////////////////////////////////////////////////////////////////////////////
#ifndef SHARED_API_H
#define SHARED_API_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

/*  resource - Struct that holds the shared resource for the threads
        filenames - List of filenames
        n_filenames - Number of filenames
        current_file - Current file index
        file_ptr - File pointer
        mutex - Mutex
*/
struct resource {
    char **filenames;       // List of filenames
    int n_filenames;        // Number of filenames
    int current_file;       // Current file index
    FILE *file_ptr;         // File pointer
    pthread_mutex_t mutex;  // Mutex
};

// GetNextLine - Function that gets the next line from the shared resource struct
char *GetNextLine();

// Initialize - Initializes a shared resource struct with a number of files and list of filenames
int Initialize(char ** filename_list, int n_filenames);

// ShowNextLine - Function that shows the next line from the file
void *ShowNextLine(void *arg);

// Terminate - Function that terminates the shared resource
int Terminate();

#endif // SHARED_API_H