#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    int arr_size = 1000000; // array size
    int key = 42; // search key
    int *arr = malloc(arr_size * sizeof(int)); // allocate memory for array

    // initialize array with random values
    #pragma omp parallel for
    for (int iteration = 0; iteration < arr_size; iteration++) {
        arr[iteration] = rand() % 100;
    }

    int counter = 0; // initialize counter
    #pragma omp parallel for reduction(+:counter)
    for (int iteration = 0; iteration < arr_size; iteration++) {
        if (arr[iteration] == key) {
            counter++;
        }
    }

    printf("key: %d occurs %d times in the array of size: %d\n", key, counter, arr_size);

    free(arr); // free memory

    return 0;
}


/*
The #pragma omp parallel for directive is used to parallelize the loop that initializes
the array with random values. Each thread is assigned a portion of the array to initialize.

The #pragma omp parallel for reduction(+:counter) directive is used to parallelize the loop
that searches for the key in the array. The reduction(+:counter) clause ensures that each thread
maintains a local counter of the number of times the key is found in its portion of the array,
and that these local counts are summed up into the variable counter at the end of the loop.

Note that the rand() function used to generate random values for the array is not thread-safe.
To make the program thread-safe, you can use the rand_r() function instead, which takes a seed
value as an argument and returns a thread-safe pseudo-random number generator.

*/

/*
gcc -fopenmp 3.c -o 3
./3

-$ output
Number of times the key 42 occurs in the array: 9972
*/