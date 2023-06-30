#include <cmath>
#include <memory>
#include <cfloat>
#include <chrono>
#include "mat_prod.hpp"

int main()
{
    const size_t dim(2048);
    double N{static_cast<double>(dim)}, Mflops{(2.0 * N * N * N - N * N) / pow(10, 6)};

    auto A{std::make_unique<double[]>(dim * dim)};
    auto B{std::make_unique<double[]>(dim * dim)};
    auto C{std::make_unique<double[]>(dim * dim)};

    std::cout << "------------------------------------------------------------" << std::endl
              << " (square) Matrix-Matrix Multiplication " << std::endl
              << " with explicit contiguous vectors dynamic allocation" << std::endl
              << " Serial version " << std::endl
              << " Precision used " << DBL_MANT_DIG << std::endl
              << " Matrix size      = " << dim << std::endl
              << " Memory size (MB) = " << 3 * sizeof(double) * N * N * 4 / 1024.0 / 1024.0 << std::endl
              << "------------------------------------------------------------" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    initMat(A.get(), dim);
    initMat(B.get(), dim);
    zeroMat(C.get(), dim);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Initialization occurred in " << static_cast<double>(elapsed.count()) * 1.0e-9 << " s." << std::endl
              << "------------------------------------------------------------" << std::endl;

    // std::cout << "A: " << std::endl;
    // printMat(A.get(), dim);
    // std::cout << "B: " << std::endl;
    // printMat(B.get(), dim);

    start = std::chrono::high_resolution_clock::now();
    multMat(A.get(), B.get(), C.get(), dim);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << " CPU time for multiplication: " << static_cast<double>(elapsed.count()) * 1.0e-9 << std::endl
              << " Mflops/sec = " << Mflops / (static_cast<double>(elapsed.count()) * 1.0e-9) << std::endl
              << " CPU computational check: " << C[dim * (dim / 2 + 1) + dim / 2] << std::endl
              << "------------------------------------------------------------" << std::endl;

    // std::cout << "C: " << std::endl;
    // printMat(C.get(), dim);

    return 0;
}