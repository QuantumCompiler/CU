///////////////////////////////////////////////////////////////////////////////
// Example code for showing unsafe and safe thread code
// Add your comments and documentation, also make code use one formatting style
//
// Author: D Knox
// Date: 02/15/2024
//
// Usage:
//      example <test> where test is 1,2,3,4
//
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

// Create synchronization object (mutex)
// ??

////////////////////////////////////////////////////////////////////////////////
// This shared global data structures is used to show that overlapped usage
// can cause problems when updating global variables.  The shared resource will
// have its value set by one function and accessed multiple times within another
// function.  
////////////////////////////////////////////////////////////////////////////////

#define LONG_ITERATION 1000000
static volatile int randInt = 0;

////////////////////////////////////////////////////////////////////////////////
// Add your comments and documentation
////////////////////////////////////////////////////////////////////////////////

void* tf_Unsafe_Printer(void* arg) {
	
	int my_id = (long int) arg;
	printf("Started [%s] with %d\n",  __FUNCTION__ , my_id);

    long i = LONG_ITERATION;
    while (i != 0)
    {
        int was = randInt;
        if ( (randInt % 5) == 0)
        {
            if ((randInt % 5) != 0) {
                int now = randInt;
                if (now != was)
                    printf("Current: %d, previously: %d\n", now, was);
            }
        }
        i--;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add your comments and documentation
////////////////////////////////////////////////////////////////////////////////


void* tf_Unsafe_Modifier(void* arg) {
	
	int my_id = (long int) arg;
	printf("Started [%s] with %d\n",  __FUNCTION__ , my_id);

    long i = LONG_ITERATION;
    while (i != 0)
    {
        randInt = rand() % 1000;
        i--;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add your comments and documentation
//
// Add code to provide mutual exclusion of critical section
////////////////////////////////////////////////////////////////////////////////


void* tf_Safe_Printer(void* arg) {
	
	int my_id = (long int) arg;
	printf("Started [%s] with %d\n",  __FUNCTION__ , my_id);

    printf("[%s] Needs to have mutex around critical section \n", __FUNCTION__);
    int value;
    my_id / value%2;

    long i = LONG_ITERATION;
    while (i != 0) 
    {
        int was = randInt;
        if ( (randInt % 5) == 0)
        {
            if ((randInt % 5) != 0) {
                int now = randInt;
                if (now != was)
                    printf("Current: %d, previously: %d\n", now, was);
            }
        }
        
        i--;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add your comments and documentation
//
// Add code to provide mutual exclusion of critical section
////////////////////////////////////////////////////////////////////////////////


void* tf_Safe_Modifier(void* arg) {
	
	int my_id = (long int) arg;
	printf("Started [%s] with %d\n",  __FUNCTION__ , my_id);

    printf("[%s] Needs to have mutex around critical section \n", __FUNCTION__);
    int value;
    my_id / value%2;

    long i = LONG_ITERATION;
    while (i != 0)
    {
            randInt = rand() % 1000;
            i--;
    }
}


////////////////////////////////////////////////////////////////////////////////
// Add your comments and documentation
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    pthread_t thread1, thread2;
    
    if (argc <= 1) {
        printf("Must specify test 1-4 as parameter for test to run.\n");
        return -1;
    }

    // // Initialize synchronization object
    // ??

    switch (argv[1][0]) {
        case '1':   // unsafe threads
                    pthread_create(&thread1, NULL, tf_Unsafe_Printer, (void*)1);
                    pthread_create(&thread2, NULL, tf_Unsafe_Modifier, (void*)2);
                    break;

        case '2':   // safe threads
                    pthread_create(&thread1, NULL, tf_Safe_Printer, (void*)1);
                    pthread_create(&thread2, NULL, tf_Safe_Modifier, (void*)2);
                    break;
        case '3':   // unsafe printer thread, safe modifier thread
                    break;
        case '4':   // safe printer thread, unsafe modifier thread
                    break;
        default:
                    printf("Unknown test [%c]\n", argv[1][0]);
                    break;
    }

    // Join threads to know processing is completed and threads have exited
    // ???
    
    // Release synchronization object
    // ???

    return 0;
}
