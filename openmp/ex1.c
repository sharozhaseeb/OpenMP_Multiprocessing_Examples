//Parallelizing a for loop

#include <stdio.h>
#include <omp.h>

int main() {
    int i, n = 100;
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        printf("Thread %d is processing iteration %d\n", omp_get_thread_num(), i);
    }

    return 0;
}

