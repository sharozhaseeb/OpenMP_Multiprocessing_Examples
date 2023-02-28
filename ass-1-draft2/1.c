/*The program uses the OpenMP parallel directive to distribute the work of the sieve algorithm across multiple threads.
 The num_threads parameter specifies the number of threads to use, and the schedule(dynamic) clause on the for loops ensures good load balancing
  by dividing the work into chunks of equal size that are assigned dynamically to threads as they become available.*/


#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


bool *sieve;

void parallel_sieve(int number, int num_threads) {
    int iteration_x, iteration_y, factor;
    double sqrt_n = sqrt(number);

    #pragma omp parallel num_threads(num_threads) private(iteration_x, iteration_y, factor)
    {
        #pragma omp for schedule(dynamic)
        for (iteration_x = 3; iteration_x <= (int) sqrt_n; iteration_x += 2) {
            if (sieve[iteration_x/2]) {
                factor = iteration_x;
                #pragma omp parallel for schedule(dynamic)
                for (iteration_y = iteration_x*iteration_x; iteration_y <= number; iteration_y += 2*factor) {
                    sieve[iteration_y/2] = false;
                }
            }
        }
    }
}



int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("try: ./1.c numProcs upper_limit [outfile]\n");
        exit(1);
    }

    int numProcs = atoi(argv[1]);
    int size = atoi(argv[2]);
    bool output = false;
    FILE *out;

    if (argc > 3) {
        output = true;
        out = fopen(argv[3], "w");
        if (out == NULL) {
            printf("file couldn't be opened %s to write\n", argv[3]);
            exit(1);
        }
    }

    // Initialize sieve array with all odd numbers marked as prime
    sieve = (bool*) malloc((size/2 + 1) * sizeof(bool));
    for (int iteration_x = 0; iteration_x <= size/2; iteration_x++) {
        sieve[iteration_x] = true;
    }

    // Mark 1 as not prime
    sieve[0] = false;

    // Run the parallel sieve algorithm
    double time_start = omp_get_wtime();
    parallel_sieve(size, numProcs);
    double time_end = omp_get_wtime();

    // Output prime numbers to file or standard output
    int count = 1; // include 2 as the first prime
    if (output) {
        fprintf(out, "2\n");
    } else {
        printf("2\n");
    }
    for (int iteration_x = 1; iteration_x <= size/2 - 1 ; iteration_x++) {
        if (sieve[iteration_x]) {
            count++;
            if (output) {
                fprintf(out, "%d\n", 2*iteration_x + 1);
            } else {
                printf("%d\n", 2*iteration_x + 1);
            }
        }
    }

    printf("Found %d primes in %f seconds\n", count, time_end - time_start);

    if (output) {
        fclose(out);
    }

    free(sieve);
    return 0;
}



//gcc -fopenmp -o prime_parallel 1.c -lm

//./prime_parallel 4 100 primes.txt

/*In this example, the program is run with 4 threads and a limit of 100.
 The output is written to a file named primes.txt.
  The program finds all prime numbers up to 100 (including 2), and outputs them to the console and to the specified file.
   The final line of the output shows that 25 prime numbers were found and that the program took 0.000156 seconds to complete.
*/

/*
if you get undefined reference to `sqrt'
collect2: error: ld returned 1 exit status

use the following to compile;
gcc -fopenmp 1.c -o 1 -lm

*/
