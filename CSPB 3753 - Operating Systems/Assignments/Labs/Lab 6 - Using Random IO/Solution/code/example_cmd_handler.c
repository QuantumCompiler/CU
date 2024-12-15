/*
	This file consists the code required for Step 3 of the assignment. In this code you will find three primary functions:

	1. get_command_line - Read a line of input from the user
		This function is responsible for reading a line of input from the user. It uses fgets to read the input and removes the trailing newline if present.
	2. parse_command_line - Tokenize the input string
		This function is responsible for tokenizing the input string. It uses strtok to tokenize the input string and stores the tokens in the tokens array.
	3. main - Entry point of the program
		This function is the entry point of the program. It reads the command line from the user, echos the command line, parses the command line into tokens, and processes the request based on the command.

	To compile the code and run, refer to the makefile in this directory.
*/

///////////////////////////////////////////////////////////////////////////////////
// Example code for processing a command line and handling requests
///////////////////////////////////////////////////////////////////////////////////
// Author:  Taylor Larrechea
// Date:    10-9-24
///////////////////////////////////////////////////////////////////////////////////
// Processing command line request
//      This code shows how to process command requests that could be used
//      in a server.  The basic commands are handled by parsing the command
//      line and performing the service, which will write results to a given
//      file descriptor.
//
///////////////////////////////////////////////////////////////////////////////////


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


