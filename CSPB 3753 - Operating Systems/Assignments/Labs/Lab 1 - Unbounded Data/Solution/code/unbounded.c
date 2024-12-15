///////////////////////////////////////////////////////////////////////////////
// Unbounded Data Structures Lab
///////////////////////////////////////////////////////////////////////////////
// Author:  Taylor Larrechea
// Date: 9-4-24
///////////////////////////////////////////////////////////////////////////////
// Creating unbounded data structures
//      Your task is to implement two functions for this lab:   
// 			`get_unbounded_line()` and 
// 			`get_value_table()`.   
// 		These functions will allocate the data structure needed from the heap 
// 		using `malloc`, `realloc`, and `free` function calls to manage the
// 		allocated space.   
//				
// 		Make sure that at the end of your program you have released any memory 
// 		that has been allocated (no memory leaks should be detected).
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

// The support functions in "debug_3753.h" use the DEBUG flag
// to modify the functions behavior.
#define DEBUG 1
//#define DEBUG 0
#include "debug_3753.h"

// Constants used in code
#define BUFFER_GROWTH_SIZE 16
#define TABLE_GROWTH_SIZE  8


///////////////////////////////////////////////////////////////////////////////
// get_unbounded_line()
//
// Read an input string of unknown length into a dynamically allocate memory
// buffer.  The buffer size can only grow by defined value BUFFER_GROWTH_SIZE.
//
//  Parameters  : none
//  Return value: pointer to a string buffer that is 0 terminated containing
//                all characters typed by user until a newline is detected.
//                Caller is responsible for deallocation of buffer.
//
//  Notes: - TO DO: handle newline in a quoted string during command line reading
//         - TO DO: handle dynamic growth during command line reading
///////////////////////////////////////////////////////////////////////////////

/*	get_unbounded_line - Reads an input string of unknown length into a dynamically allocated memory buffer.
		Input:
			none
		Algorithm:
			* Allocate a minimum amount of buffer space (in this case, BUFFER_GROWTH_SIZE)
			* Initialize buffer to empty string (position = 0)
			* Read input until newline or EOF
				* If the user hits EOF without any input
					* Free the buffer and return NULL
				* If the buffer is full
					* Extend the buffer by reallocating memory
				* Add character to buffer
			* Null-terminate the string
			* If the user hits EOF without any input
				* Free the buffer and return NULL
			* Return the buffer
		Output:
			Pointer to a string buffer that is 0 terminated containing all characters typed by user until a newline is detected
*/
static char *get_unbounded_line(void) {
	// Allocate a minimum amount of buffer space
    int allocated_size = BUFFER_GROWTH_SIZE;
    char *buffer = (char *) malloc(allocated_size * sizeof(char));
	// Memory allocation failed, return NULL
	if (buffer == NULL) {
		return NULL;
	}
	// Initialize buffer to empty string
	int position = 0;
	int ch;
	// Read input until newline or EOF
	while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
		// If no space left in the buffer, extend the buffer
		if (position >= allocated_size - 1) {
			allocated_size += BUFFER_GROWTH_SIZE;
			char *new_buffer = realloc(buffer, allocated_size * sizeof(char));
			// Memory reallocation failed
			if (new_buffer == NULL) {
				free(buffer);
				return NULL;
			}
			// Update buffer and allocated_size
			buffer = new_buffer;
		}
		// Add character to buffer
		buffer[position++] = (char) ch;
	}
	// Null-terminate the string
	buffer[position] = '\0';
	// If the user hits EOF without any input, return NULL
	if (position == 0 && ch == EOF) {
		free(buffer);
		return NULL;
	}
	// Return the buffer
    return buffer;
}

///////////////////////////////////////////////////////////////////////////////
// get_value_table(cmdline)
//
// Split the string into tokens.  The only character considered as a terminator
// is space character.  Returns an array of character pointers that is 
// dynamically allocated.
//
//  Parameters  : string of characters that are null byte terminated.
//  Return value: pointer to an array of pointers (null pointer terminated).
//                Caller is responsible for deallocation of token array.
//
//  Notes: - must have spaces around the pipe character and the background character
///////////////////////////////////////////////////////////////////////////////

