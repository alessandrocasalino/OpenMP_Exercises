#pragma once
#include <omp.h>

#include <iomanip>
#include <random>
#include <iostream>

inline void initMat(double *A, std::size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1, 1);

    for (std::size_t i = 0; i < n * n; ++i)
        A[i] = dis(gen);
}

inline void transpMat(double *A, double *B, std::size_t n)
{
#pragma omp parallel for
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < n; ++j)
        {
            B[j * n + i] = A[i * n + j];
        }
    }
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

inline void multMat_T(double *A, double *BT, double *C, std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < n; ++j)
        {
            double prod = 0.0;
            for (std::size_t k = 0; k < n; ++k)
            {
                prod += A[i * n + k] * BT[j * n + k];
            }
            C[i * n + j] = prod;
        }
    }
}

inline void multMat_T_omp(double *A, double *BT, double *C, std::size_t n)
{
#pragma omp parallel for
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < n; ++j)
        {
            double prod = 0.0;
            for (std::size_t k = 0; k < n; ++k)
            {
                prod += A[i * n + k] * BT[j * n + k];
            }
            C[i * n + j] = prod;
        }
    }
}
