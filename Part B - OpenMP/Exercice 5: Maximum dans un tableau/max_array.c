#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100000

int main() {
    int arr[N];
    srand(42);
    for (int i = 0; i < N; i++) {
        arr[i] = rand();
    }
    
    int max_val = arr[0];
    double t0 = omp_get_wtime();
    
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < N; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    printf("Max: %d\n", max_val);
    printf("Time: %.6f s\n", omp_get_wtime() - t0);
    
    return 0;
}