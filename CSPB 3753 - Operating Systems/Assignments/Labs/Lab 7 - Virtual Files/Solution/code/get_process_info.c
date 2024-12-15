/*
    get_process_info.c - A program to get information about a process on a Linux system
    Functions Included 
        get_process_info - Retrieves information about a process
    Libraries Imported:
        stdio.h - Standard Input/Output
        stdlib.h - Standard Library
        unistd.h - Standard symbolic constants and types
        sys/types.h - Data types
        string.h - String operations
    Macros:
        None
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

/*  process_info - Structure to hold information about a process
        user_time_sec - User time in seconds
        kernel_time_sec - Kernel time in seconds
        start_time_sec - Start time in seconds since boot
        running_time_sec - Running time in seconds
        waiting_time_sec - Waiting time in seconds
        buffer - Buffer to hold environment variables
        contents - Buffer to hold address space contents
*/
struct process_info {
    unsigned long user_time_sec;
    unsigned long kernel_time_sec;
    double start_time_sec;
    double running_time_sec;
    double waiting_time_sec;
    char buffer[65536];
    char contents[65536];
};

/*  get_process_info - Retrieves information about a process
        Input:
            pid - The process ID
        Algorithm:
            * Create a process_info structure
            * Initialize the structure at 0
            * Open the /proc/[PID]/stat file
                * If it fails, return an error
            * Read the contents of the file
            * Close the file
            * Parse the contents of the file
            * Get the clock ticks per second
            * Calculate the times in seconds
            * Get the system uptime
            * Read the uptime from the file
            * Close the file
            * Calculate the process times
            * Check if the process start time is in the future
            * Calculate the running and waiting times
            * Fill the process_info structure
            * Open the /proc/[PID]/environ file
                * If it fails, return an error
            * Read the environment variables
            * Add a null terminator to the buffer
            * Close the file
            * Replace null characters with newlines
            * Open the /proc/[PID]/maps file
                * If it fails, return an error
            * Print the results
            * Read the contents of the file
            * Close the file
        Output:
            None
*/
void get_process_info(pid_t pid) {
    // Create a process_info structure
    struct process_info procInfo;
    // Initialize the structure at 0
    memset(&procInfo, 0, sizeof(procInfo));
    // Open the /proc/[PID]/stat file
    char stat_path[256];
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
    FILE *statInfo = fopen(stat_path, "r");
    if (statInfo == NULL) {
        printf("Error opening /proc/[PID]/stat");
    }
    // Read the contents of the file
    char buffer[4096];
    if (fgets(buffer, sizeof(buffer), statInfo) == NULL) {
        printf("Error reading /proc/[PID]/stat");
        fclose(statInfo);
    }
    // Close the file
    fclose(statInfo);
    // Parse the contents of the file
    char *ptr = strchr(buffer, ')');
    if (ptr == NULL) {
        printf("Malformed /proc/[PID]/stat file\n");
    }
    // Skip the ')' character
    ptr++;
    // Parse the fields of the file
    unsigned long utime_ticks, stime_ticks;
    unsigned long long starttime_ticks;
    int scanned = sscanf(ptr,
        " %*c"      // Field 3: state (char)
        " %*d"      // Field 4: ppid
        " %*d"      // Field 5: pgrp
        " %*d"      // Field 6: session
        " %*d"      // Field 7: tty_nr
        " %*d"      // Field 8: tpgid
        " %*u"      // Field 9: flags
        " %*u"      // Field 10: minflt
        " %*u"      // Field 11: cminflt
        " %*u"      // Field 12: majflt
        " %*u"      // Field 13: cmajflt
        " %lu"      // Field 14: utime
        " %lu"      // Field 15: stime
        " %*d"      // Field 16: cutime
        " %*d"      // Field 17: cstime
        " %*d"      // Field 18: priority
        " %*d"      // Field 19: nice
        " %*d"      // Field 20: num_threads
        " %*d"      // Field 21: itrealvalue
        " %llu",    // Field 22: starttime
        &utime_ticks,
        &stime_ticks,
        &starttime_ticks
    );
    // Check if all fields were parsed
    if (scanned != 3) {
        printf("Error parsing /proc/[PID]/stat fields: scanned %d fields instead of 3\n", scanned);
    }
    // Get the clock ticks per second
    long clk_tck = sysconf(_SC_CLK_TCK);
    if (clk_tck == -1) {
        printf("sysconf");
    }
    // Calculate the times in seconds
    double user_time_sec = (double)utime_ticks / clk_tck;
    double kernel_time_sec = (double)stime_ticks / clk_tck;
    double start_time_sec = (double)starttime_ticks / clk_tck;
    // Get the system uptime
    FILE *uptimeFile = fopen("/proc/uptime", "r");
    if (uptimeFile == NULL) {
        printf("Error opening /proc/uptime");
    }
    // Read the uptime from the file
    double system_uptime;
    if (fscanf(uptimeFile, "%lf", &system_uptime) != 1) {
        printf("Error reading system uptime\n");
        fclose(uptimeFile);
    }
    // Close the file
    fclose(uptimeFile);
    // Calculate the process times
    double process_start_time = start_time_sec;
    double elapsed_time = system_uptime - process_start_time;
    // Check if the process start time is in the future
    if (elapsed_time < 0) {
        printf("Error: Process start time is in the future\n");
    }
    // Calculate the running and waiting times
    double running_time = user_time_sec + kernel_time_sec;
    double waiting_time = elapsed_time - running_time;
    // Check if the waiting time is negative
    if (waiting_time < 0) {
        printf("Warning: Waiting time calculated as negative. Adjusting to 0.\n");
        waiting_time = 0.0;
    }
    // Fill the process_info structure
    procInfo.user_time_sec = (unsigned long)user_time_sec;
    procInfo.kernel_time_sec = (unsigned long)kernel_time_sec;
    procInfo.start_time_sec = start_time_sec;
    procInfo.running_time_sec = running_time;
    procInfo.waiting_time_sec = waiting_time;
    // Open the /proc/[PID]/environ file
    char envPath[256];
    snprintf(envPath, sizeof(envPath), "/proc/%d/environ", pid);
    FILE *envInfo = fopen(envPath, "r");
    if (envInfo == NULL) {
        printf("Error opening /proc/PID/environ");
    }
    // Read the environment variables
    size_t envSize = fread(procInfo.buffer, 1, sizeof(procInfo.buffer) - 1, envInfo);
    if (envSize == 0) {
        printf("No environment variables present");
        fclose(envInfo);
    }
    // Add a null terminator to the buffer
    procInfo.buffer[envSize] = '\0';
    // Close the file
    fclose(envInfo);
    // Replace null characters with newlines
    for (int i = 0; i < envSize; i++) {
        if (procInfo.buffer[i] == '\0') {
            procInfo.buffer[i] = '\n';
        }
    }
    // Open the /proc/[PID]/maps file
    char addPath[256];
    snprintf(addPath, sizeof(addPath), "/proc/%d/maps", pid);
    FILE *addsInfo = fopen(addPath, "r");
    if (addsInfo == NULL) {
        printf("Error opening /proc/[PID]/maps");
    }
    // Print the results
    printf("Process ID (PID): %d\n", pid);
    printf("User Time: %.2f seconds\n", user_time_sec);
    printf("Kernel Time: %.2f seconds\n", kernel_time_sec);
    printf("Start Time: %.2f seconds since boot\n", process_start_time);
    printf("Running Time (User + Kernel): %.2f seconds\n", running_time);
    printf("Waiting Time: %.2f seconds\n", waiting_time);
    printf("Environment variables:\n\n%s\n", procInfo.buffer);
    printf("Address space contents:\n\n");
    // Read the contents of the file
    while (fgets(buffer, sizeof(buffer), addsInfo) != NULL) {
        printf("%s", buffer);
    }
    // Close the file
    fclose(addsInfo);
}

int main(int argc, char *argv[]) {
    // Get the PID from the command line
    pid_t pid;
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return EXIT_FAILURE;
    }
    // Convert the PID to an integer
    pid = atoi(argv[1]);
    if (pid <= 0) {
        printf("Invalid PID: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    // Get the process information
    get_process_info(pid);
    return 0;
}