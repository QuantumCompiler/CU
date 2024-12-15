/*
    get_sys_info.c - A program to get system information on from Linux systems
    Functions Included 
        get_cpu_info - Function to get information about the CPUs on the system
        get_linux_version - Retrieves the linux version 
        get_system_uptime - Retrieves the system uptime
        get_avg_load - Retrieves the average load on the system
        get_mem_info - Retrieves memory information
        get_swap_info - Retrieves information about swap partitions
        get_cpu_time - Retrieves the CPU usage information
        get_context_switches - Retrieves the number of context switches on the system
    Libraries Imported:
        stdio.h - Standard Input/Output
        stdlib.h - Standard Library
        unistd.h - Standard symbolic constants and types
        sys/types.h - Data types
        sys/stat.h - File information
        fcntl.h - File control options
        string.h - String operations
    Macros:
        MAX_CPUS - Maximum number of CPUs
        MAX_PARTITIONS - Maximum number of partitions
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_CPUS 128 // Maximum number of CPUs
#define MAX_PARTITIONS 10 // Maximum number of partitions

/*  cpu_info - Structure to hold information about a CPU
        processor_id - The ID of the processor
        clock_speed - The clock speed of the processor in MHz
        cores - The number of cores on the processor
*/
struct cpu_info {
    int processor_id;
    double clock_speed;
    int cores;
};

/*  get_cpu_info - Function to get information about the CPUs on the system
        input:
            cpus - An array of cpu_info structures to hold the CPU information
        Algorithm:
            * Open the /proc/cpuinfo file
                * If it fails, return an error
            * Declare a buffer to hold the lines read from the file
            * Initialize the current_cpu index to -1
            * Read the file line by line
                * Look for the CPU information
                * Look for the clock speed in MHz
                * Look for the number of cores
            * Close the file
            * Return the number of CPUs found
        Output:
            Returns number of CPUs on a system
*/
int get_cpu_info(struct cpu_info cpus[]) {
    // Open the /proc/cpuinfo file
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL) {
        printf("Error opening /proc/cpuinfo");
        return -1;
    }
    // Declare a buffer to hold the lines read from the file
    char buffer[256];
    int current_cpu = -1; // Index from zero
    // Read the file line by line
    while (fgets(buffer, sizeof(buffer), cpuinfo)) {
        // Look for new CPU
        if (strstr(buffer, "processor") != NULL) {
            current_cpu++;  // Move to the next CPU
            sscanf(buffer, "processor : %d", &cpus[current_cpu].processor_id); // Get the processor ID
        }
        // Look for clock speed in MHz
        if (strstr(buffer, "cpu MHz") != NULL) {
            sscanf(buffer, "cpu MHz : %lf", &cpus[current_cpu].clock_speed); // Get the clock speed
        }
        // Look for the number of cores
        if (strstr(buffer, "cpu cores") != NULL) {
            sscanf(buffer, "cpu cores : %d", &cpus[current_cpu].cores); // Get the number of cores
        }
    }
    fclose(cpuinfo); // Close the file
    return current_cpu + 1; // Return the number of CPUs found
}

/*  get_linux_version - Retrieves the linux version 
        Input:
            None
        Algorithm:
            * Open the /proc/version file
                * If it fails, return an error
            * Declare a buffer to hold the lines read from the file
            * Read the file line by line
                * Allocate memory for the return string
                * Copy the line to the return string
            * Close the file
            * Return the Linux version
        Output:
            Returns the Linux version
*/
char* get_linux_version() {
    // Open the /proc/version file
    FILE *linuxInfo = fopen("/proc/version", "r");
    if (linuxInfo == NULL) {
        printf("Error opening /proc/version");
        return NULL;
    }
    // Declare a buffer to hold the lines read from the file
    char buffer[256];
    // Read the file line by line
    if (fgets(buffer, sizeof(buffer), linuxInfo) != NULL) {
        // Allocate memory for the return string
        char *ret = malloc(strlen(buffer) + 1);
        if (ret != NULL) {
            strcpy(ret, buffer);
        }
        return ret; // Return the Linux version
    }
    fclose(linuxInfo); // Close the file
    return NULL; // Return NULL if no version found
}