/*	get_command_line - Read a line of input from the user
		Input:
			buffer - buffer to store the input
			size - size of the buffer
			f - file to read from
		Algorithm:
			* Use fgets to read a line of input from the user
			* Remove the trailing newline, if present
		Output:
			Returns the buffer if successful, NULL otherwise

*/
static char *get_command_line(char *buffer, size_t size, FILE *f) {
	// Read a line of input from the user
    buffer = fgets(buffer, size, f);

	// Buffer failed
    if (buffer == NULL) {
        perror("Error reading input");
        return NULL;
    }

    // Remove trailing newline, if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}

/*	parse_command_line - Tokenize the input string
		Input:
			buffer - input string
			tokens - array of strings to store tokens
			size - size of the tokens array
		Algorithm:
			* Use strtok to tokenize the input string
			* Store the tokens in the tokens array
			* Return the number of tokens found
		Output:
			Returns the number of tokens found
*/
static int parse_command_line(char *buffer, char **tokens, size_t size) {
    int token_count = 0;

    // Tokenize the string using strtok
    char *token = strtok(buffer, WHITESPACE);

    // Process each token
    while (token != NULL && token_count < (int)size) {
        tokens[token_count++] = token;
        token = strtok(NULL, WHITESPACE);
    }

    return token_count;
}



/*	main - Entry point of the program
		Input:
			argc - number of arguments
			argv - array of arguments
		Algorithm:
			* Read the command line from the corresponding file 
			* Print the output for each scenario / command
		Output:
			Returns 0 on success, 1 on failure
*/
int main(int argc,char **argv) {

    // make the stdout and stderr file descriptors non-buffered
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    int running = true;
    char *prompt = "%s > ";
    char *command_line;
    FILE *f = NULL;     // file opened for processing

    while (running  && !feof(stdin)) {

        // prompt the user for next command line
        printf(prompt, "3753-Lab-KNOX");

        char command_line[MAX_CMD_LINE_SIZE];

        if (get_command_line(command_line, sizeof(command_line), stdin) == NULL) {
            printf("\nMissing command from user\n\n");
            running = false;
            break; // out of while
        }

        // Echo the command line
        printf("%s\n", command_line);

        // parse the command line into tokens
        char *tokens[100];
        int token_count = parse_command_line(command_line, tokens, sizeof(tokens)/sizeof(char*));

        if (token_count == 0) {
            printf("No command entered\n");
            continue; // skip to next iteration
        }

        switch (tokens[0][0]) {
			// Open command
            case 'O':
            case 'o':
                {   // OPEN <filename>
                    if (token_count != 2) {
                        printf("OPEN command usage : OPEN <filename>\n");
                        break; // out of switch
                    } 

                    // Check for open file
                    if (f != NULL) {
                        printf("There is already a file open\n");
                        break; // out of switch
                    }
                    
                    // Open the file in read/write mode
                    f = fopen(tokens[1], "r+");
                    if (f == NULL) {
                        printf("Could not open file: [%s]\n", tokens[1]);
                        break; // out of switch
                    }

                    break; // out of switch
                }
			// Close command
            case 'C':
            case 'c':
                {   // CLOSE
                    if (f != NULL) {
                        fclose(f);
                        f = NULL;
                        printf("Closed file\n");
                    } else {
                        printf("No file open\n");
                    }
                    break; // out of switch
                }
			// Read command
            case 'R':
            case 'r':
                {   // READ <size>
                    if (token_count != 2) {
                        printf("READ command usage : READ <size>\n");
                        break; // out of switch
                    } 
                    size_t len = atoi(tokens[1]);

                    // Check for open file
                    if (f == NULL) {
                        printf("No file is currently open\n");
                        break; // out of switch
                    }

                    // Read from the input file and write to the output file (STDOUT)
                    size_t count = 0;
                    int c;

                    while ((count < len) && ((c = fgetc(f)) != EOF)) {
                        fputc(c, stdout);
                        count++;
                    }
                    if (count < len && ferror(f)) {
                        perror("Error reading file");
                    }
                    printf("\n"); // To move to the next line after reading
                    break; // out of switch
                }
			// Write command
            case 'W':
            case 'w':
                {   // WRITE <string>
                    if (token_count != 2) {
                        printf("WRITE command usage : WRITE <string>\n");
                        break; // out of switch
                    } 

                    // Check that the file is open
                    if (f == NULL) {
                        printf("No file is currently open\n");
                        break; // out of switch
                    }
                    
                    // Write to the current position of the file
                    size_t written = 0;

                    // Write string to file
                    written = fwrite(tokens[1], sizeof(char), strlen(tokens[1]), f);
                    if (written < strlen(tokens[1])) {
                        perror("Write failed:");
                    } else {
						printf("WRITE[%s]==> [%ld]\n", tokens[1], written);
					}
                    break;
                }
			// Seek command
            case 'S':
            case 's':
                {   // SEEK <mode> <position>
                    if (token_count != 3) {
                        printf("SEEK command usage : SEEK <mode> <position>\n");
                        break; // out of switch
                    } 

                    // Check that the file is open
                    if (f == NULL) {
                        printf("No file is currently open\n");
                        break; // out of switch
                    }

                    int mode = atoi(tokens[1]);
                    long offset = atol(tokens[2]);
                    int origin;

                    switch (mode) {
                        case 0: origin = SEEK_SET; break; // beginning of file
                        case 1: origin = SEEK_CUR; break; // current position
                        case 2: origin = SEEK_END; break; // end of file
                        default:
                            printf("Invalid seek mode\n");
                            continue; // skip to next iteration
                    }

                    int ret = fseek(f, offset, origin);

                    printf("SEEK to [%d][%ld] ==> [%d]\n", mode, offset, ret);

                    break; // out of switch
                }
			// Tell command
            case 'T':
            case 't':
                {   // TELL

                    // Check that the file is open
                    if (f == NULL) {
                        printf("No file is currently open\n");
                        break; // out of switch
                    }

                    long ret = ftell(f);

                    if (ret == -1L) {
                        perror("TELL failed");
                    } else {
                        printf("TELL ==> [%ld]\n", ret);
                    }
                    
                    break; // out of switch
                }       
			// Quit command
            case 'Q':
            case 'q':
                {   // quit the command processing
                    running = false;

                    break; // out of switch
                }
			// Default case
            default:
                printf("Unknown command has been entered\n");
                break; // out of switch
        }
    }

    // Close the file if it is open
    if (f != NULL) 
        fclose(f);

    return 0;
}