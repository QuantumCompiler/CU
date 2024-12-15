/*
    test.c - A test file for the LRU cache implementation

    Author: Taylor Larrechea
    Date: 11/20/24
    Class: CSPB 3753
    Professor: Dr. David Knox


*/
#include "insertTest.h"
#include "retrieveTest.h"
#include "evictTest.h"

int main() {

    // Insert tests

    printf("\nRunning insertion tests...\n");

    singleInsert();
    duplicateInsert();
    multiInsert();
    evictInsert();

    // Retrieve tests

    printf("\nRunning retrieval tests...\n");

    singleRetrieve();
    multiRetrieve();
    evictRetrieve();

    // Evict tests

    printf("\nRunning eviction tests...\n");

    singleEvict();
    multiEvict();
    emptyEvict();

    return 0;
}