///////////////////////////////////////////////////////////////////////////////
// Author: Taylor Larrechea
// Date: 09-26-2024	
///////////////////////////////////////////////////////////////////////////////

/*
    This file contains the functions to handle data and input from the command line.
*/

// Includes

#include "data.h"

/*  retrieve_cli - Gets input from command line and stores it in a buffer
        Input:
            None - Void
        Algorithm:
            * Define the initial buffer size
            * Attempt to allocate a buffer of the initial size times the size of a char
                * If the allocation fails, print an error message and return NULL
            * Print something to console if in debugging mode and allocation succeeds
            * Set the initial position of the buffer to 0
            * Read characters from the input until a newline or EOF is detected
                * Print the character read if in debugging mode
                * Reallocate buffer it is full
                    * Increase the buffer size
                    * Create a new buffer
                        * If the new buffer is null, print an error message and free the old buffer
                        * If the new buffer is not null, print the new buffer size and the current buffer
                    * Print a message if in debugging mode
                    * Update the buffer to the new buffer
                * Add the character to the buffer
            * Null-terminate the string
            * Determine if there is no input, if there is no input, print an error message and free the buffer
            * Print the final buffer and the final allocated size if in debugging mode
        Output:
            buffer - A pointer to a buffer containing the input from the command line
*/
static char *retrieve_cli(void) {
    printf("shellLabShell> ");
    int allocated_size = BUFFER_GROWTH_SIZE;
    // Allocate memory for the buffer
    char *buffer = (char *) malloc(allocated_size * sizeof(char));
    // Allocation failed
	if (buffer == NULL) {
        perror("Memory allocation failed\n");
		return NULL;
	} 
    // Allocation succeeded
    else {
        if (DEBUG > 0) {
            printf("Buffer allocated successfully: %lu\n", allocated_size * sizeof(char));
        }
    }
	int position = 0; // Position in the buffer
	int ch; // Character read from the input
    // Read the the input until a newline or EOF is detected
	while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (DEBUG > 0) {
            printf("Character read: %c\n", ch);
        }
        // Reallocate buffer if it is full
		if (position >= allocated_size - 1) {
            if (DEBUG > 0) {
                printf("Buffer full, reallocating memory. Current size: %lu\n", allocated_size * sizeof(char));
            }
            // Increase the size of the buffer
			allocated_size += BUFFER_GROWTH_SIZE;
            // Create new buffer
            char *new_buffer = (char *) realloc(buffer, allocated_size * sizeof(char));
            // New buffer is null
			if (new_buffer == NULL) {
                perror("Memory reallocation failed\n");
				free(buffer);
				return NULL;
			}
            // New buffer is not null
            else {
                if (DEBUG > 0) {
                    printf("New allocated buffer size: %lu\n", allocated_size * sizeof(char));
                    printf("Current buffer: %s\n", new_buffer);
                }
            }
            // Update buffer to new buffer
			buffer = new_buffer;
		}
        // Add character to the buffer
		buffer[position++] = (char) ch;
	}
    // Null-terminate the string
	buffer[position] = '\0';
    // No input detected
	if (position == 0 && ch == EOF) {
		free(buffer);
        perror("No input detected\n");
		return NULL;
	}
    // Print final buffer if in debugging mode
    if (DEBUG > 0) {
        printf("Final Buffer: %s\n", buffer);
        printf("Final allocated size: %lu\n", allocated_size * sizeof(char));
    }
    return buffer;
}