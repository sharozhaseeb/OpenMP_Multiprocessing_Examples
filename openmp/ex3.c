// Specifying the number of threads to use:

#include <stdio.h>
#include <omp.h>

int main() {
    int n_threads = 4;
    omp_set_num_threads(n_threads);
    #pragma omp parallel
    {
        printf("Hello from thread %d\n", omp_get_thread_num());
    }
    return 0;
}
