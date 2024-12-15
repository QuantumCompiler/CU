/*
    evictTest.c - A test file for the evict function in util.c

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Functions:
        singleEvict - Tests the eviction of a single entry from the LRU cache
        multiEvict - Tests the eviction of multiple entries from the LRU cache
        emptyEvict - Tests the eviction of entries from an empty LRU cache
*/
#include "util.h"

// singleEvict - Tests the eviction of a single entry from the LRU cache
void singleEvict() {
    printf("Running eviction of one key test.\n");

    LRUCache *cache = createCache(3, 10);
    insert(cache, 1, 1);
    showCache(cache);

    printf("Evicting key 1 with value 1.\n");
    evict(cache);
    showCache(cache);

    destroyCache(cache);
}

// multiEvict - Tests the eviction of multiple entries from the LRU cache
void multiEvict() {
    printf("Running eviction of multiple keys test.\n");

    LRUCache *cache = createCache(3, 10);
    insert(cache, 1, 1);
    insert(cache, 2, 2);
    insert(cache, 3, 3);
    showCache(cache);

    printf("Evicting key 1 with value 1.\n");
    evict(cache);
    showCache(cache);

    printf("Evicting key 2 with value 2.\n");
    evict(cache);
    showCache(cache);

    printf("Evicting key 3 with value 3.\n");
    evict(cache);
    showCache(cache);

    destroyCache(cache);
}

// emptyEvict - Tests the eviction of entries from an empty LRU cache
void emptyEvict() {
    printf("Running eviction of empty cache test.\n");

    LRUCache *cache = createCache(3, 10);
    showCache(cache);

    printf("Evicting key 1 with value 1.\n");
    evict(cache);
    showCache(cache);

    destroyCache(cache);
}