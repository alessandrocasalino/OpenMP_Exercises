#include <math.h>
#include <string.h>
#include <stdio.h>
#include <omp.h>

#define NN 4096
#define NM 4096

double A[NN][NM];
double Anew[NN][NM];

int main(int argc, char *argv[])
{

    int n = NN;
    int m = NM;
    int iter_max = 100;
    double tol = 1.0e-6;

    double error = 1.0;
    int iter = 0;

    memset(A, 0, n * m * sizeof(double));
    memset(Anew, 0, n * m * sizeof(double));

    for (int j = 0; j < n; j++)
    {
        A[j][0] = 1.0;
        Anew[j][0] = 1.0;
    }

    printf("Jacobi relaxation Calculation: %d x %d mesh\n", n, m);

    double start_time = omp_get_wtime();

    while (error > tol && iter < iter_max)
    {
        error = 0.0;

#pragma omp parallel default(none) shared(Anew, A, n, m, error)
        {

#pragma omp for collapse(2) reduction(max : error) schedule(dynamic, 256)
            for (int j = 1; j < n - 1; j++)
            {
                for (int i = 1; i < m - 1; i++)
                {
                    Anew[j][i] = 0.25 * (A[j][i + 1] + A[j][i - 1] + A[j - 1][i] + A[j + 1][i]);
                    error = fmax(error, fabs(Anew[j][i] - A[j][i]));
                }
            }

#pragma omp for collapse(2) schedule(dynamic, 256)
            for (int j = 1; j < n - 1; j++)
            {
                for (int i = 1; i < m - 1; i++)
                {
                    A[j][i] = Anew[j][i];
                }
            }
        }

        iter++;

        if (iter % 10 == 0)
            printf("%5d, %0.8lf\n", iter, error);
    }

    double end_time = omp_get_wtime();

    printf("Elapsed time (s) = %.2lf\n", end_time - start_time);
    printf("Stopped at iteration: %u\n", iter);

    return 0;
}
