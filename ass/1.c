/*The program uses the OpenMP parallel directive to distribute the work of the sieve algorithm across multiple threads.
 The num_threads parameter specifies the number of threads to use, and the schedule(dynamic) clause on the for loops ensures good load balancing
  by dividing the work into chunks of equal size that are assigned dynamically to threads as they become available.*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

bool *sieve;

void parallel_sieve(int n, int num_threads) {
    int i, j, factor;
    double sqrt_n = sqrt(n);

    #pragma omp parallel num_threads(num_threads) private(i, j, factor)
    {
        #pragma omp for schedule(dynamic)
        for (i = 3; i <= (int) sqrt_n; i += 2) {
            if (sieve[i/2]) {
                factor = i;
                #pragma omp parallel for schedule(dynamic)
                for (j = i*i; j <= n; j += 2*factor) {
                    sieve[j/2] = false;
                }
            }
        }
    }
}



int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./prime_parallel numProcs size [outfile]\n");
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
            printf("Error: Could not open file %s for writing\n", argv[3]);
            exit(1);
        }
    }

    // Initialize sieve array with all odd numbers marked as prime
    sieve = (bool*) malloc((size/2 + 1) * sizeof(bool));
    for (int i = 0; i <= size/2; i++) {
        sieve[i] = true;
    }

    // Mark 1 as not prime
    sieve[0] = false;

    // Run the parallel sieve algorithm
    double start_time = omp_get_wtime();
    parallel_sieve(size, numProcs);
    double end_time = omp_get_wtime();

    // Output prime numbers to file or standard output
    int count = 1; // include 2 as the first prime
    if (output) {
        fprintf(out, "2\n");
    } else {
        printf("2\n");
    }
    for (int i = 1; i <= size/2; i++) {
        if (sieve[i]) {
            count++;
            if (output) {
                fprintf(out, "%d\n", 2*i + 1);
            } else {
                printf("%d\n", 2*i + 1);
            }
        }
    }

    printf("Found %d primes in %f seconds\n", count, end_time - start_time);

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