/*
    retrieveTest.h - Header file for retrieveTest.c functions

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox

    Prototypes:
        singleRetrieve - Tests the retrieval of a single key from the LRU cache
        multiRetrieve - Tests the retrieval of multiple keys from the LRU cache
        evictRetrieve - Tests the retrieval of keys from an LRU cache that has had entries evicted
*/
#ifndef RETRIEVE_TEST_H
#define RETRIEVE_TEST_H

#include "util.h"

void singleRetrieve();
void multiRetrieve();
void evictRetrieve();

#endif // RETRIEVE_TEST_H