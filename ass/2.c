#include <stdio.h>
#include <omp.h>

#define SIZE 1000

int main() {
    int key=111;
    long win = 0;

    double start_time, end_time;
    
    // Sequential execution
    start_time = omp_get_wtime();
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            for (int k=0; k < SIZE; k++) {
                int x= (i*i*1000/35) % 1000;
                int y= (j*j*1000/36) % 1000;
                int z= (k*k*1000/37) % 1000;
                if (key == (x+y+z)) {
                    win += 1;
                }
            }
        }
    }
    end_time = omp_get_wtime();

    printf("Sequential execution time: %lf\n", end_time - start_time);
    printf("total wins=%ld\n",win);

    // Parallel execution with 2 threads
    win = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for collapse(3) shared(key) reduction(+: win) num_threads(2)
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            for (int k=0; k < SIZE; k++) {
                int x= (i*i*1000/35) % 1000;
                int y= (j*j*1000/36) % 1000;
                int z= (k*k*1000/37) % 1000;
                if (key == (x+y+z)){
                    win += 1;
                }
            }
        }
    }
    end_time = omp_get_wtime();

    printf("Parallel execution with 2 threads: %lf\n", end_time - start_time);
    printf("total wins=%ld\n",win);

    // Parallel execution with 3 threads
    win = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for collapse(3) shared(key) reduction(+: win) num_threads(3)
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            for (int k=0; k < SIZE; k++) {
                int x= (i*i*1000/35) % 1000;
                int y= (j*j*1000/36) % 1000;
                int z= (k*k*1000/37) % 1000;
                if (key == (x+y+z)) {
                    win += 1;
                }
            }
        }
    }
    end_time = omp_get_wtime();

    printf("Parallel execution with 3 threads: %lf\n", end_time - start_time);
    printf("total wins=%ld\n",win);

    // Parallel execution with 4 threads
    win = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for collapse(3) shared(key) reduction(+: win) num_threads(4)
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            for (int k=0; k < SIZE; k++) {
                int x= (i*i*1000/35) % 1000;
                int y= (j*j*1000/36) % 1000;
                int z= (k*k*1000/37) % 1000;
                if (key == (x+y+z)) {
                    win += 1;
                }
            }
        }
    }
    end_time = omp_get_wtime();

    printf("Parallel execution with 4 threads: %lf\n", end_time - start_time);
    printf("total wins=%ld\n",win);

    return 0;
}

/*The program will output the sequential execution time and the parallel execution time with 2, 3, and 4 threads, as well as the total number of wins.
We can calculate the speedup by dividing the sequential execution time by the parallel execution time for each case.*/

// Compile the code with OpenMP flags
//gcc -fopenmp openmp_code.c -o openmp_code

// Run the code
//./openmp_code


//sample output
/*
Sequential execution time: 8.186740
total wins=90132
Parallel execution with 2 threads: 4.216384
total wins=90132
Parallel execution with 3 threads: 2.807638
total wins=90132
Parallel execution with 4 threads: 2.228275
total wins=90132


*/