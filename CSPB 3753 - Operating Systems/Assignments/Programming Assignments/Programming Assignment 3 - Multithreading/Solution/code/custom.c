/*
    custom.c - Custom functions that were developed for the the project

    Author: Taylor Larrechea
    Date - 11/14/2024
    Class: CSPB 3753 Operating Systems
    Professor: Dr. David Knox

    Functions:
        logWriter - Writes an argument fed to the function into a log file
*/
// Includes
#include "custom.h"
#include "util.h"

/*  logWriter - Writes an argument fed to the function into a log file
        Parameters:
            arg - Pointer to a LogData struct
        Algorithm:
            * Cast the input (represents the LogData struct)
            * Lock the mutex for the logs (not really necessary, but good practice)
                * Print error message if locking fails
            * Open the log file in append mode so the new lines can just be written at the end
            * If the file was opened successfully, write the input message to the file and close it
            * If the file was not opened successfully, print an error message
                * Don't want to return NULL here because unlocking the mutex is still necessary
            * Unlock the log mutex
                *  Print error message if unlocking fails
            * Return NULL
        Output:
            Function prints to log file if successful, will always return NULL in all paths
*/
void* logWriter(void* arg) {
    // Cast input parameter to LogData struct
    LogData* data = (LogData*)arg;
    // Lock the log mutex (not really necessary)
    if (pthread_mutex_lock(&log_mutex) != 0) {
        printf("Error occurred in locking of log mutex\n");
        return NULL;
    }
    // Open the log file in append mode (add to end of file)
    FILE *file = fopen(data->fileName, "a");
    // File opened successfully
    if (file) {
        // Write input message and close file
        fprintf(file, "%s", data->input);
        fclose(file);
    } 
    // Something failed
    else {
        printf("Error: Could not open log file\n");
    }
    // Unlock the log mutex
    if (pthread_mutex_unlock(&log_mutex) != 0) {
        printf("Error occurred in unlocking of log mutex\n");
        return NULL;
    }
    return NULL;
}