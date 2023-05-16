cmake_minimum_required(VERSION 3.25)
project(OpenMP_Exercises)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS -fopenmp)

# Exercise 1
add_executable(Exercise1 Exercise1/serial_vec_add.cpp)
add_executable(Exercise1_C Exercise1/serial_vec_add.c)
