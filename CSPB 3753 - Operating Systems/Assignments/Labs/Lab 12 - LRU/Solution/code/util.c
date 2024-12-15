/*
    util.c - Source file for insertion, retrieval, and eviction functions for the LRU cache

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Functions:
        evict - Evicts the least recently used entry from the LRU cache
        insert - Inserts key-value pair into the LRU cache
        retrieve - Retrieves value from the LRU cache
        createCache - Creates a new LRU cache
        destroyCache - Destroys the LRU cache
        showCache - Displays the contents of the LRU cache
*/
#include "util.h"

/*
    createCache - Creates a new LRU cache

        Input:
            cap: Integer value that represents the capacity of the cache
            maxKeys: Integer value that represents the maximum number of keys in the cache

        Algorithm:
            * Allocate memory for cache
            * Set capacity and size
            * Allocate memory for entries and the hash table
            * Initialize hash table, -1 indicates key does not exist
        
        Output:
            Returns a pointer to the newly created LRU cache
*/
LRUCache *createCache(int cap, int maxKeys) {
    // Allocate memory for cache
    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));

    // Set capacity and size
    cache->cap = cap;
    cache->size = 0;

    // Allocate memory for entries and the hash table
    cache->entries = (Entry *)malloc(sizeof(Entry) * cap);
    cache->table = (int *)malloc(sizeof(int) * (maxKeys + 1));

    // Initialize hash table, -1 indicates key does not exist
    for (int i = 0; i <= maxKeys; i++) {
        cache->table[i] = -1;
    }

    return cache;
}

/*
    destroyCache - Destroys the LRU cache

        Input:
            cache: Pointer to the LRU cache data structure

        Algorithm:
            * Free memory for entries and hash table
            * Free memory for cache
        
        Output:
            Destroys the LRU cache
*/
void destroyCache(LRUCache *cache) {
    // Free memory for entries and hash table
    free(cache->entries);
    free(cache->table);

    // Free memory for cache
    free(cache);

    return;
}

/*
    showCache - Displays the contents of the LRU cache

        Input:
            cache: Pointer to the LRU cache data structure

        Algorithm:
            * Iterate through cache and print key-value pairs
        
        Output:
            Displays the contents of the LRU cache
*/
void showCache(LRUCache *cache) {
    printf("Current cache state (MRU to LRU):\n");
    for (int i = 0; i < cache->size; i++) {
        printf("Key: %d, Value: %d\n", cache->entries[i].key, cache->entries[i].val);
    }
    printf("\n");
}

/*
    evict - Evicts the least recently used entry from the LRU cache

        Input:
            cache: Pointer to the LRU cache data structure

        Algorithm:
            * Check if cache is empty
                * If cache is empty, return
            * Grab key of LRU entry
            * Update table and size
        
        Output:
            Evicts the least recently used entry from the LRU cache
*/
void evict(LRUCache *cache) {
    // Check if cache is empty
    if (cache->size == 0) {
        return;
    }

    // Grab key of LRU entry
    int key = cache->entries[cache->size - 1].key;

    // Update table and size
    cache->table[key] = -1;
    cache->size--;

    return;
}

/*
    insert - Inserts key-value pair into the LRU cache

        Input:
            cache: Pointer to the LRU cache data structure
            key: Integer value that represents the key of the entry
            val: Integer value that represents the value of the entry

        Algorithm:
            * Check if key exists
                * If key exists, update value from the position of the key and move entry to front
            * Check if cache is full
                * If cache is full, evict LRU entry
            * Move all entries up one in the cache
            * Insert new entry at front of cache
        
        Output:
            Inserts key-value pair into the LRU cache
*/
void insert(LRUCache *cache, int key, int val) {
    // Check if key exists
    if (cache->table[key] != -1) {
        // Grab position, assign value, and create temporary entry
        int pos = cache->table[key];    
        cache->entries[pos].val = val;  

        // Iterate from position of key to 0
        Entry tempEntry = cache->entries[pos]; 
        for (int i = pos; i > 0; i--) {
            cache->entries[i] = cache->entries[i - 1];
            cache->table[cache->entries[i].key] = i;
        }

        // Update front entry (MRU)
        cache->entries[0] = tempEntry;
        cache->table[key] = 0;
        return;
    }

    // Check if cache is full, evict LRU entry if full
    if (cache->size >= cache->cap) {
        int goodByeKey = cache->entries[cache->size - 1].key;
        cache->table[goodByeKey] = -1;
        cache->size--;
    }

    // Move items up one in cache
    for (int i = cache->size; i > 0; i--) {
        cache->entries[i] = cache->entries[i - 1];
        cache->table[cache->entries[i].key] = i;
    }

    // Insert new entry
    cache->entries[0].key = key;
    cache->entries[0].val = val;
    cache->table[key] = 0;
    cache->size++;

    return;
}

/*
    retrieve - Retrieves value from the LRU cache

        Input:
            cache: Pointer to the LRU cache data structure
            key: Integer value that represents the key of the entry

        Algorithm:
            * Check if key exists
                * If key does not exist, return -1
            * If key exists, shift entries from position to 0 and update front entry (MRU)
        
        Output:
            Returns value from the LRU cache if key exists, otherwise returns -1
*/
int retrieve(LRUCache *cache, int key) {
    // Check if already exists
    int pos = cache->table[key];

    // Cache miss, return - 1
    if (pos == -1) {
        return -1;
    }

    // Shift entries from position to 0
    Entry tempEntry = cache->entries[pos];
    for (int i = pos; i > 0; i--) {
        cache->entries[i] = cache->entries[i - 1];
        cache->table[cache->entries[i].key] = i;
    }

    // Update front entry (MRU)
    cache->entries[0] = tempEntry;
    cache->table[key] = 0;

    return cache->entries[0].val;
}