#include <stdio.h>
#include <omp.h>
#define N 100000

int main() {
    double A[N], B[N], C[N];
    
    // Initialisation
    for (int i = 0; i < N; i++) {
        A[i] = i;
        B[i] = 2 * i;
    }
    
    // Version séquentielle
    double t0 = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }
    double t_serial = omp_get_wtime() - t0;
    
    // Version parallèle
    t0 = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }
    double t_par = omp_get_wtime() - t0;
    
    printf("Serial: %.6f s | Parallel: %.6f s | Speedup: %.2fx\n", 
           t_serial, t_par, t_serial / t_par);
    
    return 0;
}