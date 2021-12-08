cmake_minimum_required(VERSION 3.20)
project(simple_polynomial_regression_opt)

set(CMAKE_CXX_STANDARD 14)

add_executable(simple_polynomial_regression_opt main.cpp polynomial_regression.cpp gauss_method.cpp utils.cpp)
