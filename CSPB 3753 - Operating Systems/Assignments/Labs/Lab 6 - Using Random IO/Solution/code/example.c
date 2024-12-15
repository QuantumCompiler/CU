/*
	This file consists the code required for Steps 1 and 2 of the assignment. In this code you will find two primary functions:

    1. Part1 - Reads and writes content to a file and then returns the offset of the pointer
        This function is responsible for reading and writing content to a file and then returning the offset of the pointer.

    2. Part2 - Reads and writes content to a file and then returns the content of the file
        This function is responsible for reading and writing content to a file and then returning the content of the file.

    To compile the code and run, refer to the makefile in this directory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/*  Part1 - Reads and writes content to a file and then returns the offset of the pointer
        Input:
            fileDescriptor - File descriptor of the file
        Algorithm:
            * Place the pointer at the end of the file
            * Write the content at the end
            * Get the current postion after the write
            * Display the results
            * Return final position
        Output:
            Returns the final position of the pointer
*/
off_t Part1(int fileDescriptor) {
    // Place the pointer at the end of the file
    off_t savedPos = lseek(fileDescriptor, 0, SEEK_END);
    if (savedPos == -1) {
        printf("Error occurred in lseek for initial position and 0 returned as default %s\n", strerror(errno));
        return 0; // Return 0 if lseek fails (Default)
    }

    // Write the content at the end
    const char *updated = "COMP-3753 was here! ";
    ssize_t bytesWritten = write(fileDescriptor, updated, strlen(updated));

    // Write failed
    if (bytesWritten == -1) {
        printf("Error occurred in write: %s\n", strerror(errno));
        return savedPos; // In case next write can succeed at this position
    }

    // Get the current postion after the write
    off_t currentPos = lseek(fileDescriptor, 0, SEEK_CUR);
    if (currentPos == -1) {
        printf("Error occurred in lseek for current position and returning initial as default %s\n", strerror(errno));
        return savedPos; // Same as the write
    }

    // Display the results
    printf("Bytes written: %zd\n", bytesWritten);
    printf("Difference between saved and current position: %ld\n", (long)(currentPos - savedPos));

    // Return final position
    return currentPos;
}

/*  Part2 - Reads and writes content to a file and then returns the content of the file
        Input:
            fileDescriptor - File descriptor of the file
            savedPos - The saved position of the pointer
        Algorithm:
            * Move the pointer to the saved position
            * Overwrite the content
            * Write the content
            * Move the pointer to the beginning of the file
            * Read the content of the file
            * Display the content
            * Return the content
        Output:
            Returns the content of the file
*/
char* Part2(int fileDescriptor, off_t savedPos) {
    // Get the current position
    off_t currentPos = lseek(fileDescriptor, savedPos, SEEK_SET);

    // Check if the lseek operation failed
    if (currentPos == -1) {
        printf("Error occurred in lseek for saved position %s\n", strerror(errno));
        return "Error reading acquiring saved position";
    }

    const char *overWrite = "CSPB"; // Overwrite the content

    ssize_t bytesWritten = write(fileDescriptor, overWrite, strlen(overWrite)); // Write the content

    // Check if the write operation failed
    if (bytesWritten == -1) {
        printf("Error occurred in write: %s\n", strerror(errno));
        return "Error writing the file";
    }

    // Move the pointer to the beginning of the file
    off_t finalPos = lseek(fileDescriptor, 0, SEEK_SET);

    // Check if the lseek operation failed
    if (finalPos == -1) {
        printf("Error occurred in lseek for final position %s\n", strerror(errno));
        return "Error acquiring final position";
    }

    // Read the content of the file
    char *buffer = (char *)malloc(256);
    // Check if memory allocation failed
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return "Memory allocation for file failed.";
    }

    ssize_t bytesRead = read(fileDescriptor, buffer, 255); // Space for null terminator :)

    // Check if the read operation failed
    if (bytesRead == -1) {
        printf("Error occurred in read: %s\n", strerror(errno));
        free(buffer);
        return "Read operation failed on final contents of file.";
    }

    buffer[bytesRead] = '\0'; // Null terminate the content
    printf("Final content of the file: %s\n", buffer); // Print the content

    return buffer;
}

/*  main - Entry point of the program */
int main() {
    // Open a file for reading and writing (example.txt)
    int fileDescriptor = open("example.txt", O_RDWR);

    off_t part1 = Part1(fileDescriptor);
    char *ret = (char *) Part2(fileDescriptor, part1);

    return 0;
}