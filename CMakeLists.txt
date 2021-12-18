cmake_minimum_required(VERSION 3.21)
project(kmp_with_error)

set(CMAKE_CXX_STANDARD 20)

add_executable(kmp_with_error kmp_with_errors.cpp kmp.cpp)
