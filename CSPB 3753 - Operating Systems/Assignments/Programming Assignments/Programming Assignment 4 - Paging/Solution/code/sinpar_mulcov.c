/*
    * sinpar_mulcov.c - Test file for single parser and multiple converter threads

    Usage: sinpar_mulcov <num_converter_threads> <parser_log_file> <converter_log_file> <input_file1> ... <input_fileN>
*/

#include "parcov.h"

int main(int argc, char* argv[]) {
    // Usage
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <num_converter_threads> <parser_log_file> <converter_log_file> <input_file1> ... <input_fileN>\n", argv[0]);
        return 1;
    }

    int num_parser_threads = 1;
    int num_converter_threads = atoi(argv[1]);
    char* parserLogFile = argv[2];
    char* converterLogFile = argv[3];
    char** input_files = &argv[4];
    int num_files = argc - 4;

    // Debug statements to check the values of the arguments
    printf("Number of parser threads: %d\n", num_parser_threads);
    printf("Parser log file: %s\n", parserLogFile);
    printf("Converter log file: %s\n", converterLogFile);
    for (int i = 0; i < num_files; i++) {
        printf("Input file %d: %s\n", i + 1, input_files[i]);
    }

    // Start multiple parser threads
    multi_parser(num_parser_threads, input_files, num_files, parserLogFile);

    // Start multiple converter threads
    multi_converter(num_converter_threads, converterLogFile);

    printf("\nTest with a single parser thread and multiple converter thread(s) completed successfully.\n");
    printf("Filenames produced in the directory output/ have the prefix SPMC for Single Parser Multi Converter.\n");
    printf("To run the the test for this configuration, use the command: make sinpar_mulcov\n\n");
    return 0;
}