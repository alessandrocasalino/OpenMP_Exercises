#include <iostream>
#include <cmath>
#include <omp.h>

inline constexpr std::size_t ARRAY_SIZE {512*512*512};

int main ()
{

    double  scalar     = 2.0;

    std::cout << std::endl;
    std::cout << "Vector addition" << std::endl;
    std::cout << "  C++/OpenMP version" << std::endl;
    std::cout << std::endl;
    std::cout << "  A program which adds two vector." << std::endl;

    std::cout << std::endl;
    std::cout << "The total memory allocated is "
              << 2.0 * sizeof(double) * ARRAY_SIZE/(1024*1024*1024)
              << " GB." << std::endl;
    std::cout << std::endl;

    // Allocate and initialize vectors
    double * x { new double[ARRAY_SIZE] };
    double * y { new double[ARRAY_SIZE] };

    for (std::size_t i=0; i<ARRAY_SIZE; i++ )
    {
        x[i] = 1.0;
        y[i] = 2.0;
    }

    auto start_time { omp_get_wtime() };
    for (std::size_t i=0; i<ARRAY_SIZE; i++ )
    {
        y[i] = scalar*x[i] + y[i];
    }
    auto end_time { omp_get_wtime() };

    // Print a few entries
    std::cout << std::endl;
    std::cout << "   i \t\tx[i]\ty[i]\ty[i] = scalar*x[i] + y[i]" << std::endl;
    std::cout << std::endl;
    for (std::size_t i = 0; i < ARRAY_SIZE; i += ARRAY_SIZE/10 )
    {
        std::cout << "   " << i << "\t" << x[i] << "\t" << 2 << "\t" << y[i] << std::endl;
    }

    // Free memory
    delete[] x;
    delete[] y;

    // Terminate
    std::cout << std::endl;
    std::cout << "====================================="  << std::endl;
    std::cout << "SAXPY Time: " << (end_time - start_time) << " seconds" << std::endl;
    std::cout << "=====================================" << std::endl;

    return 0;
}

/* ..........Program Listing Completed ............. */