/*  get_system_uptime - Retrieves the system uptime
        Input:
            None
        Algorithm:
            * Open the /proc/uptime file
                * If it fails, return an error
            * Read the uptime from the file
            * Calculate the days, hours, minutes, and seconds
            * Allocate memory for the return string
            * Format the return string
            * Return the system uptime
        Output:
            Returns the system uptime
*/
char* get_system_uptime() {
    // Open the /proc/uptime file
    FILE *upTimeFile = fopen("/proc/uptime", "r");
    if (upTimeFile == NULL) {
        printf("Error opening /proc/uptime");
        return NULL;
    }
    // Read the uptime from the file
    double upTimeRaw;
    fscanf(upTimeFile, "%lf", &upTimeRaw);
    fclose(upTimeFile);
    // Calculate the days, hours, minutes, and seconds
    int days = (int)(upTimeRaw / 86400);
    int hours = (int)((upTimeRaw - (days * 86400)) / 3600);
    int minutes = (int)((upTimeRaw - (days * 86400) - (hours * 3600)) / 60);
    int seconds = (int)(upTimeRaw - (days * 86400) - (hours * 3600) - (minutes * 60));
    // Allocate memory for the return string
    char *upTimeRet = malloc(65 * sizeof(char));
    if (upTimeRet == NULL) {
        printf("Memory allocation failed.");
        return NULL;
    }
    // Format the return string
    snprintf(upTimeRet, 64, "%d days %d hours %d minutes %d seconds", days, hours, minutes, seconds);
    return upTimeRet;
}

/*  get_avg_load - Retrieves the average load on the system
        Input:
            None
        Algorithm:
            * Open the /proc/loadavg file
                * If it fails, return an error
            * Read the load from the file
            * Allocate memory for the return string
            * Format the return string
            * Return the average load
        Output:
            Returns the average load on the system
*/
char* get_avg_load() {
    // Open the /proc/loadavg file
    FILE *avgLoadFile = fopen("/proc/loadavg", "r");
    if (avgLoadFile == NULL) {
        printf("Error opening /proc/loadavg");
        return NULL;
    }
    // Read the load from the file
    double load15Min;
    fscanf(avgLoadFile, "%lf", &load15Min);
    fclose(avgLoadFile);
    // Allocate memory for the return string
    char *avgLoad = malloc(16 * sizeof(char));
    if (avgLoad == NULL) {
        printf("Memory allocation for return failed.");
        return NULL;
    }
    // Format the return string
    snprintf(avgLoad, 16, "%.2f", load15Min);
    return avgLoad;
}

/*  mem_info - Structure to hold information about memory
        mem_total - Total memory
        mem_free - Free memory
        mem_avail - Available memory
        buffers - Buffers
        cache - Cache
        swapTotal - Total swap
        swapFree - Free swap
*/
struct mem_info {
    unsigned long mem_total;
    unsigned long mem_free;
    unsigned long mem_avail;
    unsigned long buffers;
    unsigned long cache;
    unsigned long swapTotal;
    unsigned long swapFree;
};

