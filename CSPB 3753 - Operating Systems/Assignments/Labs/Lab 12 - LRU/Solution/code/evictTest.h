/*
    evictTest.h - Header file for evictTest.c functions

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Prototypes:
        singleEvict - Tests the eviction of a single entry from the LRU cache
        multiEvict - Tests the eviction of multiple entries from the LRU cache
        emptyEvict - Tests the eviction of entries from an empty LRU cache
*/
#ifndef EVICT_TEST_H
#define EVICT_TEST_H

#include "util.h"

void singleEvict();
void multiEvict();
void emptyEvict();

#endif // EVICT_TEST_H