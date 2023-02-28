#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define arr_size 100

int main(int argc, char **argv) {
    double time_start, time_end;
    int iteration_x, iteration_y, iteration_z;
    int **first_matrix, **second_matrix, **third_matrix;

    // Allocate memory for matrices
    first_matrix = (int **)malloc(arr_size * sizeof(int *));
    second_matrix = (int **)malloc(arr_size * sizeof(int *));
    third_matrix = (int **)malloc(arr_size * sizeof(int *));
    for (iteration_x = 0; iteration_x < arr_size; iteration_x++) {
        first_matrix[iteration_x] = (int *)malloc(arr_size * sizeof(int));
        second_matrix[iteration_x] = (int *)malloc(arr_size * sizeof(int));
        third_matrix[iteration_x] = (int *)malloc(arr_size * sizeof(int));
    }

    // Initialize matrices
    for (iteration_x = 0; iteration_x < arr_size; iteration_x++) {
        for (iteration_y = 0; iteration_y < arr_size; iteration_y++) {
            first_matrix[iteration_x][iteration_y] = iteration_x + iteration_y;
            second_matrix[iteration_x][iteration_y] = iteration_x - iteration_y;
            third_matrix[iteration_x][iteration_y] = 0;
        }
    }

    // Parallel matrix multiplication with static scheduling
    time_start = omp_get_wtime();
    #pragma omp parallel for schedule(static) private(iteration_x, iteration_y, iteration_z) shared(first_matrix, second_matrix, third_matrix)
    for (iteration_x = 0; iteration_x < arr_size; iteration_x++) {
        for (iteration_y = 0; iteration_y < arr_size; iteration_y++) {
            for (iteration_z = 0; iteration_z < arr_size; iteration_z++) {
                third_matrix[iteration_x][iteration_y] += first_matrix[iteration_x][iteration_z] * second_matrix[iteration_z][iteration_y];
            }
        }
    }
    time_end = omp_get_wtime();
    printf("Static scheduling execution: %f seconds\n", time_end - time_start);

    // Reset resulting matrix's allocation to zero
    for (iteration_x = 0; iteration_x < arr_size; iteration_x++) {
        for (iteration_y = 0; iteration_y < arr_size; iteration_y++) {
            third_matrix[iteration_x][iteration_y] = 0;
        }
    }

    // Parallel matrix multiplication with dynamic scheduling
    time_start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) private(iteration_x, iteration_y, iteration_z) shared(first_matrix, second_matrix, third_matrix)
    for (iteration_x = 0; iteration_x < arr_size; iteration_x++) {
        for (iteration_y = 0; iteration_y < arr_size; iteration_y++) {
            for (iteration_z = 0; iteration_z < arr_size; iteration_z++) {
                third_matrix[iteration_x][iteration_y] += first_matrix[iteration_x][iteration_z] * second_matrix[iteration_z][iteration_y];
            }
        }
    }
    time_end = omp_get_wtime();
    printf("Dynamic scheduling execution: %f seconds\n", time_end - time_start);

    // Free memory for matrices
    for (iteration_x = 0; iteration_x < arr_size; iteration_x++) {
        free(first_matrix[iteration_x]);
        free(second_matrix[iteration_x]);
        free(third_matrix[iteration_x]);
    }
    free(first_matrix);
    free(second_matrix);
    free(third_matrix);

    return 0;
}


/*
This code first initializes three matrices first_matrix, second_matrix, and c with size arr_size by arr_size.
It then performs matrix multiplication with two different scheduling methods:
static and dynamic. Both parallel sections use the #pragma omp parallel for directive
to distribute the workload across threads. The schedule(static) and schedule(dynamic)
clauses specify the scheduling method for the loop iterations.

After each parallel section, the elapsed time is calculated using the omp_get_wtime()
function and printed to the console. Finally, memory is freed for the matrices.

Note that the number of threads used in the parallel sections depends on the default
number of threads set by the OpenMP environment or the value set by the OMP_NUM_THREADS
environment variable. By default, OpenMP uses the maximum number of available threads 
on the system. If you want to set the number of threads explicitly, you can use the
omp_set_num_threads() function before the parallel section.

Also, keep in mind that the performance of the parallel matrix multiplication
may depend on the hardware architecture, the size of the matrices, and the scheduling
method used. Therefore, it's first_matrix good practice to experiment with different scheduling
methods and matrix sizes to find the optimal configuration for your specific use case.

*/