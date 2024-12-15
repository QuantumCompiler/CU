///////////////////////////////////////////////////////////////////////////////
// Lab
///////////////////////////////////////////////////////////////////////////////
// Author:  Taylor Larrechea
// Date:    2021-09-15
///////////////////////////////////////////////////////////////////////////////

// Quick Overview:

/*
    - This lab focuses on piping inputs and outputs from processes
    - Two functions were written to demonstrate the use of pipes
        - The first function creates a pipe and redirects the standard input and output of a parent process to a child process (create_redirect)
        - The second function creates two child processes and pipes the output of one process to the input of the other process (create_two)
    - The functions use the execlp function to execute terminal commands
    - The functions use the fork function to create child processes
    - The functions use the pipe function to create pipes
    - The functions use the dup2 function to redirect standard input and output
    - The functions use the close function to close the ends of pipes

    - To demonstrate the use of these functions, only uncomment ONE function in the main function of this program
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

// The support functions in "debug_3753.h" use the DEBUG flag
// to modify the functions behavior.
#define DEBUG 1
//#define DEBUG 0
#include "debug_3753.h"

// Constants used in code

/*  create_redirect - Creates a pipe and redirects the processes of a parent to a child
        Input:
            None
        Algorithm:
            * Create a pipe
            * Create a pid variable for the child process
            * If in the creation of the pipe, it fails:
                * Print an error message using perror
                * Terminate 
            * If the creation of the pipe succeeds:
                * Fork the child process
                * If the fork fails:
                    * Print an error message using perror
                    * Terminate 
                * If the fork succeeds:
                    * For the child process:
                        * Close the write end of the pipe
                        * If the redirection of the standard input fails:
                            * Print an error message using perror
                            * Terminate 
                        * Close the read end of the pipe
                        * Execute the pwd command (this is done just as an example)
                        * Print error if execlp fails
                        * Terminate 
                    * For the parent process:
                        * Close the read end of the pipe
                        * If the redirection of the standard output fails:
                            * Print an error message using perror
                            * Terminate 
                        * Close the write end of the pipe
                        * Execute the ls command (this is done just as an example)
                        * Print error if execlp fails
                        * Terminate
        Output:
            This function does not return a value, it executes terminal commands as parent and child processes
*/
void create_redirect() {
    int pipefd[2];
    pid_t pid;
    // Create the pipe (-1 indicates failure)
    if (pipe(pipefd) == -1) {
        perror("pipe execution failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate the program
    }
    // Fork the child process (-1 indicates failure)
    pid = fork();
    if (pid == -1) {
        perror("fork execution failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate 
    }
    // Fork succeeds...
    if (pid == 0) { // Child process
        close(pipefd[1]); // Close the write end of the pipe
        fprintf(stderr, "Child Process: Write end closed\n");
        fflush(stderr);
        // Redirect the standard input to the read end of the pipe
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 execution failed"); // Print error message
            exit(EXIT_FAILURE); // Terminate 
        }
        close(pipefd[0]); // Close the read end of the pipe
        fprintf(stderr, "Child Process: Read end closed\n");
        fflush(stderr);
        execlp("pwd", "pwd", NULL); // Execute the pwd command
        perror("execlp execution failed"); // Print error message
        fprintf(stderr, "Child Process: Terminating\n");
        fflush(stderr);
        exit(EXIT_FAILURE); // Terminate 
    } else { // Parent process
        close(pipefd[0]); // Close the read end of the pipe
        fprintf(stderr, "Parent Process: Read end closed\n");
        fflush(stdout);
        // Redirect the standard output to the write end of the pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 execution failed"); // Print error message
            exit(EXIT_FAILURE); // Terminate 
        }
        close(pipefd[1]); // Close the write end of the pipe
        fprintf(stderr, "Parent Process: Write end closed\n");
        fflush(stderr);
        execlp("ls", "ls", NULL); // Execute the ls command
        perror("execlp execution failed"); // Print error message
        fprintf(stderr, "Parent Process: Terminating\n");
        fflush(stderr);
        exit(EXIT_FAILURE); // Terminate 
    }
    // Close pipes
    close(pipefd[0]); // Close the read end of the pipe
    close(pipefd[1]); // Close the write end of the pipe
    // Wait for the child process to finish
    wait(NULL);
}

