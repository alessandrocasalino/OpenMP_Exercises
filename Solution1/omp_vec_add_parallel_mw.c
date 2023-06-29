#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#endif

int main(int argc, char *argv[])
{
    int i;
    int n = 10000000;
    double tick, tock;

    float *a, *b, *c;

    printf("\n");
    printf("Vector addition\n");
    printf("  C/OpenMP version\n");
    printf("\n");
    printf("  A program which adds two vector.\n");

    printf("\n");
    printf("  Number of processors available = %d\n", omp_get_num_procs());
    printf("  Number of threads =              %d\n", omp_get_max_threads());
    printf("\n");

    /* Allocate the vector data. */
    a = (float *)malloc(n * sizeof(float));
    b = (float *)malloc(n * sizeof(float));
    c = (float *)malloc(n * sizeof(float));

    /* Begin the parallel region. */

    // fill the arrays
    for (i = 0; i < n; i++)
    {
        a[i] = (float)(1);
        b[i] = (float)(2);
        c[i] = (float)(0);
    }

    tick = omp_get_wtime();
/* add two vectors */
#pragma omp parallel // NOLINT   <-- necessary to avoid clang-tidy warning on default(none) clause
    {
        /* Get total number of threads and it's thread ID */
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        /* Iteration starts and ends */
        int start = tid * n / nthreads;
        int end = (tid + 1) * n / nthreads - 1;

        printf("  --> Thread %d: start %d - end %d\n", tid, start, end);

        /* add two vectors */
        for (i = start; i <= end; i++)
            c[i] = a[i] + b[i];
    }
    tock = omp_get_wtime();

    /* Print a few entries. */
    printf("\n");
    printf("   i        a[i]        b[i]      c[i] = a[i] + b[i]\n");
    printf("\n");
    for (i = 0; i < n && i < 10; i++)
    {
        printf("  %2d  %10.4f  %10.4f  %10.4f\n", i, a[i], b[i], c[i]);
    }
    /* Free memory */
    free(a);
    free(b);
    free(c);

    /* Terminate */
    printf("\n");
    printf("Vector addition\n");
    printf("  Execution is successful!.\n");

    printf("===================================== \n");
    printf("Work took %f seconds\n", tock - tick);
    printf("===================================== \n");

    return 0;
}
