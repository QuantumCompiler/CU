/*
    insertTest.h - Header file for insertTest.c functions

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Prototypes:
        singleInsert - Tests the insertion of a single key-value pair into the LRU cache
        duplicateInsert - Tests the insertion of a duplicate key into the LRU cache
        multiInsert - Tests the insertion of multiple key-value pairs into the LRU cache
        evictInsert - Tests the eviction of the least recently used entry when inserting into a full LRU cache
*/
#ifndef INSERT_TEST_H
#define INSERT_TEST_H

#include "util.h"

void singleInsert();
void duplicateInsert();
void multiInsert();
void evictInsert();

#endif // INSERT_TEST_H