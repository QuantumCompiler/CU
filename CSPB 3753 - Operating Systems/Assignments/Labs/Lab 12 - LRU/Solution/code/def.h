/*
    def.h - Header file for basic library includes, global variables, etc.

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Custom Data Structures:
    
        Entry - Data structure for an entry in the LRU cache
        LRUCache - Data structure for a Least Recently Used (LRU) cache
*/
#ifndef DEF_H
#define DEF_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    Entry - Data structure for an entry in the LRU cache

    key: Integer value that represents the key of the entry
    val: Integer value that represents the value of the entry
*/
typedef struct Entry {
    int key;    // Key of the entry
    int val;    // Value of the entry
} Entry;

/*
    LURCache - Data structure for a Least Recently Used (LRU) cache

    cap: Integer value that represents the capacity of the cache
    size: Integer value that represents the current size of the cache
    table: Array of integers that represents the "hash table" for the cache
    entries: Array of Entry structs that represents the entries in the cache
*/
typedef struct LRUCache {
    int cap;        // Capacity of the cache
    int size;       // Current size of the cache
    int *table;     // "Hash table" for the cache
    Entry *entries; // Array of entries
} LRUCache;

#endif // DEF_H