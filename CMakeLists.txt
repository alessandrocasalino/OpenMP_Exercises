cmake_minimum_required(VERSION 3.25)
project(OpenMP_Exercises)

option(SOLUTIONS "Add solutions (if available)" OFF)

set(CMAKE_CXX_STANDARD 20)

# CMake OpenMP (search for libraries and add flags during compilation)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Exercise 1
add_executable(Exercise1 Exercise1/serial_vec_add.cpp)
add_executable(Exercise1_C Exercise1/serial_vec_add.c)

# Exercise 2
add_executable(Exercise2 Exercise2/matrix_add_dyn.cpp)
add_executable(Exercise2_C Exercise2/matrix_add.c)

# Exercise 3
add_executable(Exercise3 Exercise3/serial_saxpy.cpp)
add_executable(Exercise3_C Exercise3/serial_saxpy.c)

# Exercise 4
add_executable(Exercise4 Exercise4/serial_pi.c)

#SIMD
add_executable(SIMD_Exercise1 SIMD-Exercise1/mat_prod.c)
add_executable(SIMD_Exercise2 SIMD-Exercise2/pi_value.c)

# Project
add_executable(Project Project/laplace2d.c)
target_link_libraries(Project PRIVATE m)

# SOLUTIONS
if(SOLUTIONS)

    # Solutions 1
    # Only parallel
    add_executable(Exercise1_Sol1 Solution1/omp_vec_add_parallel.cpp)
    add_executable(Exercise1_C_Sol1 Solution1/omp_vec_add_parallel.c)
    # Manual workshare
    add_executable(Exercise1_C_Sol2 Solution1/omp_vec_add_parallel_mw.c)
    add_executable(Exercise1_Sol2 Solution1/omp_vec_add_parallel_mw.cpp)
    # Parallel for
    add_executable(Exercise1_C_Sol3 Solution1/omp_vec_add_parallel_for.c)
    add_executable(Exercise1_Sol3 Solution1/omp_vec_add_parallel_for.cpp)

    #Solutions 2
    add_executable(Exercise2_Sol Solution2/matrix_add_dyn.cpp)
    add_executable(Exercise2_C_Sol Solution2/matrix_add.c)

    #Solutions 3
    add_executable(Exercise3_Sol1 Solution3/Step1/saxpy.c)
    add_executable(Exercise3_Sol2 Solution3/Step2/saxpy.c)

    # Solutions 4
    add_executable(Exercise4_Sol1 Solution4/Step1/pi_critical.c)
    add_executable(Exercise4_Sol2 Solution4/Step2/pi_atomic.c)
    add_executable(Exercise4_Sol3 Solution4/Step3/pi_reduction.c)

    #SIMD
    add_executable(SIMD_Exercise1_Sol SIMD-Solution1/mat_prod.c)
    add_executable(SIMD_Exercise2_Sol SIMD-Solution2/pi_value.c)

    # Project
    add_executable(Project_Sol Project_Solution/laplace2d.c)
    target_link_libraries(Project_Sol PRIVATE m)

endif(SOLUTIONS)