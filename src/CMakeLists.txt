cmake_minimum_required(VERSION 3.28)
project(src)

set(CMAKE_CXX_STANDARD 20)

add_executable(src A2.cpp
        ArrayGenerator.h
        ArrayGenerator.cpp
        SortTester.h
        SortTester.cpp

)
