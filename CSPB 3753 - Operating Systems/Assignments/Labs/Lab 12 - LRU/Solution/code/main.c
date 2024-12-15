/*
    main.c - Source file for the main function

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Functions:
        main - Main function for the LRU cache program

        Usage:
            * ./EXECNAME <cache_capacity> <max_keys>
*/
#include "util.h"

int main(int argc, char *argv[]) {
    // Validate number of inputs
    if (argc != 3) {
        printf("Usage: %s <cache_capacity> <max_keys>\n", argv[0]);
        return 1;
    }

    // Grab inputs
    int cap = atoi(argv[1]);
    int maxKeys = atoi(argv[2]);

    // Validate inputs again
    if (cap <= 0 || maxKeys <= 0) {
        printf("Error: Invalid input\n");
        return 1;
    }

    // Create cache
    LRUCache *cache = createCache(cap, maxKeys);
    if (cache == NULL) {
        printf("Error: Unable to create cache\n");
        return 1;
    }

    printf("\nCache created with capacity %d and max keys %d, please enter commands.\n", cap, maxKeys);

    printf("\nCommands:\n");
    printf("\ni: <key> <value> - Insert key-value pair\n");
    printf("r: <key> - Retrieve value from key\n");
    printf("e: Evict least recently used entry\n");
    printf("s: Show cache\n");
    printf("q: Quit\n\n");

    // Buffer for command and key value pairs
    char cmd[10];
    int key, val;

    // Command loop
    while(1) {
        printf("> ");
        scanf("%s", cmd);
        // Insert command
        if (strcmp(cmd, "i") == 0) {
            scanf("%d %d", &key, &val);
            insert(cache, key, val);
        } 
        // Retrieve command
        else if (strcmp(cmd, "r") == 0) {
            scanf("%d", &key);
            int result = retrieve(cache, key);
            if (result != -1) {
                printf("Value: %d\n", result);
            } 
            else {
                printf("Key not found\n");
            }
        }
        // Evict command
        else if (strcmp(cmd, "e") == 0) {
            evict(cache);
        }
        // Show command
        else if (strcmp(cmd, "s") == 0) {
            showCache(cache);
        }
        // Quit command
        else if (strcmp(cmd, "q") == 0) {
            destroyCache(cache);
            break;
        } 
        // Invalid command
        else {
            printf("Invalid command\n");
        }
    }
    return 0;
}