/* ======================================================
 * Serial Pi code
 * This program will numerically compute the integral of
 *    4/(1+x*x) between 0 and 1.
 *
 * =====================================================*/

#include <stdio.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define PI25DT 3.141592653589793238462643
#define INTERVALS 1000000000

int main(int argc, char **argv)
{
    long int i, intervals = INTERVALS;
    double x, dx, f, sum, pi;
    double time2;

    printf ( "\n" );
    printf ( "Estimating the value of Pi\n" );
    printf ( "  C/Serial version\n" );
    printf ( "\n" );

    time_t time1 = clock();

    printf("Number of intervals: %ld\n", intervals);

    sum = 0.0;
    dx = 1.0 / (double) intervals;

    double start_time = omp_get_wtime();

#pragma omp parallel for simd default(none) shared(intervals,dx) private(x,f) reduction(+:sum) schedule(simd:static)
    for (i = 1; i <= intervals; i++)
    {
        x = dx * ( (double) i - 0.5);
        f = 4.0 / (1.0 + x*x);
        sum = sum + f;
    }

    pi = dx*sum;

    double end_time = omp_get_wtime();

    printf("Computed PI %.24f\n", pi);
    printf("The true PI %.24f\n\n", PI25DT);
    printf("Elapsed time (s) = %.2lf\n", end_time - start_time);

    return 0;
}