/*	get_value_table - Splits the string into tokens and returns an array of integers
		Input:
			cmdline - String of characters that are null byte terminated
		Algorithm:
			* Allocate a minimum amount of buffer space (in this case, TABLE_GROWTH_SIZE)
			* Initialize table to empty
			* Tokenize the string by spaces
			* Parse each token and convert to integer
				* If the table is full
					* Expand the table by reallocating memory
				* Convert token to integer and add to table
			* Add sentinel value for end of array
			* Return the table
		Output:
			Pointer to an array of integers (null pointer terminated)
*/
int *get_value_table(char *command_line) {
	// Allocate a minimum amount of buffer space
	int allocated_size = TABLE_GROWTH_SIZE;
	int *table = (int *) malloc(allocated_size * sizeof(int));
	// Memory allocation failed, return NULL
	if (table == NULL) {
		return NULL;
	}
	// Initialize table to empty
	int position = 0;
	char *token = strtok(command_line, " ");
	// Parse each token and convert to integer
	while (token != NULL) {
		// If the table is full, expand the table
		if (position >= allocated_size) {
			allocated_size += TABLE_GROWTH_SIZE;
			int *new_table = realloc(table, allocated_size * sizeof(int));
			// Memory reallocation failed
			if (new_table == NULL) {
				free(table);
				return NULL;
			}
			// Update table and allocated_size
			table = new_table;
		}
		// Add the converted integer to the table
		table[position++] = atoi(token);
		token = strtok(NULL, " ");
	}
	// Ensure space for the sentinel value
	if (position >= allocated_size) {
		int *new_table = realloc(table, (allocated_size + 1) * sizeof(int));
		if (new_table == NULL) {
			free(table);
			return NULL;
		}
		table = new_table;
	}
	// Add sentinel value for end of array (INT_MAX in this case)
	table[position] = INT_MAX;
	// Return the dynamically allocated table
    return table;
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
/*	main - Main function for the program
		Input:
			argc - Number of command line arguments
			argv - Array of command line arguments
		Algorithm:
			* Make stdout and stderr file descriptors non-buffered
			* Initialize the running flag and prompt
			* Continue processing until the user hits EOF
				* Prompt the user for the next command line
				* Get the command line from the user
					* If the user hits EOF without any input
						* Print error message and set running to false
					* If the buffer is full
						* Print error message and set running to false
					* Process the command line
						* If no valid table values received
							* Print error message
						* Process the table values
							* Iterate through the table until the sentinel value (INT_MAX) is found
								* Count the number of values
								* Calculate the sum of the values
								* Find the minimum and maximum values
							* Results of the table processing to be displayed
								* If values were processed
									* Print the number of values, minimum, maximum, and average
								* If no values were processed
									* Print error message
					* Release the dynamically allocated data
						* If the command line buffer exists
							* Free the buffer
						* If the table exists
							* Free the table
		Output:
			None
*/
int main(int argc, char **argv) {
	// Make stdout and stderr file descriptors non-buffered
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	// Initialize the running flag and prompt
	int running = true;
	char *prompt = "%s> ";
	// Continue processing until the user hits EOF
	while (running && !feof(stdin)) {
		char *command_line = NULL;
		int *table = NULL;
		// Prompt the user for the next command line
		printf(prompt, "3753-Lab-KNOX");
		// Get the command line from the user
		command_line = get_unbounded_line();
		if (command_line == NULL) {
			DEBUG_PRINT("\nMissing data from user or memory allocation failed\n\n");
			running = false;
		}
		// Process the command line 
		else {
			table = get_value_table(command_line);
			if (table == NULL || table[0] == INT_MAX) {
				DEBUG_PRINT("\nNo valid table values received or memory allocation failed\n\n");
			} else {
				// Process the table values
				int count = 0;
				int sum = 0;
				int min = INT_MAX, max = INT_MIN;
				// Iterate through the table until the sentinel value (INT_MAX) is found
				for (int i = 0; table[i] != INT_MAX; i++) {
					count++;
					sum += table[i];
					if (table[i] < min) min = table[i];
					if (table[i] > max) max = table[i];
				}
				// Results of the table processing to be displayed
				if (count > 0) {
					float avg = sum / (float) count;
					printf("Values: %d, Min: %d, Max: %d, Avg: %.2f\n", count, min, max, avg);
				} 
				// No values processed
				else {
					DEBUG_PRINT("\nNo values processed\n\n");
				}
			}
		}
		// Release the dynamically allocated data
		if (command_line) {
			free(command_line);
			command_line = NULL;
		}
		// Release the dynamically allocated data
		if (table) {
			free(table);
			table = NULL;
		}
	}
	return 0;
}