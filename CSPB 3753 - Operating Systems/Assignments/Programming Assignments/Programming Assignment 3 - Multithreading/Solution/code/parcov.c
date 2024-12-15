/*
    parcov.c - Functions for parsing and converting domain names

    Author: Taylor Larrechea
    Date - 11/14/2024
    Class: CSPB 3753 Operating Systems
    Professor: Dr. David Knox

    Functions:
        parser - Function that reads domain names from input files and adds them to the global buffer
        multi_parser - Function that creates multiple parser threads
        converter - Function that performs DNS lookups on domain names in the buffer
        multi_converter - Function that creates multiple converter threads
*/

// Includes
#include "parcov.h"

// Buffer and Index
char* buffer[BUFFER_SIZE];
int buffer_index = 0;
int parsing_done = 0;

// Mutex and condition variables
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

// Shared file data
int file_idx = 0;
pthread_mutex_t file_idx_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

/*  parser - Function that reads domain names from input files and adds them to the global buffer
        Input:
            arg - Pointer to a ThreadArgs struct
        Algorithm:
            * Cast the input argument to a ThreadArgs struct
            * Create a LogData struct for logging
            * Create a local buffer for log messages
            * Log the start of parsing
            * Loop through each file
                * Lock the file index mutex
                    * Print error message if locking fails
                * Check if the index is out of bounds
                    * Print message if all files have been parsed
                    * Unlock the file index mutex
                    * Break out of the loop
                * Create a pointer to the input file and increment the index
                * Open the input file
                    * Print error message if the file could not be opened
                    * Log the error
                    * Continue to the next file
                * Process each line in the file
                    * Trim the newline character
                    * Lock the buffer to add the domain
                        * Print error message if locking fails
                    * Wait if buffer is full
                    * Check buffer_index bounds before adding to buffer
                        * Print error message if buffer_index is out of bounds
                        * Unlock the buffer
                        * Exit the program
                    * Add the domain to the buffer
                    * Check if strdup failed
                        * Print error message if strdup failed
                        * Unlock the buffer
                        * Exit the program
                    * Increment the buffer index
                    * Log the domain added
                    * Signal that the buffer is not empty
                    * Unlock the buffer
                * Close the input file
                * Print message that the file has been parsed
                * Log completion of file parsing
            * Return NULL
        Output:
            No return value generated
*/
void* parser(void* arg) {
    // Cast the input argument to ThreadArgs
    ThreadArgs* args = (ThreadArgs*)arg;
    // Create a LogData struct for logging
    LogData logData;
    logData.fileName = args->output_file;
    // Local buffer for log messages
    char message[256];
    // Get the current thread ID
    pthread_t tid = pthread_self();
    // Log the start of parsing
    snprintf(message, sizeof(message), "Parser thread %lu started parsing input file(s)\n", (uintptr_t)tid);
    logData.input = message;
    logWriter(&logData);
    // Loop through each file
    while (1) {
        // Lock the file index mutex
        if (pthread_mutex_lock(&file_idx_mutex) != 0) {
            fprintf(stderr, "Error: Could not lock file index mutex\n");
            exit(1);
        }
        // Check if the index is out of bounds
        if (file_idx >= args->num_files) {
            fprintf(stdout, "All files have been parsed\n");
            // Unlock the file index mutex
            if (pthread_mutex_unlock(&file_idx_mutex) != 0) {
                fprintf(stderr, "Error: Could not unlock file index mutex\n");
                exit(1);
            }
            break;
        }
        // Create pointer to the input file and increment the index
        char* inputFile = args->input_files[file_idx];
        file_idx++;
        if (pthread_mutex_unlock(&file_idx_mutex) != 0) {
            fprintf(stderr, "Error: Could not unlock file index mutex\n");
            exit(1);
        }
        // Open the input file
        FILE *file = fopen(inputFile, "r");
        // File failed to open
        if (!file) {
            printf("Error: Could not open file %s\n", inputFile);
            // Log the error
            snprintf(message, sizeof(message), "Error: Could not open input file %s\n", inputFile);
            logData.input = message;
            logWriter(&logData);
            continue;
        }
        // Process each line in the file
        char domain[256];
        while (fgets(domain, sizeof(domain), file)) {
            // Trim the newline character
            domain[strcspn(domain, "\n")] = 0;
            // Lock the buffer to add the domain
            if (pthread_mutex_lock(&buffer_mutex) != 0) {
                fprintf(stderr, "Error: Could not lock buffer mutex\n");
                exit(1);
            }
            // Wait if buffer is full
            while (buffer_index >= BUFFER_SIZE) {
                pthread_cond_wait(&buffer_not_full, &buffer_mutex);
            }
            // Check buffer_index bounds before adding to buffer
            if (buffer_index < 0 || buffer_index >= BUFFER_SIZE) {
                fprintf(stderr, "Error: buffer_index out of bounds: %d\n", buffer_index);
                pthread_mutex_unlock(&buffer_mutex);
                exit(1);
            }
            // Add the domain to the buffer
            buffer[buffer_index] = strdup(domain);
            // Check if strdup failed
            if (buffer[buffer_index] == NULL) {
                fprintf(stderr, "Error: strdup failed for domain %s\n", domain);
                if (pthread_mutex_unlock(&buffer_mutex) != 0) {
                    fprintf(stderr, "Error: Could not unlock buffer mutex after failed strdup\n");
                    exit(1);
                }
                exit(1);
            }
            printf("Domain added to buffer at index %d from file %s: %s\n", buffer_index, inputFile, domain);
            // Increment the buffer index
            buffer_index++;
            // Log the domain added
            snprintf(message, sizeof(message), "Domain added to buffer at index %d from file %s: %s\n", buffer_index - 1, inputFile, domain);
            logData.input = message;
            logWriter(&logData);
            // Signal that the buffer is not empty
            pthread_cond_signal(&buffer_not_empty);
            // Unlock the buffer
            if (pthread_mutex_unlock(&buffer_mutex) != 0) {
                fprintf(stderr, "Error: Could not unlock buffer mutex\n");
                exit(1);
            }
        }
        // Close the input file
        fclose(file);
        printf("File %s has been parsed\n", inputFile);
        // Log completion of file parsing
        snprintf(message, sizeof(message), "File %s parsed\n", inputFile);
        logData.input = message;
        logWriter(&logData);
    }
    // Signal parsing completion after all parser threads have completed
    if (pthread_mutex_lock(&buffer_mutex) != 0) {
        fprintf(stderr, "Error: Could not lock buffer mutex\n");
        exit(1);
    }
    // Signal that parsing is done
    parsing_done = 1;
    if (pthread_cond_broadcast(&buffer_not_empty) != 0) {
        fprintf(stderr, "Error: Could not broadcast buffer_not_empty\n");
        exit(1);
    }
    // Unlock the buffer
    if (pthread_mutex_unlock(&buffer_mutex) != 0) {
        fprintf(stderr, "Error: Could not unlock buffer mutex\n");
        exit(1);
    }
    // Return NULL
    return NULL;
}

