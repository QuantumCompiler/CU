/*
    parcov.h - Header file for the parser and converter functions

    Author: Taylor Larrechea
    Date - 11/14/2024
    Class: CSPB 3753 Operating Systems
    Professor: Dr. David Knox

    Prototypes / Structs:
        ThreadArgs - Struct that holds the arguments for the thread
        converter - Function that performs DNS lookups on domain names in the buffer
        multi_converter - Function that creates multiple converter threads
        multi_parser - Function that creates multiple parser threads
        parser - Function that reads domain names from input files and adds them to the global buffer
*/
#ifndef PARCOV_H
#define PARCOV_H

// Includes

#include "custom.h"
#include "util.h"

/*  ThreadArgs - Struct that holds the arguments for the thread
        Parameters:
            input_files - Pointer to a pointer to a character representing the input files
            output_file - Pointer to a character representing the output file
            num_files - Integer representing the number of input files
*/
typedef struct {
    char** input_files;
    char* output_file;
    int num_files;
} ThreadArgs;

// Prototypes

// converter - Function that performs DNS lookups on domain names in the buffer
void* converter(void* arg);
// multi_converter - Function that creates multiple converter threads
void multi_converter(int threads, char* log);
// multi_parser - Function that creates multiple parser threads
void multi_parser(int threads, char** input_files, int num_files, char* log);
// parser - Function that reads domain names from input files and adds them to the global buffer
void* parser(void* arg);

#endif // PARCOV_H