#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100000

int main() {
    int data[N];
    long long histogram[256] = {0};
    
    srand(42);
    for (int i = 0; i < N; i++) {
        data[i] = rand() % 256;
    }
    
    double t0 = omp_get_wtime();
    
    // Version avec atomic - CORRECTE
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int v = data[i];
        #pragma omp atomic
        histogram[v]++;
    }
    
    printf("Time: %.6f s\n", omp_get_wtime() - t0);
    
    long long total = 0;
    for (int v = 0; v < 256; v++) {
        total += histogram[v];
    }
    printf("Total counts: %ld (should be %d)\n", total, N);
    
    return 0;
}