#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int N = 1000000; // array size
    int key = 42; // search key
    int *arr = malloc(N * sizeof(int)); // allocate memory for array

    // initialize array with random values
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    int count = 0; // initialize count
    #pragma omp parallel for reduction(+:count)
    for (int i = 0; i < N; i++) {
        if (arr[i] == key) {
            count++;
        }
    }

    printf("Number of times the key %d occurs in the array: %d\n", key, count);

    free(arr); // free memory

    return 0;
}


/*
The #pragma omp parallel for directive is used to parallelize the loop that initializes the array with random values. Each thread is assigned a portion of the array to initialize.

The #pragma omp parallel for reduction(+:count) directive is used to parallelize the loop that searches for the key in the array. The reduction(+:count) clause ensures that each thread maintains a local count of the number of times the key is found in its portion of the array, and that these local counts are summed up into the variable count at the end of the loop.

Note that the rand() function used to generate random values for the array is not thread-safe. To make the program thread-safe, you can use the rand_r() function instead, which takes a seed value as an argument and returns a thread-safe pseudo-random number generator.

*/

/*
gcc -fopenmp 3.c -o 3
./3

-$ output
Number of times the key 42 occurs in the array: 9972
*/