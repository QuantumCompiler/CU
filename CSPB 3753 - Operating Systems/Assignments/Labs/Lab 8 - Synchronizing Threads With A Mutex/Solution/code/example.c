///////////////////////////////////////////////////////////////////////////////
// Example code for showing unsafe and safe thread code
//
// Author: Taylor Larrechea
// Date: 10/21/2024
//
// Usage:
//          make - Do everything, dude
//          make api - Creates shared api and tests with default files
//          make example - Creates example and tests with default files
//          make testAPI - Builds and tests
//          make testExample - Builds and tests
//          make clean - Cleans up the directory
///////////////////////////////////////////////////////////////////////////////

/*  example.c - Example code for showing unsafe and safe thread code
        Globals:
            LONG_ITERATION - Number of iterations
            randInt - Random integer initialized to 0
        Functions:
            tf_Unsafe_Printer - Function that uses an un-synchronized thread and prints out the current and previous values of a calculation
            tf_Unsafe_Modifier - Function that uses an un-synchronized thread and modifies the global variable randInt
            tf_Safe_Printer - Function that uses a synchronized thread and prints out the current and previous values of a calculation
            tf_Safe_Modifier - Function that uses a synchronized thread and modifies the global variable randInt
            main - Main function that creates threads based on the input from the command line
        Execution:
            example <test> where <test> is 1-4
        Synopsis:
            This program demonstrates the creation of threads in both a 'safe' and 'unsafe' manner. Respective functions were written
            to demonstrate each of these behaviors. The test cases implement the following tests for each case:
                1 - Unsafe threads (both printer and modifier)
                2 - Safe threads (both printer and modifier)
                3 - Unsafe printer thread, safe modifier thread
                4 - Safe printer thread, unsafe modifier thread
            It is recommended one outputs the results of this program to a file for easier interpretation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

// Create synchronization object (mutex)
pthread_mutex_t mutex; 

// Globals
#define LONG_ITERATION 1000000 // Number of iterations
static volatile int randInt = 0; // Random integer initialized to 0

/*  tf_Unsafe_Printer - Function that uses an un-synchronized thread and prints out the current and previous values of a calculation
        Input:
            arg - Void pointer to the thread id
        Algorithm:
            * Cast the void pointer to an integer
            * Print the function name and the thread id
            * Create a long integer to iterate through the LONG_ITERATION
            * While the previous variable is not 0:
                * Get the random integer from the input in the function call
                * If the random integer is divisible by 5, do nothing
                * If the random integer is not divisible by 5, print the current and previous values
                * If the current value is not equal to the previous value, print the current and previous values
                * Decrement the iterator
            * Return NULL
        Output:
            This function does not return a value other than NULL, it prints the current and previous values of the random integer
            that is divisible by 5 and not divisible by 5 that is being modified by the tf_Unsafe_Modifier function
*/
void* tf_Unsafe_Printer(void* arg) {
    // Cast thread id to int
	int my_id = (long int) arg;
    // Print welcome
	printf("Started [%s] with %d\n",  __FUNCTION__ , my_id);
    long i = LONG_ITERATION;
    // While the iterator is not 0
    while (i != 0) {
        int was = randInt; // Random int from function call
        // Divisible by 5
        if ( (randInt % 5) == 0) {
            // Not divisible by 5
            if ((randInt % 5) != 0) {
                // Update now
                int now = randInt; 
                // Check for equality
                if (now != was)
                    printf("Thread %d: Current: %d, previously: %d\n", my_id, now, was);
            }
        }
        i--; // Decrement iterator
    }
    return NULL; // Return NULL
}

/*  tf_Unsafe_Modifier - Function that uses an un-synchronized thread and modifies the global variable randInt
        Input:
            arg - Void pointer to the thread id
        Algorithm:
            * Cast the void pointer to an integer
            * Print the function name and the thread id
            * Create a long integer to iterate through the LONG_ITERATION
            * While the iterator is not 0:
                * Get the random integer from the input in the function call
                * Decrement the iterator
            * Return NULL
        Output:
            This function does not return a value other than NULL, it modifies the global variable randInt that is to be printed from the
            tf_Unsafe_Printer function
        Relevant Sources:
            * Simple Random Integer Implementation In C: https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
*/
void* tf_Unsafe_Modifier(void* arg) {
	int my_id = (long int) arg; // Cast thread id to int
    // Print welcome
	printf("Started [%s] with %d\n",  __FUNCTION__ , my_id);
    long i = LONG_ITERATION;
    // While the iterator is not 0
    while (i != 0) {
        randInt = rand() % 1000; // Random int from 0 to 999
        i--; // Decrement iterator
    }
    return NULL; // Return NULL
}

