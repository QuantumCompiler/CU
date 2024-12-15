///////////////////////////////////////////////////////////////////////////////
// Author: Taylor Larrechea
// Date: 09-26-2024	
///////////////////////////////////////////////////////////////////////////////

/*
    Header file for the pipe-fork.c file. Contains the function prototypes for the functions in pipe-fork.c.
*/

#ifndef PIPE_FORK

// Includes

#include "includes.c"

void built_in_cmd(char **tokens); // Executes a built in command from command line

void execute_command(char *command); // Executes a command from the command line

void pipe_processes(char **commands); // Pipes the processes together

void run_shell(); // Runs the shell

#endif