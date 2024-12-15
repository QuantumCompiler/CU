/*
    * includes.h - Header file for the libraries and global variables
*/

#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h>

extern dispatch_semaphore_t read_mutex; // Semaphore for read access
extern dispatch_semaphore_t resource_access; // Semaphore for write access
extern dispatch_semaphore_t turnstile; // Semaphore for turnstile (starvation prevention)
int read_count; // Number of readers currently reading

#endif // INCLUDES_H