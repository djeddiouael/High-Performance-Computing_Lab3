#include <stdio.h>
#include <omp.h>
#define N 10000000

int main() {
    double sum = 0.0;
    double step = 1.0 / N;
    
    // Version avec reduction (recommandée)
    double t0 = omp_get_wtime();
    sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    double pi = sum * step;
    double t_reduction = omp_get_wtime() - t0;
    printf("Reduction - Pi = %.10f (error: %e) Time: %.4f s\n", 
           pi, pi - 3.14159265358979, t_reduction);
    
    // Version avec critical (bonus - plus lente)
    t0 = omp_get_wtime();
    sum = 0.0;
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) * step;
        double term = 4.0 / (1.0 + x * x);
        #pragma omp critical
        sum += term;
    }
    pi = sum * step;
    double t_critical = omp_get_wtime() - t0;
    printf("Critical - Pi = %.10f (error: %e) Time: %.4f s\n", 
           pi, pi - 3.14159265358979, t_critical);
    
    return 0;
}