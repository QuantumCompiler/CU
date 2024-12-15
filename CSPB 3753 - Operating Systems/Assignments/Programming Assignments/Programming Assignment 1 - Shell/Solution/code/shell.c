///////////////////////////////////////////////////////////////////////////////
// Shell Lab
///////////////////////////////////////////////////////////////////////////////
// Author: Taylor Larrechea
// Date: 09-26-2024	
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

/*
	This file contains the main function for the shellLab shell.

	This program is designed to run a shell that can execute commands from the command line.

	This program is designed to work in a Unix environment, specifically a Linux environment.
*/

// Includes

#include "data.c"
#include "includes.c"
#include "pipe-fork.c"
#include "debug_3753.h"
#include "split_cmdline.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

/*	main - Main function for the shellLab shell
		Input:
			int argc - Number of arguments passed to the program
			char **argv - Array of arguments passed to the program
		Algorithm:
			* Set the output streams to be nonbuffered
			* Print the welcome message
			* Run the shell
		Output:
			Program runs the shell
*/
int main(int argc, char **argv) {

	// normally the output streams are buffered, meaning that the print text 
	// will not show up at the terminal until the buffer is full or the stream
	// is closed.  That is a problem with multiple processes printing different 
	// information.  To make sure that the text is sent to the terminal 
	// immediately, you can set the buffer size to 0, when makes it nonbuffered.
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// Fun greetings

	// Welcom To The Shell Lab
	char *welcome = 
		"__        __   _                            _____       _____ _            ____  _          _ _   _          _     _ \n"
		"\\ \\      / /__| | ___ ___  _ __ ___   ___  |_   _|__   |_   _| |__   ___  / ___|| |__   ___| | | | |    __ _| |__ | |\n"
		" \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\    | | | '_ \\ / _ \\ \\___ \\| '_ \\ / _ \\ | | | |   / _` | '_ \\| |\n"
		"  \\ V  V /  __/ | (_| (_) | | | | | |  __/   | | (_) |   | | | | | |  __/  ___) | | | |  __/ | | | |__| (_| | |_) |_|\n"
		"   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|   |_|\\___/    |_| |_| |_|\\___| |____/|_| |_|\\___|_|_| |_____\\__,_|_.__/(_)\n";

	// By
	char *by = 
		" ____        \n"
		"| __ ) _   _ \n"
		"|  _ \\| | | |\n"
		"| |_) | |_| |\n"
		"|____/ \\__, |\n"
		"       |___/ \n";

	// Quantum Compiler
	char *qc = 
		"  ___                    _                    ____                      _ _             __  \n"
		" / _ \\ _   _  __ _ _ __ | |_ _   _ _ __ ___  / ___|___  _ __ ___  _ __ (_) | ___ _ __   \\ \\ \n"
		"| | | | | | |/ _` | '_ \\| __| | | | '_ ` _ \\| |   / _ \\| '_ ` _ \\| '_ \\| | |/ _ \\ '__| (_) |\n"
		"| |_| | |_| | (_| | | | | |_| |_| | | | | | | |__| (_) | | | | | | |_) | | |  __/ |     _| |\n"
		" \\__\\_\\\\__,_|\\__,_|_| |_|\\__|\\__,_|_| |_| |_|\\____\\___/|_| |_| |_| .__/|_|_|\\___|_|    (_) |\n"
		"                                                                 |_|                    /_/ \n";

	printf("%s\n", welcome);
	printf("%s\n", by);
	printf("%s\n", qc);

	// Actual shell

	run_shell();

    return 0;
}