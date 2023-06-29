#pragma once
#include <omp.h>

#include <iomanip>
#include <random>
#include <iostream>

template <int i = 0>
inline void multMat_omp(double *A, double *B, double *C, std::size_t n) = delete;

inline void initMat(double *A, std::size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1, 1);

    for (std::size_t i = 0; i < n * n; ++i)
        A[i] = dis(gen);
}

inline void zeroMat(double *A, std::size_t n)
{
    for (std::size_t i = 0; i < n * n; ++i)
        A[i] = 0.0;
}

inline void printMat(double *A, std::size_t n)
{

    typedef std::numeric_limits<double> dbl;
    std::cout.precision(dbl::max_digits10);
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < n; ++j)
            std::cout << std::setw(26) << A[i * n + j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

inline void multMat(double *A, double *B, double *C, std::size_t n)
{

    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < n; ++j)
        {
            double prod = 0;
            for (std::size_t k = 0; k < n; ++k)
            {
                prod += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = prod;
        }
    }
}

// First version with omp
template <>
inline void multMat_omp(double *A, double *B, double *C, std::size_t n)
{

#pragma omp parallel for
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < n; ++j)
        {
            double prod(0.0);
            for (std::size_t k = 0; k < n; ++k)
            {
                prod += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = prod;
        }
    }
}

// Second version with omp
template <>
inline void multMat_omp<1>(double *A, double *B, double *C, std::size_t n)
{
    double prod(0.0);
#pragma omp parallel for default(none) shared(A, B, C, n) reduction(+ : prod)
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < n; ++j)
        {
            prod = 0.0;
            for (std::size_t k = 0; k < n; ++k)
            {
                prod += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = prod;
        }
    }
}

// Third version with omp and SIMD
template <>
inline void multMat_omp<2>(double *A, double *B, double *C, std::size_t n)
{
    std::size_t i(0), j(0), k(0);
#pragma omp parallel for simd default(none) shared(A, B, C, n) private(i, j, k)
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            double prod(0.0); // automatically private since it is defined inside the loop
            for (k = 0; k < n; ++k)
            {
                prod += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = prod;
        }
    }
}
