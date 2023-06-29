#include <memory>
#include <cfloat>
#include "mat_prod.hpp"

int main()
{
     const size_t dim(2048);
     double N = static_cast<double>(dim), dtime(0.0), Mflops((2.0 * N * N * N - N * N) / pow(10, 6)), check(0.0);

     auto A = std::make_unique<double[]>(dim * dim);
     auto B = std::make_unique<double[]>(dim * dim);
     auto C = std::make_unique<double[]>(dim * dim);
     auto C2 = std::make_unique<double[]>(dim * dim);

     std::cout << "------------------------------------------------------------" << std::endl
               << " (square) Matrix-Matrix Multiplication " << std::endl
               << " with explicit contiguous vectors dynamic allocation" << std::endl
               << " OpenMP version with n_threads = " << omp_get_num_threads() << " out of " << omp_get_max_threads() << std::endl
               << " and number of processors = " << omp_get_num_procs() << std::endl
               << " Precision used " << DBL_MANT_DIG << std::endl
               << " Matrix size      = " << dim << std::endl
               << " Memory size (MB) = " << 3 * sizeof(double) * N * N * 4 / 1024.0 / 1024.0 << std::endl
               << "------------------------------------------------------------" << std::endl;

     dtime = omp_get_wtime();
     initMat(A.get(), dim);
     initMat(B.get(), dim);
     zeroMat(C.get(), dim);
     zeroMat(C2.get(), dim);
     dtime = omp_get_wtime() - dtime;
     std::cout << "Initialization occurred in " << dtime << " s." << std::endl
               << "------------------------------------------------------------" << std::endl;

     // std::cout << "A: " << std::endl;
     // printMat(A.get(), dim);
     // std::cout << "B: " << std::endl;
     // printMat(B.get(), dim);

     dtime = omp_get_wtime();
     multMat_omp(A.get(), B.get(), C.get(), dim);
     dtime = omp_get_wtime() - dtime;
     std::cout << "CPU time for multiplication: " << dtime << " s       Mflops/sec = " << Mflops / dtime << std::endl
               << "CPU computational check: " << C[dim * (dim / 2 + 1) + dim / 2] << std::endl
               << "------------------------------------------------------------" << std::endl;

     // std::cout << "C: " << std::endl;
     // printMat(C.get(), dim);

     dtime = omp_get_wtime();
     multMat_omp<2>(A.get(), B.get(), C2.get(), dim);
     dtime = omp_get_wtime() - dtime;
     std::cout << "CPU time for multiplication: " << dtime << " s       Mflops/sec = " << Mflops / dtime << std::endl
               << "CPU computational check: " << C2[dim * (dim / 2 + 1) + dim / 2] << std::endl
               << "------------------------------------------------------------" << std::endl;

     // std::cout << "C2: " << std::endl;
     // printMat(C2.get(), dim);

     for (size_t i = 0; i < dim; ++i)
     {
          for (size_t j = 0; j < dim; ++j)
          {
               check += pow(C2[i * dim + j] - C[i * dim + j], 2);
          }
     }

     std::cout << "---------------------------------" << std::endl
               << "Difference OMP Mat:              " << check << std::endl
               << "---------------------------------" << std::endl;

     return 0;
}