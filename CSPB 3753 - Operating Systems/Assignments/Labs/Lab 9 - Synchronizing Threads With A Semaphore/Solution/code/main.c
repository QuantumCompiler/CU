/*
    main.c - Main file for program

    Author: Taylor Larrechea
    Date: 10/30/24

    Usage: ./main <number of readers> <number of writers>
*/
#include <unistd.h>
#include "lib/includes.h"
#include "lib/read.h"
#include "lib/write.h"

// Global variables
dispatch_semaphore_t read_mutex; // Semaphore for read access
dispatch_semaphore_t resource_access; // Semaphore for write access
dispatch_semaphore_t turnstile; // Semaphore for turnstile (starvation prevention)

/*  main - Main function for program
        Input:
            int argc - Number of command line arguments
            char *argv[] - Array of command line arguments
        Algorithm:
            * Parse command line arguments
            * Validate command line arguments
            * Initialize semaphores
            * Initialize threads
            * Create custom_reader threads
            * Create custom_writer threads
            * Join the custom_reader threads
            * Join the custom_writer threads
            * Release semaphores
            * Return 0
        Output:
            * 0 if successful, -1 if unsuccessful
*/
int main(int argc, char *argv[]) {
    // Check for number of command line arguments
    if (argc != 3) {
        printf("Usage: %s <number of readers> <number of writers>\n", argv[0]);
        return -1;
    }
    // Parse command line arguments
    int num_readers = atoi(argv[1]);
    int num_writers = atoi(argv[2]);
    // Validate command line arguments
    if (num_readers < 0 || num_writers < 0) {
        if (num_readers < 0) {
            printf("Number of readers must be a positive integer\n");
        }
        if (num_writers < 0) {
            printf("Number of writers must be a positive integer\n");
        }
        return -1;
    }
    // Initialize semaphores
    read_mutex = dispatch_semaphore_create(1);
    resource_access = dispatch_semaphore_create(1);
    turnstile = dispatch_semaphore_create(1);
    if (read_mutex == NULL || resource_access == NULL || turnstile == NULL) {
        printf("Failed to create semaphores\n");
        return -1;
    }
    // Initialize threads
    pthread_t reader_threads[num_readers];
    pthread_t writer_threads[num_writers];
    // Create custom_reader threads
    for (int i = 0; i < num_readers; i++) {
        if (pthread_create(&reader_threads[i], NULL, custom_reader, (void *)(long)i) != 0) {
            printf("Failed to create custom_reader thread\n");
            return -1;
        }
    }
    // Create custom_writer threads
    for (int i = 0; i < num_writers; i++) {
        if (pthread_create(&writer_threads[i], NULL, custom_writer, (void *)(long)i) != 0) {
            printf("Failed to create custom_writer thread\n");
            return -1;
        }
    }
    // Join the custom_reader threads
    for (int i = 0; i < num_readers; i++) {
        if (pthread_join(reader_threads[i], NULL) != 0) {
            printf("Failed to join custom_reader thread\n");
            return -1;
        }
    }
    // Join the custom_writer threads
    for (int i = 0; i < num_writers; i++) {
        if (pthread_join(writer_threads[i], NULL) != 0) {
            printf("Failed to join custom_writer thread\n");
            return -1;
        }
    }
    // Release semaphores
    dispatch_release(read_mutex);
    dispatch_release(resource_access);
    dispatch_release(turnstile);
    // Exit message
    printf("All threads have finished execution.\n");
    return 0;
}