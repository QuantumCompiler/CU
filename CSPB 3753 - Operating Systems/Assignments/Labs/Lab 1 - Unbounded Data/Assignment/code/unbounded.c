///////////////////////////////////////////////////////////////////////////////
// Unbounded Data Structures Lab
///////////////////////////////////////////////////////////////////////////////
// Author:  < no credit without updated comments>
// Date:
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

static char *get_unbounded_line(void) {
    int allocated_size = BUFFER_GROWTH_SIZE;
    char *buffer = NULL;
	
	// Basic Algorithm
	// 	allocate a minimum amount of buffer space
	// while not EOF or EOL
	// 	get next character
	// 	if (no space left in buffer)
	// 		extend the buffer
	// 	append the character to the buffer
	// return buffer
		

    return buffer;  // return the buffer to caller who is responsible for deallocation
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

int *get_value_table(char *command_line) {
	int allocated_size = TABLE_GROWTH_SIZE;
	int *table = NULL;
	
	// Basic Algorithm
	//    allocate a minimum amount of table space
	//    while more data in command line
	//    	get next token
	//    	convert token into integer value
	//    	if (no space left in table)
	//    		extend the table
	//    	append the value to the table
	//
	//    append terminator value to table 
	//    return table
	
    return table;
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {

	// make the stdout and stderr file descriptors non-buffered
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int running = true;
	char *prompt = "%s> ";

	while (running  && !feof(stdin)) {
		char *command_line = NULL;
		int *table = NULL;

		// prompt the user for next command line
		printf(prompt, "3753-Lab-KNOX");

		command_line = get_unbounded_line();
		if (command_line == NULL) {
			DEBUG_PRINT("\nMissing data from user\n\n");
			running = false;
		} else {
			table = get_value_table(command_line);
			if ((table == NULL) || (table[0] == INT_MAX)) {
				DEBUG_PRINT("\nNo table values received\n\n");
			} else {
				// process the table values
				// print the results of the table data analysis
			}
		}
        
		//  release the dynamically allocated data structures
		if (command_line)  {}
		if (table) {}
	}
	
    return 0;
}

