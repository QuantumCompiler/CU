///////////////////////////////////////////////////////////////////////////////
// Shell Lab
///////////////////////////////////////////////////////////////////////////////
// Author:  < no credit without updated comments>
// Date:
///////////////////////////////////////////////////////////////////////////////
// Creating Your Own Shell
//      Your task is to extend the Fork Lab and the Pipe Lab to create a basic 
//      shell with a small memory footprint.  The program will handle any size 
//      command line, but only allocate the minimum number of bytes to store the
//      string (never having more than 16 bytes of unused space allocated).  
//      The shell should operate as follows:
//          1. Print a customized welcome message to stdout.
//          2. Display a customized command prompt.
//          3. Fetch a command from stdin and store it into a buffer.
//          4. Execute this command (as separate processes).
//          5. Report the exit status of all processes in the command to stdout
//             (only if entire process is not run in background, specified with
//              a trailing `&` in command line).
//          6. Repeat the steps 2 through 5 until the user enters DONE.
//
//      To keep things simple, we will not do any sophisticated parsing of the 
//      user’s input (e.g., no quotation matching, checks for escape characters,
//      etc..). In particular, you may assume that the user will input data in 
//      the format shown in the example below:
//          cmd_1 arg arg ... arg | ... | cmd_n arg arg ... arg &
//
//      You will manage the redirection of the output from one process to the 
//      next to replicate the behavior of a bash shell.
//
//      Need to make sure that all allocated data structures (memory, files, 
//      pipes, ...) need to be deallocated.  Use the `valgrind` tools to verify.
///////////////////////////////////////////////////////////////////////////////

#define _GNU_SOURCE 

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define DEBUG 1
//#define DEBUG 0
#include "debug_3753.h"
#include "split_cmdline.h"

// Constants used in code
#define COMMAND_BUFFER_GROWTH_SIZE 16
#define ARG_TABLE_GROWTH_SIZE 4
#define PIPE_SYMBOL "|"
#define BACKGROUND_SYMBOL "&"

// Special Commands to process
#define CHANGE_DIRECTORY  "cd"
#define EXIT  "done"

///////////////////////////////////////////////////////////////////////////////
// read_command_line()
//
// [explain the function purpose, parameters, return value, 
//  and any other information that is useful or needed]
//
//  Parameters  : none
//  Return value: pointer to a string buffer that is 0 terminated containing
//                all characters typed by user until a newline is detected.
//                Caller is responsible for deallocation of buffer.
//
//  Notes: - does not handle newline in a quoted string during command line reading
//         - does not handle dynamic growth during command line reading
///////////////////////////////////////////////////////////////////////////////

static char *read_command_line(void) {
    int used = 0;       // number of bytes currently used by the command line
    int ch;             // character read from stdin to be placed in command line buffer
    int allocated_size = COMMAND_BUFFER_GROWTH_SIZE;
    char *buffer = malloc(allocated_size * sizeof (char));
	buffer[0] = 0;

	// TODO: add error checking code to see that a buffer has been returned
    // if ( ??? ) {
    //    output an error message
    //    cannot continue without a buffer, terminate the process
    // }

    // Loop while we have not seen the End of Line or End of File.
    // Uses trick to set a variable during the conditional expression evaluation.
    // Careful to use correct equal sign operators. 
    while ( ((ch = fgetc(stdin)) != '\n') && !feof(stdin)) { 
		
#if DEBUG > 3
		DEBUG_PRINT("read[%02X, '%c']", ch, ch);
#endif
		
        // Check to see if there is enough space to add the character 
        // still and maintain an ending null character.
        // if not increase the buffer another COMMAND_BUFFER_GROWTH_SIZE bytes
        if (used >= allocated_size-1) {
            // get a bigger boat
#if DEBUG > 3
            DEBUG_PRINT("getting a bigger boat\n");
#endif
			allocated_size += COMMAND_BUFFER_GROWTH_SIZE;
			buffer = realloc(buffer, allocated_size * sizeof (char));
        }

        buffer[used++] = ch;
        buffer[used] = 0;   // keep a zero termination character in buffer at all times
    }

#if DEBUG > 3
	DEBUG_PRINT("\ncommand line:[%s]\n", buffer);
#endif
	
    return buffer;  // return the buffer to caller who is responsible for deallocation
}

