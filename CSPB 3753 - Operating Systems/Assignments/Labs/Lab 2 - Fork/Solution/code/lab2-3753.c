#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int main(int argc,char **argv) {
    // Check if the number of arguments is less than 2
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [<command> ...]\n", argv[0]);
    }
    // For the number of arguments, execute the following
    for (int i = 1; i < argc; i++) {
        // Create a child process
        pid_t pid = fork();
        // Check if fork failed
        if (pid == -1)  {
            perror("fork failed");
            exit(1);
        }
        // Execute the child process
        if (pid == 0) {
            /*put code for child process here*/
            printf("Child: I am the child process.\n");
            printf("Child: My process id = %d\n", getpid());
            printf("Child: My parent's process id = %d\n", getppid());
            // execute the command
            execlp(argv[i], argv[i], NULL);
            // if execlp fails
            perror("execlp failed");
            // exit child process
            exit(1);
        } 
        // Process is a parent process
        else {
            /*put code for parent process here*/
            printf("I am the parent process.\n");
            printf("Parent: process id = %d\n", getpid());
            // wait for child process to finish
            int status;
            if (wait(&status) == -1) {
                perror("wait failed");
                exit(1);
            }
            // check if child process exited normally
            if (WIFEXITED(status)) {
                printf("Parent: child exited with status %d\n", WEXITSTATUS(status));
            } 
            // check if child process exited abnormally
            else {
                printf("Parent: child exited abnormally\n");
            }
        }
    }
	return 0;
}