/*  create_two - Creates two child processes and pipes the input from one process to the other and a command is executed with that data
        Input:
            None
        Algorithm:
            * Create a pipe
            * Create a pid variable for the first child process
            * If in the creation of the pipe, it fails:
                * Print an error message using perror
                * Terminate 
            * If the creation of the pipe succeeds:
                * Fork the first child process if the fork fails:
                    * Print an error message using perror
                    * Terminate 
                * If the fork succeeds for the first child process:
                    * Close the read end of the pipe
                    * If the redirection of the standard output fails:
                        * Print an error message using perror
                        * Terminate 
                    * Close the write end of the pipe
                    * Execute the cat command (this is done just as an example)
                    * Print error if execlp fails
                    * Terminate 
                * Fork the second child process If the fork fails:
                    * Print an error message using perror
                    * Terminate 
                * If the fork succeeds for the second child process:
                    * Close the write end of the pipe
                    * If the redirection of the standard input fails:
                        * Print an error message using perror
                        * Terminate 
                    * Close the read end of the pipe
                    * Execute the sort command (this is done just as an example)
                    * Print error if execlp fails
                    * Terminate 
            * Close the read end of the pipe
            * Close the write end of the pipe
            * Wait for the child processes to finish
        Output:
            This function does not return a value, it executes terminal commands for child processes and pipes the data between them
*/
void create_two() {
    int pipefd[2];
    pid_t pid1, pid2;
    // Create the pipe (-1 indicates failure)
    if (pipe(pipefd) == -1) {
        perror("pipe execution failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate
    }
    // Fork 1 process (-1 indicates failure)
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork execution failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate 
    }
    // First child process
    if (pid1 == 0) {
        fprintf(stderr, "Child 1: Executing 'cat test.txt'\n");
        fflush(stderr);
        close(pipefd[0]); // Close the read end of the pipe
        fprintf(stderr, "Child 1: Read end closed.\n");
        fflush(stderr);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 execution failed"); // Print error message
            exit(EXIT_FAILURE); // Terminate 
        }
        close(pipefd[1]); // Close the write end of the pipe
        fprintf(stderr, "Child 1: Write end closed.\n");
        fflush(stderr);
        execlp("cat", "cat", "test.txt", NULL);
        perror("execlp execution failed"); // Print error message
        fprintf(stderr, "Child 1 finished execution.\n");
        fflush(stderr);
        exit(EXIT_FAILURE); // Terminate
    }
    // Fork 2 process (-1 indicates failure)
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork execution failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate 
    }
    // Second child process
    if (pid2 == 0) {
        fprintf(stderr, "Child 2: Executing 'sort'\n");
        fflush(stderr);
        close(pipefd[1]); // Close the write end of the pipe
        fprintf(stderr, "Child 2: Write end closed.\n");
        fflush(stderr);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 execution failed"); // Print error message
            exit(EXIT_FAILURE); // Terminate 
        }
        close(pipefd[0]); // Close the read end of the pipe
        fprintf(stderr, "Child 2: Read end closed.\n");
        fflush(stderr);
        execlp("sort", "sort", "test.txt", NULL);
        perror("execlp execution failed"); // Print error message
        exit(EXIT_FAILURE); // Terminate
    }
    // Close ends of pipe
    close(pipefd[0]); // Close the read end of the pipe
    close(pipefd[1]); // Close the write end of the pipe
    // Wait for the child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

// Steps for use: Only uncomment the function that you want to examine
int main(int argc,char **argv) {
    DEBUG_PRINT("\n%d parameter(s) received\n\n", argc);
    // create_redirect();
    create_two();
    return 0;
}

