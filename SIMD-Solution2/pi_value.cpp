/* Exercise: Pi
 *  *
 *   * In this exercise you will determine the value
 *    * of PI using the integral  of
 *     *    4/(1+x*x) between 0 and 1.
 *      *
 *       * The integral is approximated by a sum of n intervals.
 *        *
 *         * The approximation to the integral in each interval is:
 *          *    (1/n)*4/(1+x*x).
 * * * * * * */

#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <omp.h>

inline constexpr std::size_t INTERVALS{100000000};

//TO COMPILE WITH -std = c++20 OR 23

int main()
{
    double x(0.0), dx{1.0 / static_cast<double>(INTERVALS)}, f(0.0), sum(0.0), pi(0.0);

    double time2{0.0};
    double time1{omp_get_wtime()};

    std::cout << "Number of intervals: " << INTERVALS << std::endl;

#pragma omp parallel for simd default(none) shared(INTERVALS,dx) private(x,f) reduction(+:sum) schedule(simd:static)
    for (std::size_t i = 1; i <= INTERVALS; i++)
    {
        x = dx * (static_cast<double>(i) - 0.5);
        f = 4.0 / (1.0 + x * x);
        sum += f;
    }

    pi = dx * sum;

    time2 = omp_get_wtime() - time1;
    
    long double error((std::numbers::pi_v<long double> - static_cast<long double>(pi)) / std::numbers::pi_v<long double>);

    std::cout << "Computed PI: " << std::setprecision(25) << pi << std::endl
              << "True PI: " << std::setprecision(25) << std::numbers::pi_v<long double> << std::endl
              << "Estimate error: " << std::abs(error) << std::endl
              << "Elapsed time (s) = " << time2 << std::endl;

    return 0;
}
