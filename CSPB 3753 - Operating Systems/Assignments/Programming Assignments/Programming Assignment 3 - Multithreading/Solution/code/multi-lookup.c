/*
    multi-lookup.c - Main program that creates parser and converter threads to process domain names from text files

    Author: Taylor Larrechea
    Date - 11/18/2024
    Class: CSPB 3753 Operating Systems
    Professor: Dr. David Knox

    Functions:
        list_dir - Function that lists the contents of a directory
        main - Main function that creates parser and converter threads

    Usage:
        ./multi-lookup <num_parser_threads> <num_converter_threads> <parser_log_file> <converter_log_file> <input_file1> ... <input_fileN>
*/

#include "parcov.h"
#include <dirent.h>

/*  list_dir - Function that lists the contents of a directory
        Input:
            path - Pointer to a character representing the path to the directory
        Algorithm:
            * Open the directory
                * Print error message if the directory could not be opened
            * Print the contents of the directory
            * Close the directory
                * Print error message if the directory could not be closed
        Output:
            No return value generated
*/
void list_dir(const char* path) {
    // Open the directory
    struct dirent* entry;
    DIR* dir = opendir(path);
    // Check if the directory was opened successfully
    if (dir == NULL) {
        perror("opendir failed");
        return;
    }
    // Print the contents of the directory
    printf("\nContents of directory %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    // Close the directory
    if (closedir(dir) != 0) {
        perror("closedir failed");
    }
}

int main(int argc, char* argv[]) {
    // List the contents of the input and output directories
    list_dir("input");
    list_dir("output");
    // Validate arguments
    if (argc < 6) {
        fprintf(stderr, "Usage: %s <num_parser_threads> <num_converter_threads> <parser_log_file> <converter_log_file> <input_file1> ... <input_fileN>\n", argv[0]);
        return 1;
    }
    // Grab arguments
    int num_parser_threads = atoi(argv[1]);
    int num_converter_threads = atoi(argv[2]);
    char* parserLogFile = argv[3];
    char* converterLogFile = argv[4];
    char** input_files = &argv[5];
    int num_files = argc - 4;
    // Start multiple parser threads
    multi_parser(num_parser_threads, input_files, num_files, parserLogFile);
    // Create a single converter thread
    multi_converter(num_converter_threads, converterLogFile);
    return 0;
}