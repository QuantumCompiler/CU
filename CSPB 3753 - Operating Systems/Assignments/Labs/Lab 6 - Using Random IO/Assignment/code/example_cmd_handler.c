///////////////////////////////////////////////////////////////////////////////
// Example code for processing a command line and handling requests
///////////////////////////////////////////////////////////////////////////////
// Author:  < no credit without updated comments>
// Date:
///////////////////////////////////////////////////////////////////////////////
// Processing command line request
//		This code shows how to process command requests that could be used
//		in a server.  The basic commands are handled by parsing the command
//		line and performing the service, which will write results to a given
//		file descriptor.
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

#define MAX_CMD_LINE_SIZE 1024
#define WHITESPACE " \f\n\r\t\v"

///////////////////////////////////////////////////////////////////////////////
// int get_command_line(buffer, size, f)
//
// Read an input string into given buffer.  
//
//  Parameters  : f - pointer to FILE data structure from which to read
//                buffer - char array in which to store data
//                size - max number of bytes to read into the buffer
//  Return value: buffer from fgets()
//
///////////////////////////////////////////////////////////////////////////////

// !!!!!!!!!!!!SHOULD BE REPLACED WITH YOUR DYNAMIC COMMAND LINE READER !!!!!!!!!!!!
static char *get_command_line(char *buffer, size_t size, FILE *f) {
	
	// Basic Algorithm
	//		get a line of text from given file descriptor
	//		return buffer
		
	// Read a line of input from file descriptor
	buffer =  fgets(buffer, size, f);
	if (buffer == NULL) {
		perror("Error reading input");
	}

	return buffer;
}

///////////////////////////////////////////////////////////////////////////////
// int parse_command_line(buffer, tokens, size)
//
// Given an input string, parse into tokens stored in given token array.  
//
//  Parameters  : buffer - null terminated string
//				  tokens - array in which to store the string pointers.
//				  size - max number of tokens to be stored.
//  Return value: number of tokens placed in array
//
///////////////////////////////////////////////////////////////////////////////

// !!!!!!!!!!!!SHOULD BE REPLACED WITH YOUR DYNAMIC TOKEN GENERATOR !!!!!!!!!!!!
static int parse_command_line(char *buffer, char **tokens, size_t size) {

	DEBUG_PRINT("Parsing command line [%s]\n", buffer);

	// parse the command line into tokens
	// 		parse the command line into strings (by whitespace)
	// 		first string is command, other tokens are parameter(s)
	int token_count = 0;


	// Tokenize the string using strtok
	char *token = strtok(buffer, WHITESPACE); 

	// Process each token
	while ((token != NULL) && (token_count < 100)) {
		// add token to list
		DEBUG_PRINT("\tAdding token [%s]\n", token);
		tokens[token_count++] = token;

		// Get the next token
		token = strtok(NULL, WHITESPACE);
	}

	// return count
	DEBUG_PRINT("Number of tokens: %d\n", token_count);
	return token_count;
}


///////////////////////////////////////////////////////////////////////////////
// Sample code to read a command line and process the request
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {

	// make the stdout and stderr file descriptors non-buffered
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int running = true;
	char *prompt = "%s> ";
	char *command_line;
	FILE *f = NULL;		// file opened for processing

	while (running  && !feof(stdin)) {

		// prompt the user for next command line
		printf(prompt, "\n3753-Lab-KNOX");

		char command_line[MAX_CMD_LINE_SIZE];

		if (get_command_line(command_line, sizeof(command_line), stdin) == NULL) {
			DEBUG_PRINT("\nMissing command from user\n\n");
			running = false;
			break; // out of while
		}

		// parse the command line into tokens
		char *tokens[100];
		int token_count = parse_command_line(command_line, tokens, sizeof(tokens)/sizeof(char*));

		switch (tokens[0][0]) {
			case 'O':
			case 'o':
				{	// OPEN <filename>
					if (token_count != 2) {
						DEBUG_PRINT("OPEN command usage : OPEN <filename>\n");
						break; // out of switch
					} 

					// check if there is already a file open !!!!!
					
					DEBUG_PRINT("Opening File[%s]\n", tokens[1]);
					f = fopen(tokens[1], "r");
					if (f == NULL) {
						DEBUG_PRINT("Could not open file: [%s]\n", tokens[1]);
						break; // out of switch
					}
					DEBUG_PRINT("Opened File[%s]\n", tokens[1]);

					break; // out of switch
				}
			case 'C':
			case 'c':
				{	// CLOSE
					if (f != NULL)
						fclose(f);
					break; // out of switch
				}
			case 'R':
			case 'r':
				{	// READ <size>
					if (token_count != 2) {
						DEBUG_PRINT("READ command usage : READ <size>\n");
						break; // out of switch
					} 
					size_t len = atoi(tokens[1]);

					// check that the file is open !!!!!
					// TODO

					// Read from the input file and write to the output file (STDOUT)
					char buffer[10];
					int count = 0;
					char c;

					while ( (count < len) && (c=getc(f)) && ( ! feof(f) )) {
						count++;
						fputc(c, stdout);
					}
					break; // out of switch
				}
			case 'W':
			case 'w':
				{	// WRITE <string>
					if (token_count != 2) {
						DEBUG_PRINT("WRITE command usage : WRITE <string>\n");
						break; // out of switch
					} 

					// check that the file is open !!!!!
					// TODO
					
					// Write to the current position of the file
					DEBUG_PRINT("Writing [%s]\n", tokens[1]);
					size_t written = 0;
					
					//   write string to file
					// TODO

					if (written <= 0) perror("write failed:");
					DEBUG_PRINT("Wrote [%ld] bytes\n", written);

					break; // out of switch
				}
			case 'S':
			case 's':
				{	// SEEK <mode> <position>
					if (token_count != 3) {
						DEBUG_PRINT("SEEK command usage : SEEK <mode> <position>\n");
						break; // out of switch
					} 

					DEBUG_PRINT("SEEK requested\n");

					// check that the file is open !!!!!
					// TODO

					long ret = -1;

					// seek to position from given starting point
					// TODO

					DEBUG_PRINT("SEEK returned [%ld]\n", ret);
					
					break; // out of switch
				}
			case 'T':
			case 't':
				{	// TELL
					DEBUG_PRINT("TELL requested\n");

					// check that the file is open !!!!!
					// TODO

					long ret = -1;

					// get current position
					// TODO

					DEBUG_PRINT("TELL [%ld]\n", ret);
					
					break; // out of switch
				}			case 'Q':
			case 'q':
				{	// quit the command processing
					running = false;
					DEBUG_PRINT("Exiting command parser\n");

					break; // out of switch
				}
		}
	}
	
	if (f != NULL) 
		fclose(f);

    return 0;
}

