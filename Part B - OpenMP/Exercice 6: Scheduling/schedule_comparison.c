#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000000

int main() {
    int *arr = malloc(N * sizeof(int));
    long long sum = 0;
    
    // Initialisation avec valeurs aléatoires
    srand(42);
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 1000;
    }
    
    // static schedule
    double t0 = omp_get_wtime();
    sum = 0;
    #pragma omp parallel for schedule(static) reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }
    double t_static = omp_get_wtime() - t0;
    
    // dynamic schedule
    t0 = omp_get_wtime();
    sum = 0;
    #pragma omp parallel for schedule(dynamic) reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }
    double t_dynamic = omp_get_wtime() - t0;
    
    // guided schedule
    t0 = omp_get_wtime();
    sum = 0;
    #pragma omp parallel for schedule(guided) reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }
    double t_guided = omp_get_wtime() - t0;
    
    printf("static:  %.6f s\n", t_static);
    printf("dynamic: %.6f s\n", t_dynamic);
    printf("guided:  %.6f s\n", t_guided);
    
    free(arr);
    return 0;
}