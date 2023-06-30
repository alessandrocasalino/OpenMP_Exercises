/* ======================================================
 * 2D Vector addition
 * The value of 3 for each element
 * Alessandro Casalino & Nitin Shukla
 * =====================================================*/

#include <iostream>
#include <vector>
#ifdef _OPENMP
#include <omp.h>
#else
#include <time.h>
#endif

inline constexpr std::size_t M{10000};
inline constexpr std::size_t N{10000};

int main()
{

    std::cout << std::endl;
    std::cout << "2D vector sum" << std::endl;
    std::cout << "  C++/OpenMP version" << std::endl;
    std::cout << "==========================================================" << std::endl;

    std::cout << "  Number of processors available = " << omp_get_num_procs() << std::endl;
    std::cout << "  Number of threads =              " << omp_get_max_threads() << std::endl;

    std::cout << "==========================================================" << std::endl;

    std::vector<double> A(M * N, 2.);
    std::vector<double> B(M * N, 2.);
    std::vector<double> C(M * N, 0.);

    // C = A + B

#ifdef _OPENMP
    auto time1{omp_get_wtime()};
#else
    auto time1 = clock();
#endif

// Tricky thing: DO NOT brace initialize i, e.g., do NOT do size_t {0}, but use direct initialization instead
// From the serial code, this should be changed
#pragma omp for collapse(2)
    for (std::size_t i = 0; i < M; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            C[i * M + j] = A[i * M + j] + B[i * M + j];
        }
    }

#ifdef _OPENMP
    auto time2{omp_get_wtime() - time1};
#else
    auto time2 = (clock() - time1) / (double)CLOCKS_PER_SEC;
#endif

    std::cout << std::endl;
    std::cout << "  Elapsed time (s) = " << time2 << std::endl;
    std::cout << "==========================================================" << std::endl;

    // Print some values
    /*
        for (std::size_t i = 0; i < N; i += N / 4)
        {
            for (std::size_t j = 0; j < M; j += M / 4)
            {
                std::cout << i << "\t" << j << "\t" << A[i * N + j] << "\t" << B[i * N + j] << "\t" << C[i * N + j] << std::endl;
            }
        }
    */

    return 0;
}
