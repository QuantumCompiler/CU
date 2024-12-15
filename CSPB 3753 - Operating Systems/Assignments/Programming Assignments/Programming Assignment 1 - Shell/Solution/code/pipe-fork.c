///////////////////////////////////////////////////////////////////////////////
// Author: Taylor Larrechea
// Date: 09-26-2024	
///////////////////////////////////////////////////////////////////////////////

/*
    This file contains the functions to execute the shell commands that mainly pertain to forking, piping, and executing commands.
    Along with the previous functions, the run_shell function is included to run the shell.
*/

// Includes

#include "pipe-fork.h"
#include "split_cmdline.c"


/*  built_in_cmd - Executes a built in command from command line
        Input:
            char **tokens - Command line input that has been split into tokens
        Algorithm:
            * Check if the command is done
                * If the command is done, free the tokens and exit the program
            * Check if the command is to change directory
                * If the command is to change directory, change the directory
                * Check if it fails
                    * If it does, print an error message
        Output:
            Program executes either "done" or "cd"
*/
void built_in_cmd(char **tokens) {
    // Check if the command is done
    if (strcmp(tokens[0], "done") == 0) {
        free(tokens);
        exit(0);
    } 
    // Check if the command is to change directory
    else if (strcmp(tokens[0], "cd") == 0) {
        // Command to change directory failed
        if (tokens[1] == NULL || chdir(tokens[1]) != 0) {
            perror("cd failed");
        }
    }
}

/*  execute_command - Executes a command from the command line
        Input:
            char *command - Command line input
        Algorithm:
            * Split the command into tokens
            * Check if the command is a built in command
                * If the command is a built in command, execute the built in command
            * Otherwise, fork and execute the command
        Output:
            Program executes the command
*/
void execute_command(char *command) {
    // Split the command into tokens
    char **tokens = split_cli(command, " ");
    // Check if the command is a built in command
    if (strcmp(tokens[0], "cd") == 0 || strcmp(tokens[0], "done") == 0) {
        built_in_cmd(tokens);
    } 
    // Otherwise, fork and execute the command
    else {
        // Fork the process
        pid_t pid = fork();
        // Child process
        if (pid == 0) {
            // Execute the command with the tokens with execvp
            execvp(tokens[0], tokens);
            perror("Error executing command");
            // Handle the error (exit function)
            // exit(EXIT_FAILURE);
        } 
        // Parent process
        else if (pid > 0) {
            waitpid(pid, NULL, 0);
        } 
        // Error forking process
        else {
            perror("Error forking process");
        }
    }
    // Free the tokens
    free(tokens);
}

/*  pipe_processes - Pipes the processes together
        Input:
            char **commands - Commands to be piped together
        Algorithm:
            * Count the number of commands
            * Execute the command if there is only one command
            * Create the pipes (2 * (num_commands - 1) because there is a pipe for each command)
            * Create the pipes
            * Loop through the commands
                * Split the command into tokens
                * Fork the process
                * Child process
                    * Check if the command is not the first
                        * Duplicate the input
                    * Check if the command is not the last
                        * Duplicate the output
                    * Close the pipes from the child
                    * Execute the command with the tokens with execvp
                * Fork failed
                    * Print an error message
            * Close the pipes of the processes
            * Wait for the parent processes to finish
        Output:
            Program pipes the processes together
*/
void pipe_processes(char **commands) {
    if (commands != NULL) {
        // Count the number of commands
        int num_commands = 0;
        while (commands[num_commands] != NULL) {
            num_commands++;
        }
        // Execute the command if there is only one commands
        if (num_commands == 1) {
            execute_command(commands[0]);
            return;
        }
        // Create the pipes (2 * (num_commands - 1) because there is a pipe for each command)
        int pipefds[2 * (num_commands - 1)];
        // Create the pipes
        for (int i = 0; i < num_commands - 1; i++) {
            // Check if the pipe was created successfully
            if (pipe(pipefds + i * 2) < 0) {
                perror("Could not create pipe");
                exit(EXIT_FAILURE);
            }
        }
        int pid; // Process ID
        int status; // Status of the process
        int j = 0; // Index for the pipe
        // Loop through the commands
        for (int i = 0; i < num_commands; i++) {
            // Split the command into tokens
            char **tokens = split_cli(commands[i], " ");
            // Fork the process
            pid = fork();
            // Child process
            if (pid == 0) {
                // Check if the command is not the first (command redirects to the next command)
                if (i > 0) {
                    // Duplicate the input
                    if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) < 0) {
                        perror("dup2 input failed");
                        exit(EXIT_FAILURE);
                    }
                }
                // Check if the command is not the last (command redirects to the next command)
                if (i < num_commands - 1) {
                    // Duplicate the output
                    if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) < 0) {
                        perror("dup2 output failed");
                        exit(EXIT_FAILURE);
                    }
                }
                // Close the pipes from the child
                for (int k = 0; k < 2 * (num_commands - 1); k++) {
                    close(pipefds[k]);
                }
                // Execute the command with the tokens with execvp
                execvp(tokens[0], tokens);
                perror("Error executing command");
                exit(EXIT_FAILURE);
            }
            // Fork failed
            else if (pid < 0) {
                perror("Error forking process");
                exit(EXIT_FAILURE);
            }
            // Free the tokens
            free(tokens);
        }
        // Close the pipes of the processes
        for (int i = 0; i < 2 * (num_commands - 1); i++) {
            close(pipefds[i]);
        }
        // Wait for the parent processes to finish
        for (int i = 0; i < num_commands; i++) {
            wait(&status);
        }
    }
}

/*  run_shell - Runs the shellLab shell
        Input:
            None
        Algorithm:
            * Set the input to NULL originally
            * Run the shell
                * Get the input from the CLI
                * Split the commands with the pipe
                * Check if the commands are NULL, free the input and continue
                * Pipe the processes (using the function pipe_processes)
                * Free the commands
            * Free the input
        Output:
            Program runs the shell
*/
void run_shell() {
    // Set the input to NULL originally
    char *input = NULL;
    // Run the shell
    while (1) {
        // Get the input from the CLI
        input = retrieve_cli();
        // Split the commands with the pipe
        char **commands = split_cli(input, "|");
        // Check if the commands are NULL, free the input and continue
        if (commands == NULL) {
            free(input);
            continue;
        }
        // Pipe the processes
        pipe_processes(commands);
        // Free the commands
        free(commands);
    }
    // Free the input
    free(input);
}