///////////////////////////////////////////////////////////////////////////////
// calc_number_of_processes(tokens)
//
//  Search the tokens to find count of PIPE SYMBOL tokens.
//
//  Parameters  : list of pointers to strings of characters representing the 
//                tokens of the command line.  List is NULL pointer terminated.
//  Return value: count of the number of PIPE SYMBOL strings found in tokens.
///////////////////////////////////////////////////////////////////////////////
int calc_number_of_processes(char ** tokens) {
	int count = 0;
	if (tokens != NULL) {
		count = 1;   // at least one command???

		// iterate through the tokens looking for pipe symbol
		// 		if token matches PIPE SYMBOL
		//			found another process to handle
	}

	return count;
}


///////////////////////////////////////////////////////////////////////////////
// Support checking of system call return values
//
//  Routines to call system level functions and exit if command fails.
//  You can define a wrapper function to call the system function and
//  check the return value for any errors during the function call.
///////////////////////////////////////////////////////////////////////////////

// Below is an example of how to write a macro that the compiler will 
// interpret and generate the place in the code that it is called
//
// check_close(int fd, message, parameters...);
// a macro that checks the close function return value
// [should still have a function like header 
//  explaining the purpose and parameters]
#define check_close(fd, fmt, ...)                        \
    {                                                    \
        int ret = close(fd);                             \
		if (ret == -1) {                                 \
	        fprintf(stderr, "[DEBUG: %s:%d:%s()]: " fmt, \
			               __FILE__, __LINE__, __func__, \
						   ##__VA_ARGS__);               \
			perror("close pipe failed");                 \
			exit(98);                                    \
		}                                                \
    }


// check_pipe(int **fds, message, parameters...);
// TO DO - define macro or function to check a pipe call
#define check_pipe(fds, ...) {}

// check_dup2(int old_fd, int new_fd, message, parameters...);
// TO DO - define macro or function to check a pipe call

// check_execvp(char *cmd, char **tokens, message, parameters...);
// TO DO - define macro or function to check an execvp

///////////////////////////////////////////////////////////////////////////////
// Globals to support pipes and processes
///////////////////////////////////////////////////////////////////////////////

// Pipes have two file descriptors, the following makes your code easier 
// to understand than using 0 and 1.
#define READ_SIDE 0
#define WRITE_SIDE 1

// global variables to handle remembering pid(s) of created children
// and for holding all the pipes that are created.
// [These variables should be dynamically allocated, growing as needed]
int pid_count = 0;
int *pids = NULL; // need to malloc storage and check results for errors
int pipe_count = 0;
int **pipes =  NULL; // need to malloc storage and check results for errors

///////////////////////////////////////////////////////////////////////////////
// create_next_child(prev_pipe, tokens, next_pipe)
//
//  Fork the process and use the tokens to execv a new executable.
//  If there is a previous pipe then connect stdin to the previous pipe.
//  If the next_pipe, connect stdout to the next_pipe.
//
//  Parameters  : list of pointers to strings of characters representing the 
//                tokens of the command line.  List is NULL pointer terminated.
//  Return value: PID
//
//  Globals: uses pipe list to maintain all pipes.
//
///////////////////////////////////////////////////////////////////////////////
int create_next_child(int *prev_pipe, char ** tokens, int *next_pipe) {
	DEBUG_PRINT ("[%d] ==> [%s] ==> [%d]\n", 
					(prev_pipe==NULL?-1:prev_pipe[0]),
					tokens[0], 
					(next_pipe==NULL?-1:next_pipe[1]));

	if ((tokens == NULL) || (tokens[0] == NULL))
	{
		DEBUG_PRINT ("*** ERROR No tokens given\n");
		return 0;
	}
	
	
	DEBUG_PRINT ("Creating fork()...\n");
	
	int pid = fork();
	if (pid == -1) {
		DEBUG_PRINT ("child[%s] error in fork()\n", tokens[0]);
		return false;
	}

	if (pid == 0) {
		// In the child process
		DEBUG_PRINT ("child[%s] setup pipe connections\n", tokens[0]);

		// connect stdin to previous pipe if there is one
		if (prev_pipe != NULL) {
			// connect stdin with READ_SIDE of prev_pipe
			// close the WRITE_SIDE of prev_pipe
		}

		// connect stdout to next pipe if there is one
		if (next_pipe != NULL) {
			// connect stdout with WRITE_SIDE of this pipe, pipe[pipe_count][1]
			// close the READ_SIDE of this pipe, pipe[pipe_count][0]
		}
		
		// you can use the same DEBUG defined value to decide to execute some
		// debug code.  Here it will have the system process a couple commands.
		#if DEBUG > 0
			// checks to see if the child process is recognized by OS by a
			// having a directory existing in the /proc system directory)
			// prints out the current open file descriptors for that process.
			// Try out the command:  ls -l /proc/6/fd
			char command[120]; 
			int child_pid = getpid();
			sprintf(command, "echo Process: %d && ls -l /proc/%d/fd ", child_pid, child_pid);
			int result = system(command);
		#endif

		DEBUG_PRINT ("Calling ??? ([%s],...)\n", tokens[0]);
		// start up the new command for this child to process
		if (-1 /* start new program*/ == -1) {
			perror("??? : error");
			exit(0);
		}
		perror("??? : error - should never get here");
		exit(-99);
	}
	
	// otherwise, this is the parent
	// print error if fork failed
	DEBUG_PRINT ("Parent received pid = %d\n", pid);
	#if DEBUG > 0
		char command[120]; 
		sprintf(command, "echo Process: %d && ls -l /proc/%d/fd ", pid, pid);
		int result = system(command);
	#endif

	return pid;
}
	

///////////////////////////////////////////////////////////////////////////////
// eval_tokens(tokens)
//
//  Fork the process and use the tokens to execv a new executable.  If there is
//  a previous pipe (see pipe_count) then connect stdin to the previous
//  pipe.  If the next set of tokens ends with a PIPE SYMBOL, create a pipe for 
//  the next process and hook stdout to the pipe.
//
//  Parameters  : list of pointers to strings of characters representing the 
//                tokens of the command line.  List is NULL pointer terminated.
//  Return value: if processing was successful
//
//  Globals: uses pipe list to maintain all pipes.
//
///////////////////////////////////////////////////////////////////////////////
int eval(char ** tokens) {
	DEBUG_PRINT ("eval(...)\n");

	int *prev_pipe = NULL;
	int *next_pipe = NULL;

	while ((tokens != NULL) && (tokens[0] != NULL)) {
		
		// From the list of tokens, find the end of command arguments.
		int i = 0;  // position of the end of the current command arguments
		// [iterate to find the end of the tokens or a pipe symbol]


	#if DEBUG > 0
		// Here is another way to print out messages.  Print them to stderr stream.
		fprintf(stderr, "Evaluating command[%d tokens] [", i);
		for (int k=0 ; k < i ; ++k) {
			fprintf(stderr, "[%s]",tokens[k]);
		}
		fprintf(stderr, "]\n");
	#endif

		// check to see if there are more commands to process after this one.
		bool more_tokens = (tokens[i] != NULL);

		bool found_pipe_symbol = ((tokens[i] != NULL) && (strncmp(tokens[i], PIPE_SYMBOL, sizeof(PIPE_SYMBOL)) == 0));
		if (found_pipe_symbol) {
			// Need to create a new PIPE before fork() so both processes 
			// (parent and child) have access to both READ_SIDE and WRITE_SIDE.
			// create new pipe in pipes[pipe_count], update pipe_count LATER.
			tokens[i] = NULL;   //replace the symbol with a NULL termination for 
								// the command params in system call.

			#if DEBUG > 0
				DEBUG_PRINT ("Creating pipe()...\n");
			#endif		

			next_pipe = pipes[pipe_count];
			check_pipe(next_pipe, "unable to create output pipe for [%s]", tokens[0]);

			#if DEBUG > 0
				DEBUG_PRINT ("[%s] new pipe[in,out]=[%d, %d]\n", tokens[0], 
						next_pipe[READ_SIDE], next_pipe[WRITE_SIDE]);
			#endif		
		}

		// Create a child to handle the process
		int pid = create_next_child(prev_pipe, tokens, next_pipe);

		DEBUG_PRINT ("setting pid[%d]=%d into structure\n", pid_count, pid);
		pids[pid_count] = pid;
		pid_count++;

		if (next_pipe)
			pipe_count++;

		// reset pipes for next iteration
		if (prev_pipe) {
			check_close(prev_pipe[READ_SIDE], "READ_SIDE closed failed");
			check_close(prev_pipe[WRITE_SIDE], "WRITE_SIDE closed failed");
		}

		// For the next iteration, next pipe is now the previous pipe 
		// and there is not a next pipe until it is needed.
		prev_pipe = next_pipe;
		next_pipe = NULL;

		if (more_tokens)			// [why is this here?????]
			tokens = &tokens[i+1];	
		else {
			DEBUG_PRINT ("end of tokens\n");
			tokens = NULL;
		}

	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {

	// normally the output streams are buffered, meaning that the print text 
	// will not show up at the terminal until the buffer is full or the stream
	// is closed.  That is a problem with multiple processes printing different 
	// information.  To make sure that the text is sent to the terminal 
	// immediately, you can set the buffer size to 0, when makes it nonbuffered.
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

    int running = true;
    char *prompt = "%s> ";
        
    while (running  && !feof(stdin)) {

        printf(prompt, "3753-Lab-1");
        
        char *cmdline = read_command_line();
		if (cmdline == NULL)
			printf("\nMissing command line\n\n");
		
		char **tokens = split_command_line(cmdline);
		if ((tokens == NULL) || (tokens[0] == NULL)) {
			DEBUG_PRINT("\nNo command line received\n\n");
		} else {
			// process the token structure
			DEBUG_PRINT("/n# of processes found in tokens: %d\n", calc_number_of_processes(tokens));
			if (strncmp(tokens[0], EXIT, sizeof(EXIT)) == 0) {
				free(cmdline);
				break;
			} else if (strncmp(tokens[0], CHANGE_DIRECTORY, sizeof(CHANGE_DIRECTORY)) == 0) {
				// process change of directory
			} else {
				// process tokens
				//    1. Collect the tokens until a PIPE symbol, a BACKGROUND symbol, or end of the tokens
				//    2. Place a NULL pointer into tokens at break, so we can use execv system call
				//    3. Manage pipes to redirect output from first command to next command

				// Replace this comment and the code below with call(s) to process and pipe management
				// This problem has a nice recursive solution
				DEBUG_PRINT ("Processing command [%s]\n", cmdline);
				for (int i=0 ; tokens[i] != NULL ; ++i) {
					DEBUG_PRINT("\t%3d:[%s]\n", i, tokens[i]);
				}

				// run the command
				eval(tokens);
				

				// wait for all pids to terminate
				for (int i=0 ; i < pid_count ; i++) {
					if (pids[i] > 0) {
						int status;
						int dead_pid = wait(&status);
						DEBUG_PRINT("%d is dead\n", dead_pid);
					}
				}
			}
		}

        // free any allocated data that has not been deallocated

    }

    return 0;
}

