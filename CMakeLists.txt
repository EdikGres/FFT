cmake_minimum_required(VERSION 3.20)
project(FFTTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(FFTTest main.cpp FFT.cpp FFT.h)
