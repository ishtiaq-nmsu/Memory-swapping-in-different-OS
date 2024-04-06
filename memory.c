/*
Assignment 2: Observing the difference between memory access and experience swapping
Submitted by: Md Ishtiaq Ahmed
Objective: Run a program to observe the effects of extensive physical memory consumption and swapping during program execution time. 
A C program is designed which incrementally consumes all available physical memory and eventually forces the system to utilize swap space. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

//#define SIZE 26214400  // size of each array (100*1024*1024) , when filled with integer of size 4 byte total consumption will be 100 MB
#define SIZE 131072000  // size of each array (100*1024*1024) , when filled with integer of size 4 byte total consumption will be 500 MB



int *A[1000]; // Max Number of array

// Pre Condition: Define a size which will be used for memory allocation of each array, also define the array
// Post COndition: Program will run until it consumes all of the available memory

int main() {

    long long memoryAllocated = 0; // To keep track of the total allocated memory
    int index = 0; // initial index of array set as 0
    
    clock_t start, end;  // To calculate execution time
    double cpu_time_used;  // Variable to store execution time

    
    while (1) {  
        
        A[index] = malloc(SIZE * sizeof(int));  // memory allocation for each array, each array will have a size of 26214400 and filled by integer of 4 byte, total 100 MB 
        if (A[index] == NULL) { // If out of memory, program will be exited
            printf("Program Exited, Memory allocation failed at index %d\n", index);
            break; // Exit if we can't allocate more memory
        }

        // Fill previous arrays with 1
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < SIZE; j++) {
                A[i][j] = 1;
            }
        }
        memoryAllocated += (SIZE * sizeof(int))/(1024*1024); // total memory allocated after each iteration
        printf("Total Used Memory: %lld MB\n", memoryAllocated);

        // Measure time to fill the latest array
        start = clock(); // Start time
        for (int j = 0; j < SIZE; j++) {  // Fill up the last array
            A[index][j] = 1;
        } // end for
        end = clock();  // End time

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        printf("Index %d, Time: %f seconds\n", index, cpu_time_used);
        

        index++;
            
        // Sleep for 1 second to observe the behavior
        //sleep(1);
    } // end while

    // Free allocated memory
    for (int i = 0; i < index; i++) {
        free(A[i]);
    } // end for

    return 0;
} // end main
