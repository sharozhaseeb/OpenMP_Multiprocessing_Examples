#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10

int main(int argc, char **argv) {
    double start_time, end_time;
    int i, j, k;
    int **a, **b, **c;

    // Allocate memory for matrices
    a = (int **)malloc(N * sizeof(int *));
    b = (int **)malloc(N * sizeof(int *));
    c = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        a[i] = (int *)malloc(N * sizeof(int));
        b[i] = (int *)malloc(N * sizeof(int));
        c[i] = (int *)malloc(N * sizeof(int));
    }

    // Initialize matrices
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
            c[i][j] = 0;
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
        for (k = 0; k < N; k++) {
            c[row][col] += a[row][k] * b[k][col];
        }
    }
    end_time = omp_get_wtime();
    printf("Default scheduling execution time: %f seconds\n", end_time - start_time);

    // Reset result matrix to zero
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = 0;
        }
    }

    // Parallel matrix multiplication with static scheduling
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(static) private(i, j, k) shared(a, b, c)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    end_time = omp_get_wtime();
    printf("Static scheduling execution time: %f seconds\n", end_time - start_time);

    // Reset result matrix to zero
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = 0;
        }
    }

    // Parallel matrix multiplication with dynamic scheduling
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) private(i, j, k) shared(a, b, c)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    end_time = omp_get_wtime();
    printf("Dynamic scheduling execution time:%f seconds\n", end_time - start_time);

    // Free memory for matrices
for (i = 0; i < N; i++) {
    free(a[i]);
    free(b[i]);
    free(c[i]);
}
free(a);
free(b);
free(c);

return 0;
}



/*
For large values of N you will get Segmentation fault (core dumped)
*/

/*
This code performs matrix multiplication of two N x N matrices using OpenMP for parallelism. The matrix multiplication is performed in three different ways: with default scheduling, static scheduling, and dynamic scheduling.

First, memory is allocated for the matrices using dynamic memory allocation. Then, the matrices are initialized with random values.

Next, the number of threads is set to be equal to the number of elements in the output matrix (N x N). This is done to create a fine-grained parallelization, where each thread is assigned to compute one element of the output matrix.

The matrix multiplication is then performed using OpenMP parallelization with default scheduling. Each thread computes a row and a column of the output matrix using the tid, row and column variables.

The result matrix is reset to zero, and the matrix multiplication is performed again with static scheduling, where each thread is assigned a set of rows to compute. Finally, the matrix multiplication is performed with dynamic scheduling, where each thread is assigned a set of rows to compute dynamically at runtime.

The execution times for each matrix multiplication method are printed to the console. Finally, memory for the matrices is deallocated before the program exits.
*/