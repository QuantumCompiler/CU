/*
    insertTest.c - Test functions for the insert function in util.c

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Functions:
        singleInsert - Tests the insertion of a single key-value pair into the LRU cache
        duplicateInsert - Tests the insertion of a duplicate key into the LRU cache
        multiInsert - Tests the insertion of multiple key-value pairs into the LRU cache
        evictInsert - Tests the eviction of the least recently used entry when inserting into a full LRU cache
*/
#include "insertTest.h"

// singleInsert - Tests the insertion of a single key-value pair into the LRU cache
void singleInsert() {
    printf("Running insertion of one key test.\n");
    LRUCache *cache = createCache(3, 10);
    insert(cache, 1, 1);
    showCache(cache);
    destroyCache(cache);
}

// duplicateInsert - Tests the insertion of a duplicate key into the LRU cache
void duplicateInsert() {
    printf("Running insertion of duplicate key test.\n");
    LRUCache *cache = createCache(3, 10);
    insert(cache, 1, 1);
    showCache(cache);
    insert(cache, 1, 2);
    showCache(cache);
    insert(cache, 1, 3);
    showCache(cache);
    insert(cache, 2, 20);
    showCache(cache);
    insert(cache, 2, 25);
    showCache(cache);
    insert(cache, 2, 29);
    showCache(cache);
    insert(cache, 3, 30);
    showCache(cache);
    insert(cache, 3, 31);
    showCache(cache);
    insert(cache, 3, 32);
    showCache(cache);
    destroyCache(cache);
}

// multiInsert - Tests the insertion of multiple key-value pairs into the LRU cache
void multiInsert() {
    printf("Running insertion of five keys test.\n");
    LRUCache *cache = createCache(5, 10);
    insert(cache, 1, 1);
    insert(cache, 2, 2);
    insert(cache, 3, 3);
    insert(cache, 4, 4);
    insert(cache, 5, 5);
    showCache(cache);
    destroyCache(cache);
}

// evictInsert - Tests the eviction of the least recently used entry when inserting into a full LRU cache
void evictInsert() {
    printf("Running insertion test with eviction.\n");
    LRUCache *cache = createCache(3, 10);
    insert(cache, 1, 1);
    insert(cache, 2, 2);
    insert(cache, 3, 3);
    showCache(cache);
    insert(cache, 4, 24);
    showCache(cache);
    insert(cache, 2, 10);
    showCache(cache);
    insert(cache, 3, 23);
    showCache(cache);
    destroyCache(cache);
}