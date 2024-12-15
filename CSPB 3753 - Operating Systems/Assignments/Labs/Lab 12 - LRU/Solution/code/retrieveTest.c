/*
    retrieveTest.c - A test file for the retrieve function in util.c

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Functions:
        singleRetrieve - Tests the retrieval of a single key from the LRU cache
        multiRetrieve - Tests the retrieval of multiple keys from the LRU cache
        evictRetrieve - Tests the retrieval of keys from an LRU cache that has had entries evicted
*/
#include "util.h"

// singleRetrieve - Tests the retrieval of a single key from the LRU cache
void singleRetrieve() {
    printf("Running retrieval of one key test.\n");

    LRUCache *cache = createCache(3, 10);
    insert(cache, 1, 1);
    showCache(cache);

    printf("Attempting to retrieve key 1 with value 1.\n");
    int val = retrieve(cache, 1);
    printf("Retrieved value: %d\n", val);

    destroyCache(cache);
}

// multiRetrieve - Tests the retrieval of multiple keys from the LRU cache
void multiRetrieve() {
    printf("Running retrieval of multiple keys test.\n");

    LRUCache *cache = createCache(3, 10);
    insert(cache, 1, 1);
    insert(cache, 2, 2);
    insert(cache, 3, 3);
    showCache(cache);

    printf("Attempting to retrieve key 1 with value 1.\n");
    int val = retrieve(cache, 1);
    printf("Retrieved value: %d\n", val);
    showCache(cache);

    printf("Attempting to retrieve key 2 with value 2.\n");
    val = retrieve(cache, 2);
    printf("Retrieved value: %d\n", val);
    showCache(cache);

    printf("Attempting to retrieve key 3 with value 3.\n");
    val = retrieve(cache, 3);
    printf("Retrieved value: %d\n", val);
    showCache(cache);

    destroyCache(cache);
}

// evictRetrieve - Tests the retrieval of keys from an LRU cache that has had entries evicted
void evictRetrieve() {
    printf("Running retrieval test with eviction.\n");

    LRUCache *cache = createCache(3, 10);
    insert(cache, 1, 1);
    insert(cache, 2, 2);
    insert(cache, 3, 3);
    showCache(cache);

    evict(cache);
    showCache(cache);

    printf("Attempting to retrieve key 1 with value 1.\n");
    int val = retrieve(cache, 1);
    printf("Retrieved value: %d\n", val);

    evict(cache);
    showCache(cache);

    printf("Attempting to retrieve key 2 with value 2.\n");
    val = retrieve(cache, 2);
    printf("Retrieved value: %d\n", val);

    printf("Attempting to retrieve key 3 with value 3.\n");
    val = retrieve(cache, 3);
    printf("Retrieved value: %d\n", val);

    evict(cache);
    showCache(cache);

    printf("Attempting to retrieve key 3 with value 3.\n");
    val = retrieve(cache, 3);
    printf("Retrieved value: %d\n", val);

    destroyCache(cache);
}