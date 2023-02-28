#include <omp.h>
#include <stdlib.h>
#include <stdio.h>


#define UPPER_BOUND 1000

int main() {
    int key=111;
    long win = 0;

    double time_start, time_end;
    
    // Sequential execution
    time_start = omp_get_wtime();
    for (int iteration=0; iteration < UPPER_BOUND; iteration++) {
        for (int iteration_y=0; iteration_y < UPPER_BOUND; iteration_y++) {
            for (int iteration_z=0; iteration_z < UPPER_BOUND; iteration_z++) {
                int x= (iteration*iteration*1000/35) % 1000;
                int y= (iteration_y*iteration_y*1000/36) % 1000;
                int z= (iteration_z*iteration_z*1000/37) % 1000;
                if (key == (x+y+z)) {
                    win += 1;
                }
            }
        }
    }
    time_end = omp_get_wtime();

    printf("Sequential execution time: %lf\n", time_end - time_start);
    printf("total wins=%ld\n",win);

    // Parallel execution with 2 threads
    win = 0;
    time_start = omp_get_wtime();
    #pragma omp parallel for collapse(3) shared(key) reduction(+: win) num_threads(2)
    for (int iteration=0; iteration < UPPER_BOUND; iteration++) {
        for (int iteration_y=0; iteration_y < UPPER_BOUND; iteration_y++) {
            for (int iteration_z=0; iteration_z < UPPER_BOUND; iteration_z++) {
                int x= (iteration*iteration*1000/35) % 1000;
                int y= (iteration_y*iteration_y*1000/36) % 1000;
                int z= (iteration_z*iteration_z*1000/37) % 1000;
                if (key == (x+y+z)){
                    win += 1;
                }
            }
        }
    }
    time_end = omp_get_wtime();

    printf("Parallel execution with 2 threads: %lf\n", time_end - time_start);
    printf("total wins=%ld\n",win);

    // Parallel execution with 3 threads
    win = 0;
    time_start = omp_get_wtime();
    #pragma omp parallel for collapse(3) shared(key) reduction(+: win) num_threads(3)
    for (int iteration=0; iteration < UPPER_BOUND; iteration++) {
        for (int iteration_y=0; iteration_y < UPPER_BOUND; iteration_y++) {
            for (int iteration_z=0; iteration_z < UPPER_BOUND; iteration_z++) {
                int x= (iteration*iteration*1000/35) % 1000;
                int y= (iteration_y*iteration_y*1000/36) % 1000;
                int z= (iteration_z*iteration_z*1000/37) % 1000;
                if (key == (x+y+z)) {
                    win += 1;
                }
            }
        }
    }
    time_end = omp_get_wtime();

    printf("Parallel execution with 3 threads: %lf\n", time_end - time_start);
    printf("total wins=%ld\n",win);

    // Parallel execution with 4 threads
    win = 0;
    time_start = omp_get_wtime();
    #pragma omp parallel for collapse(3) shared(key) reduction(+: win) num_threads(4)
    for (int iteration=0; iteration < UPPER_BOUND; iteration++) {
        for (int iteration_y=0; iteration_y < UPPER_BOUND; iteration_y++) {
            for (int iteration_z=0; iteration_z < UPPER_BOUND; iteration_z++) {
                int x= (iteration*iteration*1000/35) % 1000;
                int y= (iteration_y*iteration_y*1000/36) % 1000;
                int z= (iteration_z*iteration_z*1000/37) % 1000;
                if (key == (x+y+z)) {
                    win += 1;
                }
            }
        }
    }
    time_end = omp_get_wtime();

    printf("Parallel execution with 4 threads: %lf\n", time_end - time_start);
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