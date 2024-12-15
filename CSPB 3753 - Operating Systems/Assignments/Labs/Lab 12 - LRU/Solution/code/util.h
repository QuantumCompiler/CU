/*
    util.h - Header file for util.c functions

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Prototypes:
        evict - Evicts the least recently used entry from the LRU cache
        insert - Inserts key-value pair into the LRU cache
        retrieve - Retrieves value from the LRU cache
        createCache - Creates a new LRU cache
        destroyCache - Destroys the LRU cache
        showCache - Displays the contents of the LRU cache
*/
#ifndef UTIL_H
#define UTIL_H

#include "def.h"

// evict - Evicts the least recently used entry from the LRU cache
void evict(LRUCache *cache);

// insert - Inserts key-value pair into the LRU cache
void insert(LRUCache *cache, int key, int val);

// retrieve - Retrieves value from the LRU cache
int retrieve(LRUCache *cache, int key);

// createCache - Creates a new LRU cache
LRUCache *createCache(int cap, int maxKeys);

// destroyCache - Destroys the LRU cache
void destroyCache(LRUCache *cache);

// showCache - Displays the contents of the LRU cache
void showCache(LRUCache *cache);
#endif // UTIL_H