/*  get_mem_info - Retrieves memory information
        Input:
            None
        Algorithm:
            * Open the /proc/meminfo file
                * If it fails, return an error
            * Declare a buffer to hold the lines read from the file
            * Read the file line by line
                * Look for memory information
            * Close the file
            * Allocate memory for the return string
            * Format the return string
            * Return the memory information
        Output:
            Returns the memory information
*/
char* get_mem_info() {
    // Open the /proc/meminfo file
    FILE *memInfo = fopen("/proc/meminfo", "r");
    if (memInfo == NULL) {
        printf("Error opening /proc/meminfo\n");
        return NULL;
    }
    // Declare a buffer to hold the lines read from the file
    struct mem_info memory = {0};
    char buffer[256];
    // Read the file line by line
    while (fgets(buffer, sizeof(buffer), memInfo)) {
        sscanf(buffer, "MemTotal: %lu kB", &memory.mem_total);
        sscanf(buffer, "MemFree: %lu kB", &memory.mem_free);
        sscanf(buffer, "MemAvailable: %lu kB", &memory.mem_avail);
        sscanf(buffer, "Buffers: %lu kB", &memory.buffers);
        sscanf(buffer, "Cached: %lu kB", &memory.cache);
        sscanf(buffer, "SwapTotal: %lu kB", &memory.swapTotal);
        sscanf(buffer, "SwapFree: %lu kB", &memory.swapFree);
    }
    // Close the file
    fclose(memInfo);
    char *ret = malloc(512 * sizeof(char));
    if (ret == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // Format the return string
    snprintf(ret, 512,
        "MemTotal: %lu kB\n"
        "MemFree: %lu kB\n"
        "MemAvailable: %lu kB\n"
        "Buffers: %lu kB\n"
        "Cached: %lu kB\n"
        "SwapTotal: %lu kB\n"
        "SwapFree: %lu kB\n",
        memory.mem_total, memory.mem_free, memory.mem_avail,
        memory.buffers, memory.cache, memory.swapTotal, memory.swapFree);
    return ret; // Return the memory information
}

/*  swap_info - Structure to hold information about a swap partition
        filename - The filename of the swap partition
        type - The type of the swap partition
        size - The size of the swap partition
        used - The amount of the swap partition used
        priority - The priority of the swap partition
*/
struct swap_info {
    char filename[128];
    char type[16];
    unsigned long size;
    unsigned long used;
    int priority;
};

/*  get_swap_info - Retrieves information about swap partitions
        Input:
            swaps - An array of swap_info structures to hold the swap information
        Algorithm:
            * Open the /proc/swaps file
                * If it fails, return an error
            * Declare a buffer to hold the lines read from the file
            * Read the file line by line
                * Look for swap information
            * Close the file
            * Return the number of swap partitions found
        Output:
            Returns the number of swap partitions found
*/
int get_swap_info(struct swap_info swaps[]) {
    // Open the /proc/swaps file
    FILE *swapInfo = fopen("/proc/swaps", "r");
    if (swapInfo == NULL) {
        printf("Error opening /proc/swaps\n");
        return -1;
    }
    // Declare a buffer to hold the lines read from the file
    char buffer[256];
    fgets(buffer, sizeof(buffer), swapInfo);
    int swap_count = 0;
    // Read the file line by line
    while (fgets(buffer, sizeof(buffer), swapInfo)) {
        if (swap_count >= MAX_PARTITIONS) {
            break;
        }
        // Look for swap information
        sscanf(buffer, "%127s %15s %lu %lu %d", 
                swaps[swap_count].filename, swaps[swap_count].type, 
                &swaps[swap_count].size, &swaps[swap_count].used, 
                &swaps[swap_count].priority);
        swap_count++;
    }
    // Close the file
    fclose(swapInfo);
    return swap_count; // Return the number of swap partitions found
}

/*  get_cpu_time - Retrieves the CPU usage information
        Input:
            None
        Algorithm:
            * Open the /proc/stat file
                * If it fails, return an error
            * Declare a buffer to hold the lines read from the file
            * Read the file line by line
                * Look for CPU time information
            * Close the file
            * Calculate the total user and kernel time
            * Allocate memory for the return string
            * Format the return string
            * Return the CPU usage information
        Output:
            Returns the CPU usage information
*/
char* get_cpu_time() {
    // Open the /proc/stat file
    FILE *cpuInfo = fopen("/proc/stat", "r");
    if (cpuInfo == NULL) {
        printf("Error opening /proc/stat");
        return NULL;
    }
    // Declare a buffer to hold the lines read from the file
    char buffer[256];
    unsigned long userTime;
    unsigned long niceTime; // Low priority user
    unsigned long systemTime;
    unsigned long idleTime;
    unsigned long waitTime;
    unsigned long irqTime;
    unsigned long softirqTime;
    // Read the file line by line
    if (fgets(buffer, sizeof(buffer), cpuInfo)) {
        // Look for CPU time information
        sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu", &userTime, &niceTime, &systemTime, &idleTime, &waitTime, &irqTime, &softirqTime);
        // Close the file
        fclose(cpuInfo);
        // Calculate the total user and kernel time
        unsigned long totalUserTime = userTime + niceTime; 
        unsigned long totalKernelTime = systemTime;
        double userTime = (double)totalUserTime / sysconf(_SC_CLK_TCK);
        double kernelTime = (double)totalKernelTime / sysconf(_SC_CLK_TCK);
        // Allocate memory for the return string
        char *ret = malloc(128 * sizeof(char));
        if (ret == NULL) {
            printf("Memory allocation failed");
            return NULL;
        }
        // Format the return string
        snprintf(ret, 128,
            "CPU Time Spent in User Mode: %.2f seconds\n"
            "CPU Time Spent in Kernel Mode: %.2f seconds\n",
            userTime, kernelTime
        );
        return ret; // Return the CPU usage information
    }
}

/*  get_context_switches - Retrieves the number of context switches on the system
        Input:
            None
        Algorithm:
            * Open the /proc/stat file
                * If it fails, return an error
            * Declare a buffer to hold the lines read from the file
            * Read the file line by line
                * Look for context switch information
            * Close the file
            * Return the number of context switches
        Output:
            Returns the number of context switches on the system
*/
unsigned long get_context_switches() {
    // Open the /proc/stat file
    FILE *contextInfo = fopen("/proc/stat", "r");
    if (contextInfo == NULL) {
        printf("Error opening /proc/stat");
        return -1;
    }
    // Declare a buffer to hold the lines read from the file
    char buffer[256];
    // Read the file line by line
    unsigned long ret = 0;
    while (fgets(buffer, sizeof(buffer), contextInfo)) {
        if (sscanf(buffer, "ctxt %lu", &ret) == 1) {
            break;
        }
    }
    // Close the file
    fclose(contextInfo);
    return ret; // Return the number of context switches
}

/*  main - The main function of the program
        Input:
            None
        Algorithm:
            * Get CPU information
            * Print CPU information
            * Get Linux version
            * Print Linux version
            * Get system uptime
            * Print system uptime
            * Get average load
            * Print average load
            * Get memory information
            * Print memory information
            * Get swap information
            * Print swap information
            * Get CPU usage information
            * Print CPU usage information
            * Get context switches
            * Print context switches
        Output:
            Returns 0 on success
*/
int main() {
    // Get CPU information
    struct cpu_info cpus[MAX_CPUS]; 
    int cpu_count = get_cpu_info(cpus);
    if (cpu_count <= 0) {
        printf("No CPU information found.\n");
        return 1;
    }
    // Print CPU information
    printf("CPU Information:\n");
    for (int i = 0; i < cpu_count; i++) {
        printf("CPU %d:\n", cpus[i].processor_id);
        printf("    Clock Speed: %.2f MHz\n", cpus[i].clock_speed);
        printf("    Number of Cores: %d\n", cpus[i].cores);
    }
    // Get linux version 
    char *linux_version = get_linux_version();
    if (linux_version != NULL) {
        printf("Linux Version: %s\n", linux_version);
        free(linux_version);
    } else {
        printf("Obtaining Linux Version failed.");
    }
    // Get system uptime
    char *upTime = get_system_uptime();
    if (upTime != NULL) {
        printf("System Uptime: %s\n", upTime);
        free(upTime);
    }
    // Get average load
    char *avgLoad = get_avg_load();
    if (avgLoad != NULL) {
        printf("Average load on system over the past 15 minutes: %s\n", avgLoad);
        free(avgLoad);
    }
    // Get memory information
    char *memInfo = get_mem_info();
    if (memInfo != NULL) {
        printf("Memory inforation:\n%s\n", memInfo);
        free(memInfo);
    }
    // Get swap information
    struct swap_info swaps[MAX_PARTITIONS];
    int swap_count = get_swap_info(swaps);
    // Print swap information
    if (swap_count < 0) {
        printf("Error in obtaining swaps.");
    } 
    // Print swap information
    else if (swap_count == 0) {
        printf("No swaps currently on system.\n");
    } 
    // Print swap information
    else {
        printf("Swap Information:\n");
        // Print swap information
        for (int i = 0; i < swap_count; i++) {
            printf("Filename: %s\n", swaps[i].filename);
            printf("Type: %s\n", swaps[i].type);
            printf("Size: %lu kB\n", swaps[i].size);
            printf("Used: %lu kB\n", swaps[i].used);
            printf("Priority: %d\n\n", swaps[i].priority);
        }
    }
    // Get CPU usage information
    char *systemInfo = get_cpu_time();
    if (systemInfo != NULL) {
        printf("CPU Usage Information:\n%s\n", systemInfo);
        free(systemInfo);
    }
    // Get context switches
    unsigned long contextSwitches = get_context_switches();
    // Print context switches
    if (contextSwitches > 0) {
        printf("Number of context switches on system: %lu\n", contextSwitches);
    } 
    // Print context switches
    else {
        printf("No context swtiches found on system");
    }
    return 0;
}