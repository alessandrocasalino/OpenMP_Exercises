cmake_minimum_required(VERSION 3.25)
project(OpenMP_Exercises)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Exercise 1
add_executable(Exercise1 Exercise1/serial_vec_add.cpp)
add_executable(Exercise1_C Exercise1/serial_vec_add.c)

# Solutions 1
add_executable(Exercise1_Sol Solution1/omp_vec_add_parallel.cpp)
add_executable(Exercise1_C_Sol Solution1/omp_vec_add_parallel.c)