/*  tf_Safe_Printer - Function that uses a synchronized thread and prints out the current and previous values of a calculation
        Input:
            arg - Void pointer to the thread id
        Algorithm:
            * Cast the void pointer to an integer
            * Print the function name and the thread id
            * Create a long integer to iterate through the LONG_ITERATION
            * Create variable for previous value (do not want to print same value if not modified)
            * While the iterator is not 0:
                * Lock the mutex
                * Get the random integer from the input in the function call
                * If the random integer is divisible by 5, print the current and previous values
                * Unlock the mutex
                * Decrement the iterator
            * Return NULL
        Output:
            This function does not return a value other than NULL, it prints the current and previous values of the random integer
            that is divisible by 5 and not divisible by 5 that is being modified by the tf_Safe_Modifier function
        Relevant Sources:
            * pthread_mutex_lock: https://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_mutex_lock.html
            * pthread_mutex_unlock: https://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_mutex_unlock.html
*/
void* tf_Safe_Printer(void* arg) {
    // Cast thread id to int
	int my_id = (long int) arg;
     // Print welcome
	printf("Started [%s] with %d\n",  __FUNCTION__ , my_id);
     // Print mutex requirement
    printf("[%s] Needs to have mutex around critical section \n", __FUNCTION__);
    long i = LONG_ITERATION;
    // Previous value
    int was = 0;
    // While the iterator is not 0
    while (i != 0) {
        // Lock mutex
        if (pthread_mutex_lock(&mutex) != 0) {
            printf("Failed to lock mutex\n");
            return NULL;
        }
        // Updated randInt
        int now = randInt;
        // Divisible by 5
        if (now != was && now % 5 == 0) {
            printf("Thread %d: Current: %d, previously: %d\n", my_id, now, was);
            was = now;
        }
        // Unlock mutex
        if (pthread_mutex_unlock(&mutex) != 0) {
            printf("Failed to unlock mutex\n");
            return NULL;
        }
        i--; // Decrement iterator
    }
    return NULL; // Return NULL
}

/*  tf_Safe_Modifier - Function that uses a synchronized thread and modifies the global variable randInt
        Input:
            arg - Void pointer to the thread id
        Algorithm:
            * Cast the void pointer to an integer
            * Print the function name and the thread id
            * Create a long integer to iterate through the LONG_ITERATION
            * While the iterator is not 0:
                * Lock the mutex
                * Get the random integer from the input in the function call
                * Unlock the mutex
                * Decrement the iterator
            * Return NULL
        Output:
            This function does not return a value other than NULL, it modifies the global variable randInt that is to be printed from the
            tf_Safe_Printer functions
        Relevant Sources:
            * pthread_mutex_lock: https://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_mutex_lock.html
            * pthread_mutex_unlock: https://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_mutex_unlock.html
*/
void* tf_Safe_Modifier(void* arg) {
    // Cast thread id to int
	int my_id = (long int) arg;
    // Print welcome
	printf("Started [%s] with %d\n",  __FUNCTION__ , my_id);
    // Print mutex requirement
    printf("[%s] Needs to have mutex around critical section \n", __FUNCTION__);
    long i = LONG_ITERATION;
    // While the iterator is not 0
    while (i != 0) {
        // Lock mutex
        if (pthread_mutex_lock(&mutex) != 0) {
            printf("Failed to lock mutex\n");
            return NULL;
        }
        randInt = rand() % 1000; // Random int from 0 to 999
        // Unlock mutex
        if (pthread_mutex_unlock(&mutex) != 0) {
            printf("Failed to unlock mutex\n");
            return NULL;
        }
        i--; // Decrement iterator
    }
    return NULL; // Return NULL
}

