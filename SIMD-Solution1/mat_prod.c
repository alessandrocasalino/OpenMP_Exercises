#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc,char **argv) {
    int n = 1000;
    int i, j, k;
    double start_time, end_time;
    double ( *a )[n] = malloc(sizeof(double[n][n]));
    double ( *b )[n] = malloc(sizeof(double[n][n]));
    double ( *c )[n] = malloc(sizeof(double[n][n]));

    printf ( "\n" );
    printf ( "  C/OpenMP version\n" );
    printf ( "==========================================================\n" );

    printf ( "  Number of processors available = %d\n", omp_get_num_procs ( ) );
    printf ( "  Number of threads =              %d\n", omp_get_max_threads ( ) );

    printf ( "==========================================================\n" );

    for (i=0; i<n; i++)
        for (j=0; j<n; j++) {
            a[i][j] = ((double)rand())/((double)RAND_MAX);
            b[i][j] = ((double)rand())/((double)RAND_MAX);
            c[i][j] = 0.0;
        }
    start_time = omp_get_wtime();
#pragma omp parallel for simd default(none) shared(a,b,c,n) private(j,k)
    for (i=0; i<n; ++i)
        for (k=0; k<n; k++)
            for (j=0; j<n; ++j)
                c[i][j] += a[i][k]*b[k][j];
    end_time = omp_get_wtime();

    /* .......... Terminate ............. */
    for (i=0; i<4; i++)
        for (j=0; j<4; j++)
            printf("[%2d %2d] = %10.4f\n", i, j, c[i][j]);

    printf ( "\n" );
    printf("===================================== \n");
    printf ("Execution Time: %f seconds \n", (end_time - start_time));
    printf("===================================== \n");

    return 0;
}
