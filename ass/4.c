#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100

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
    printf("Dynamic scheduling execution time: %f seconds\n", end_time - start_time);

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
This code first initializes three matrices a, b, and c with size N by N.
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
  method used. Therefore, it's a good practice to experiment with different scheduling
   methods and matrix sizes to find the optimal configuration for your specific use case.

*/