/*  main - Main function that creates threads based on the input from the command line
        Input:
            argc - Number of arguments
            argv - Array of arguments (which scenario should be tested)
        Algorithm:
            * Check for input
            * Switch on the input from the command line
                * Case 1: Unsafe threads
                    * Create thread 1 with tf_Unsafe_Printer
                    * Create thread 2 with tf_Unsafe_Modifier
                * Case 2: Safe threads
                    * Create mutex
                    * Create thread 1 with tf_Safe_Printer
                    * Create thread 2 with tf_Safe_Modifier
                * Case 3: Unsafe printer thread, safe modifier thread
                    * Create mutex
                    * Create thread 1 with tf_Unsafe_Printer
                    * Create thread 2 with tf_Safe_Modifier
                * Case 4: Safe printer thread, unsafe modifier thread
                    * Create mutex
                    * Create thread 1 with tf_Safe_Printer
                    * Create thread 2 with tf_Unsafe_Modifier
                * Default: Unknown test
            * Wait for threads to terminate, release resources after
                * Join thread 1
                * Join thread 2
                * Destroy mutex
        Output:
            This function does not return a value other than 0, it creates threads based on the input from the command line
        Relevant Sources:
            * pthread_create: https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_create.html
            * pthread_join: https://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_join.html
            * pthread_mutex_init: https://pubs.opengroup.org/onlinepubs/007904875/functions/pthread_mutex_init.html
            * pthread_mutex_destroy: https://pubs.opengroup.org/onlinepubs/007904875/functions/pthread_mutex_destroy.html
            * pthread example: https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
*/
int main(int argc, char **argv) {
    // Create threads
    pthread_t thread1, thread2;
    // Check for input
    if (argc <= 1) {
        printf("Must specify test 1-4 as parameter for test to run.\n");
        return -1;
    }
    // Switch for inputs on program execution
    switch (argv[1][0]) {
        case '1':   // unsafe threads
                    // Create thread 1
                    if (pthread_create(&thread1, NULL, tf_Unsafe_Printer, (void*)1) != 0) {
                        printf("Failed to create Thread 1 with tf_Unsafe_Printer\n");
                    } else {
                        printf("Thread 1 with tf_Unsafe_Printer created successfully\n");
                    }
                    // Create thread 2
                    if (pthread_create(&thread2, NULL, tf_Unsafe_Modifier, (void*)2) != 0) {
                        printf("Failed to create Thread 2 with tf_Unsafe_Modifier\n");
                    } else {
                        printf("Thread 2 with tf_Unsafe_Modifier created successfully.\n");
                    }
                    break;
        case '2':   // safe threads
                    // Create mutex
                    if (pthread_mutex_init(&mutex, NULL) != 0) {
                        printf("Failed to create mutex\n");
                    } else {
                        printf("Mutex created\n");
                    }
                    // Create thread 1
                    if (pthread_create(&thread1, NULL, tf_Safe_Printer, (void*)1) != 0) {
                        printf("Failed to create Thread 1 with tf_Safe_Printer\n");
                    } else {
                        printf("Thread 1 with tf_Safe_Printer created successfully.\n");
                    }
                    // Create thread 2
                    if (pthread_create(&thread2, NULL, tf_Safe_Modifier, (void*)2) != 0) {
                        printf("Failed to create Thread 2 with tf_Safe_Modifier\n");
                    } else {
                        printf("Thread 2 with tf_Safe_Modifier created successfully .\n");
                    }
                    break;
        case '3':   // unsafe printer thread, safe modifier thread
                    // Create mutex 
                    if (pthread_mutex_init(&mutex, NULL) != 0) {
                        printf("Failed to create mutex\n");
                    } else {
                        printf("Mutex created\n");
                    }
                    // Create thread 1
                    if (pthread_create(&thread1, NULL, tf_Unsafe_Printer, (void*)1) != 0) {
                        printf("Failed to create Thread 1 with tf_Unsafe_Printer\n");
                    } else {
                        printf("Thread 1 with tf_Unsafe_Printer created successfully.\n");
                    }
                    // Create thread 2
                    if (pthread_create(&thread2, NULL, tf_Safe_Modifier, (void*)2) != 0) {
                        printf("Failed to create Thread 2 with tf_Safe_Modifier\n");
                    } else {
                        printf("Thread 2 with tf_Safe_Modifier created successfully.\n");
                    }
                    break;
        case '4':   // safe printer thread, unsafe modifier thread
                    // Create mutex
                    if (pthread_mutex_init(&mutex, NULL) != 0) {
                        printf("Failed to create mutex\n");
                    } else {
                        printf("Mutex created\n");
                    }
                    // Create Thread 1
                    if (pthread_create(&thread1, NULL, tf_Safe_Printer, (void*)1) != 0) {
                        printf("Failed to create Thread 1 with tf_Safe_Printer\n");
                    } else {
                        printf("Thread 1 with tf_Safe_Printer created successfully.\n");
                    }
                    // Create Thread 2
                    if (pthread_create(&thread2, NULL, tf_Unsafe_Modifier, (void*)2) != 0) {
                        printf("Failed to create Thread 2 with tf_Unsafe_Modifier\n");
                    } else {
                        printf("Thread 2 with tf_Unsafe_Modifier created successfully.\n");
                    }
                    break;
        default:
                    printf("Unknown test [%c]\n", argv[1][0]);
                    break;
    }
    // Wait for threads to terminate, release resources after
    // Join thread 1
    if (pthread_join(thread1, NULL) != 0) {
        printf("Thread 1 failed to join.\n");
    } else {
        printf("Thread 1 joined successfully.\n");
    }
    // Join thread 2
    if (pthread_join(thread2, NULL) != 0) {
        printf("Thread 2 failed to join.\n");
    } else {
        printf("Thread 2 joined successfully.\n");
    }
    // Destroy mutex
    if (argv[1][0] == '2' || argv[1][0] == '3' || argv[1][0] == '4') {
        // Destroy mutex
        if (pthread_mutex_destroy(&mutex) != 0) {
            printf("Failed to destroy mutex.\n");
        } else {
            printf("Mutex destroyed successfully.\n");
        }
    }
    return 0;
}
