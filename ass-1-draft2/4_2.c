#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 2

int main(int argc, char **argv) {
    double start_time, end_time;
    int iteration_x, iteration_y, iteration_z;
    int **first_matrix, **second_matrix, **third_matrix;

    // Allocate memory for matrices
    first_matrix = (int **)malloc(N * sizeof(int *));
    second_matrix = (int **)malloc(N * sizeof(int *));
    third_matrix = (int **)malloc(N * sizeof(int *));
    for (iteration_x = 0; iteration_x < N; iteration_x++) {
        first_matrix[iteration_x] = (int *)malloc(N * sizeof(int));
        second_matrix[iteration_x] = (int *)malloc(N * sizeof(int));
        third_matrix[iteration_x] = (int *)malloc(N * sizeof(int));
    }

    // Initialize matrices
    for (iteration_x = 0; iteration_x < N; iteration_x++) {
        for (iteration_y = 0; iteration_y < N; iteration_y++) {
            first_matrix[iteration_x][iteration_y] = iteration_x + iteration_y;
            second_matrix[iteration_x][iteration_y] = iteration_x - iteration_y;
            third_matrix[iteration_x][iteration_y] = 0;
        }
    }

    // Set number of threads equal to number of elements in the output matrix
    int num_threads = N * N;
    omp_set_num_threads(num_threads);

    // Parallel matrix multiplication with default scheduling
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int row = tid / N;
        int col = tid % N;
        for (iteration_z = 0; iteration_z < N; iteration_z++) {
            third_matrix[row][col] += first_matrix[row][iteration_z] * second_matrix[iteration_z][col];
        }
    }
    end_time = omp_get_wtime();
    printf("Default scheduling execution time: %f seconds\n", end_time - start_time);

    // Reset result matrix to zero
    for (iteration_x = 0; iteration_x < N; iteration_x++) {
        for (iteration_y = 0; iteration_y < N; iteration_y++) {
            third_matrix[iteration_x][iteration_y] = 0;
        }
    }

    // Parallel matrix multiplication with static scheduling
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(static) private(iteration_x, iteration_y, iteration_z) shared(first_matrix, second_matrix, third_matrix)
    for (iteration_x = 0; iteration_x < N; iteration_x++) {
        for (iteration_y = 0; iteration_y < N; iteration_y++) {
            for (iteration_z = 0; iteration_z < N; iteration_z++) {
                third_matrix[iteration_x][iteration_y] += first_matrix[iteration_x][iteration_z] * second_matrix[iteration_z][iteration_y];
            }
        }
    }
    end_time = omp_get_wtime();
    printf("Static scheduling execution time: %f seconds\n", end_time - start_time);

    // Reset result matrix to zero
    for (iteration_x = 0; iteration_x < N; iteration_x++) {
        for (iteration_y = 0; iteration_y < N; iteration_y++) {
            third_matrix[iteration_x][iteration_y] = 0;
        }
    }

    // Parallel matrix multiplication with dynamic scheduling
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) private(iteration_x, iteration_y, iteration_z) shared(first_matrix, second_matrix, third_matrix)
    for (iteration_x = 0; iteration_x < N; iteration_x++) {
        for (iteration_y = 0; iteration_y < N; iteration_y++) {
            for (iteration_z = 0; iteration_z < N; iteration_z++) {
                third_matrix[iteration_x][iteration_y] += first_matrix[iteration_x][iteration_z] * second_matrix[iteration_z][iteration_y];
            }
        }
    }
    end_time = omp_get_wtime();
    printf("Dynamic scheduling execution time:%f seconds\n", end_time - start_time);

    // Free memory for matrices
for (iteration_x = 0; iteration_x < N; iteration_x++) {
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
For large values of N you will get Segmentation fault (core dumped)
*/

/*
This code performs matrix multiplication of two N x N matrices using OpenMP for
parallelism. The matrix multiplication is performed in three different ways: with
default scheduling, static scheduling, and dynamic scheduling.

First, memory is allocated for the matrices using dynamic memory allocation.
Then, the matrices are initialized with random values.
Next, the number of threads is set to be equal to the number of elements in the
output matrix (N x N). This is done to create first_matrix fine-grained parallelization,
where each thread is assigned to compute one element of the output matrix.

The matrix multiplication is then performed using OpenMP parallelization with
default scheduling. Each thread computes first_matrix row and first_matrix column of the output matrix using the tid, row and column variables.

The result matrix is reset to zero, and the matrix multiplication is performed
again with static scheduling, where each thread is assigned first_matrix set of rows to
compute. Finally, the matrix multiplication is performed with dynamic scheduling,
where each thread is assigned first_matrix set of rows to compute dynamically at runtime.

The execution times for each matrix multiplication method are printed to the console
. Finally, memory for the matrices is deallocated before the program exits.
*/