/*  multi_parser - Function that creates multiple parser threads
        Input:
            threads - Integer representing the number of threads to create
            input_files - Pointer to a pointer to a character representing the input files
            num_files - Integer representing the number of input files
            log - Pointer to a character representing the output file
        Algorithm:
            * Create a ThreadArgs struct with the input arguments
            * Create parser threads
            * Join parser threads
            * Signal parsing completion after all parser threads have completed
        Output:
            No return value generated
*/
void multi_parser(int threads, char** input_files, int num_files, char* log) {
    // Thread args
    ThreadArgs args;
    args.input_files = input_files;
    args.num_files = num_files;
    args.output_file = log;
    // Create parser threads
    pthread_t parser_threads[threads];
    for (int i = 0; i < threads; i++) {
        if (pthread_create(&parser_threads[i], NULL, parser, &args) != 0) {
            perror("Error: Could not create parser thread");
            exit(1);
        }
    }
    // Join parser threads
    for (int i = 0; i < threads; i++) {
        if (pthread_join(parser_threads[i], NULL) != 0) {
            perror("Error: Could not join parser thread");
            exit(1);
        }
    }
}

/*  converter - Function that performs DNS lookups on domain names in the buffer
        Input:
            arg - Pointer to a character representing the output file
        Algorithm:
            * Cast the input argument to a character pointer
            * Create a LogData struct for logging
            * Create a local buffer
            * Log the start of conversion
            * Loop until parsing is done and buffer is empty
                * Lock the buffer
                    * Print error message if locking fails
                * Wait if buffer is empty and parsing not done
                * Exit if parsing is done and buffer is empty
                * Retrieve domain 
                * Buffer is empty
                    * Print error message
                    * Unlock the buffer
                    * Break out of the loop
                * Pointer to buffer domain
                * Signal that buffer has space
                * Unlock the buffer
                * Add DNS lookup code
                * Check for errors
                    * Print the error
                    * Log the error
                * No errors
                    * Print the IP address
                    * Log the IP address
                * Free the memory allocated for the domain
            * Log completion of conversion
            * Return NULL
        Output:
            No return value generated
*/
void* converter(void* arg) {
    // Cast the input argument to a character pointer
    char* outputFile = (char*)arg;
    LogData logData;
    logData.fileName = outputFile;
    // Declare local buffer
    char message[256];
    // Get the current thread ID
    pthread_t tid = pthread_self();
    // Log the start of conversion
    snprintf(message, sizeof(message), "Converter thread %lu started processing domains\n", (uintptr_t)tid);
    logData.input = message;
    logWriter(&logData);
    // Loop until parsing is done and buffer is empty
    while (1) {
        // Lock the buffer
        if (pthread_mutex_lock(&buffer_mutex) != 0) {
            fprintf(stderr, "Error: Could not lock buffer mutex\n");
            break;
        }
        // Wait if buffer is empty and parsing not done
        while (buffer_index <= 0 && !parsing_done) {
            pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
        }
        // Exit if parsing is done and buffer is empty
        if (parsing_done && buffer_index <= 0) {
            if (pthread_mutex_unlock(&buffer_mutex) != 0) {
                fprintf(stderr, "Error: Could not unlock buffer mutex\n");
                exit(1);
            }
            break;
        }
        // Retrieve domain 
        if (buffer_index > 0) {
            buffer_index--;
        } 
        // Buffer is empty
        else {
            fprintf(stderr, "Error: buffer_index out of bounds in converter\n");
            pthread_mutex_unlock(&buffer_mutex);
            break;
        }
        // Pointer to buffer domain
        char* domain = buffer[buffer_index];
        buffer[buffer_index] = NULL;
        // Signal that buffer has space
        if (pthread_cond_signal(&buffer_not_full) != 0) {
            fprintf(stderr, "Error: Could not signal buffer_not_full\n");
            if (pthread_mutex_unlock(&buffer_mutex) != 0) {
                fprintf(stderr, "Error: Could not unlock buffer mutex\n");
            }
            break;
        }
        // Unlock the buffer
        if (pthread_mutex_unlock(&buffer_mutex) != 0) {
            fprintf(stderr, "Error: Could not unlock buffer mutex\n");
            break;
        }
        // Add DNS lookup code
        char ipstr[INET6_ADDRSTRLEN];
        int res = dnslookup(domain, ipstr, sizeof(ipstr));
        // Check for errors
        if (res == UTIL_FAILURE) {
            // Print the error
            fprintf(stderr, "dnslookup error: %s\n", domain);
            // Log the error
            snprintf(message, sizeof(message), "No IP address found for domain: %s\n", domain);
            logData.input = message;
            logWriter(&logData);
        } 
        // No errors
        else {
            // Print the IP address
            printf("IP address for %s: %s\n", domain, ipstr);
            // Log the IP address
            snprintf(message, sizeof(message), "IP address for %s: %s\n", domain, ipstr);
            logData.input = message;
            logWriter(&logData);
        }
        // Free the memory allocated for the domain
        free(domain);
    }
    // Log completion of conversion
    snprintf(message, sizeof(message), "Converter thread %lu finished processing all domains\n", (uintptr_t)tid);
    logData.input = message;
    logWriter(&logData);
    return NULL;
}

/*  multi_converter - Function that creates multiple converter threads
        Input:
            threads - Integer representing the number of threads to create
            log - Pointer to a character representing the output file
        Algorithm:
            * Create converter threads
            * Join converter threads
        Output:
            No return value generated
*/
void multi_converter(int threads, char* log) {
    // Pointer to the output file
    char* outputFile = log;
    // Create converter threads
    pthread_t converter_threads[threads];
    for (int i = 0; i < threads; i++) {
        if (pthread_create(&converter_threads[i], NULL, converter, outputFile) != 0) {
            perror("Error: Could not create converter thread");
            exit(1);
        }
    }
    // Join converter threads
    for (int i = 0; i < threads; i++) {
        if (pthread_join(converter_threads[i], NULL) != 0) {
            perror("Error: Could not join converter thread");
            exit(1);
        }
    }
}