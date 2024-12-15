///////////////////////////////////////////////////////////////////////////////
// Author: Taylor Larrechea
// Date: 10/23/24
//
// Usage:
//      shared_api <filename> ....
//      Make sure files are not empty (blanket tests included in makefile)
//          make - Do everything, dude
//          make api - Creates shared api and tests with default files
//          make example - Creates example and tests with default files
//          make testAPI - Builds and tests
//          make testExample - Builds and tests
//          make clean - Cleans up the directory
///////////////////////////////////////////////////////////////////////////////
#include "shared_api.h"

static struct resource thread_resource;

/*  GetNextLine - Function that returns the next line from the file
        Input:
            None
        Algorithm:
            * Lock the mutex
            * Check if all files have been processed
                * If so, unlock the mutex and return NULL
            * Open the next file
                * If the file pointer is NULL, open the file in read mode
                * Check for null
                    * Increment the file index
                    * Unlock the mutex
                    * Make recursive call
            * Read the next line of the file
                * Allocate memory for the line
                * Check for null
                    * Read the line
                    * Check for null
                        * Close the file
                        * Increment the file index
                        * Unlock the mutex
                        * Make recursive call
            * Unlock the mutex
            * Return the line
        Output:
            Returns the next line from the file (caller must free memory)
*/
char *GetNextLine() {
    // Lock the mutex
    pthread_mutex_lock(&thread_resource.mutex);
    // All files processed
    if (thread_resource.current_file >= thread_resource.n_filenames) {
        // Unlock the mutex
        pthread_mutex_unlock(&thread_resource.mutex);
        return NULL;
    }
    // Open next file
    if (thread_resource.file_ptr == NULL) {
        // Open file in read
        thread_resource.file_ptr = fopen(thread_resource.filenames[thread_resource.current_file], "r");
        // Check for null
        if (thread_resource.file_ptr == NULL) {
            // Increment file index
            thread_resource.current_file++;
            // Unlock the mutex
            pthread_mutex_unlock(&thread_resource.mutex);
            return GetNextLine();
        }
    }
    // Read next line of file
    char *readLine = malloc(1024);
    // Check for null
    if (readLine == NULL) {
        printf("Failed to allocate memory for readLine\n");
        // Unlock the mutex
        pthread_mutex_unlock(&thread_resource.mutex);
        return NULL;
    }
    // Read line
    if (fgets(readLine, 1024, thread_resource.file_ptr) == NULL) {
        // Close file
        fclose(thread_resource.file_ptr);
        // Increment file index
        thread_resource.current_file++;
        // Unlock the mutex
        pthread_mutex_unlock(&thread_resource.mutex);
        return GetNextLine();
    }
    // Unlock the mutex
    pthread_mutex_unlock(&thread_resource.mutex);
    // Return the lines
    return readLine;
}

/*  Initialize - Initializes a shared resource struct with a number of files and list of filenames
        Input:
            filename_list - List of filenames
            n_filenames - Number of filenames
        Algorithm:
            * Allocate memory for the filenames
                * Check allocation and return -1 if failed
            * Copy the filenames
                * Copy string from input parameter to the resource struct
                * Check for allocation and return -1 if failed
            * Set up the resource struct
                * Set the number of filenames
                * Set the current file index
                * Set the file pointer to NULL
            * Initialize the mutex for the resource struct
                * Check for failure and return -1 if failed
            * Return 0 if successful
        Output:
            Returns 0 if successful, -1 if failed for initialization of the shared resource
*/
int Initialize(char ** filename_list, int n_filenames) {
    // Init memory for files
    thread_resource.filenames = malloc(sizeof(char*) * n_filenames);
    // Check allocation
    if (thread_resource.filenames == NULL) {
        printf("Failed to allocate memory for filenames\n");
        return -1;
    }
    // Copy the filenames
    for (int i = 0; i < n_filenames; i++) {
        // Return pointer of copied string
        thread_resource.filenames[i] = strdup(filename_list[i]);
        if (thread_resource.filenames[i] == NULL) {
            printf("Failed to copy filename\n");
            return -1;
        }
    }
    // Set up resource struct
    thread_resource.n_filenames = n_filenames;
    thread_resource.current_file = 0;
    thread_resource.file_ptr = NULL;
    // Initialize mutex
    if (pthread_mutex_init(&thread_resource.mutex, NULL) != 0) {
        printf("Failed to create mutex\n");
        return -1;
    }
    // Return success
    return 0;
}

/*  ShowNextLine - Function that shows the next line from the file
        Input:
            arg - Void pointer to the thread id
        Algorithm:
            * Get the next line with the GetNextLine function
            * While the line is not null
                * Print the line
                * Free the line
            * Return NULL
        Output:
            Returns NULL
*/
void *ShowNextLine(void *arg) {
    // Get the next line
    char *line = GetNextLine();
    // While the line is not null
    while ((line = GetNextLine()) != NULL) {
        // Print the line
        printf("Thread %ld: %s", (long)arg, line);
        // Free the line
        free(line);
    }
    // Print finished reading
    printf("Thread %ld finished reading.\n", (intptr_t)arg);
    // Return NULL
    return NULL;
}

/*  Terminate - Function that terminates the shared resource
        Input:
            None
        Algorithm:
            * Lock the mutex
            * Close the files
                * Check for null
            * Free the filenames
            * Free the list of filenames
            * Unlock the mutex
            * Destroy the mutex
                * Check for failure and return -1 if failed
            * Return 0 if successful
        Output:
            Returns 0 if successful, -1 if failed for termination of the shared resource struct
*/
int Terminate() {
    // Lock the mutex
    pthread_mutex_lock(&thread_resource.mutex);
    // Close the files
    if (thread_resource.file_ptr != NULL) {
        fclose(thread_resource.file_ptr);
    }
    // Free filenames
    for (int i = 0; i < thread_resource.n_filenames; i++) {
        free(thread_resource.filenames[i]);
    }
    // Free list of filenames
    free(thread_resource.filenames);
    // Unlock the mutex
    pthread_mutex_unlock(&thread_resource.mutex);
    // Destroy the mutex
    if (pthread_mutex_destroy(&thread_resource.mutex) != 0) {
        printf("Failed to destroy mutex\n");
        return -1;
    }
    // Return success
    return 0;
}

int main(int argc, char* argv[]) {
    // Random number of threads
    int randThread = 10;
    // Not enough arguments
    if (argc <= 2) {
        printf("Usage: %s <filename> ...\n", argv[0]);
        return -1;
    }
    // Initialize the shared resource
    if (Initialize(&argv[1], argc - 1) != 0) {
        printf("Failed to initialize shared resource.\n");
        return -1;
    } 
    // Initialization succeeded
    else {
        printf("Shared resource initialized successfully.\n");
    }
    // Create threads
    pthread_t threads[20];
    for (int i = 0; i < randThread; i++) {
        // Create thread (print error if failed)
        if (pthread_create(&threads[i], NULL, ShowNextLine, (void*)(intptr_t)i) != 0) {
            printf("Failed to create thread %d\n", i);
        } 
        // Thread created successfully
        else {
            printf("Thread %d created successfully\n", i);
        }
    }
    // Wait for threads to finish
    for (int i = 0; i < randThread; i++) {
        pthread_join(threads[i], NULL);
    }
    // Terminate all resources
    if (Terminate() != 0) {
        printf("Failed to terminate shared resource.\n");
        return -1;
    }
    return 0;
}