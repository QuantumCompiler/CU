/*
    custom.h - Custom functions that were developed for the the project

    Author: Taylor Larrechea
    Date - 11/14/2024
    Class: CSPB 3753 Operating Systems
    Professor: Dr. David Knox

    Prototypes / Structs:
        LogData - Custom struct that holds data for a logging event
        logWriter - Function that writes a message to a log file
*/
#ifndef CUSTOM_H
#define CUSTOM_H

// Includes
#include "buffer.h" // Custom buffer file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>

/*  LogData - Struct that holds the log data
        Parameters:
            fileName - Pointer to character representing the file name
            input - Pointer to character representing the input message
*/
typedef struct {
    char* fileName;
    char* input;
} LogData;

//  logWriter - Function that will write a message to a log file
void* logWriter(void* arg);

#endif // CUSTOM_H