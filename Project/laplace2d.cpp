#include <cmath>
#include <memory>
#include <cfloat>
#include <cstdio>
#include <sys/time.h>
#include <cstdlib>
#include <random>
#include <iostream>
#include <omp.h>

inline void initMat(double *A, size_t MM, size_t NN)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1, 1);

    for (std::size_t i = 0; i < MM * NN; ++i)
        A[i] = dis(gen);
}

int main()
{
    const std::size_t m(4096), n(4096);
    double tol(1.0e-6), error(1.0);
    int iter(0), iter_max(100);
    struct timeval temp_1, temp_2;
    double ttime(0.0), seconds(0.0), microseconds(0.0);

    // matrices initialization
    auto A = std::make_unique<double[]>(m * n);
    auto Anew = std::make_unique<double[]>(m * n);

    initMat(A.get(), m, n);

    std::cout << "Jacobi relaxation Calculation: << " << m << " x " << n << " mesh." << std::endl;

    gettimeofday(&temp_1, (struct timezone *)0);

    while (error > tol && iter < iter_max)
    {
        error = 0.0;

        for (std::size_t i = 1; i < m - 1; i++)
        {
            for (std::size_t j = 1; j < n - 1; j++)
            {
                Anew[i * n + j] = 0.25 * (A[i * n + (j + 1)] + A[i * n + (j - 1)] + A[(i - 1) * n - j] + A[(i + 1) * n - j]);
                error = fmax(error, fabs(Anew[i * n + j] - A[i * n + j]));
            }
        }

        for (std::size_t i = 1; i < m * n; i++)
        {
            A[i] = Anew[i];
        }

        iter++;

        if (iter % 10 == 0)
            std::cout << "Iteration: " << iter << " \t Error: " << error << std::endl;
    }

    gettimeofday(&temp_2, (struct timezone *)0);
    seconds = static_cast<double>(temp_2.tv_sec - temp_1.tv_sec);
    microseconds = static_cast<double>(temp_2.tv_usec - temp_1.tv_usec);
    ttime = 1e-6 * (seconds * 1.e6 + microseconds);

    std::cout << "Elapsed time (s) = " << ttime << std::endl
              << "Stopped at iteration: " << iter << std::endl;

    return 0;
}
