cmake_minimum_required(VERSION 3.14)
project(dissertation)

set(CMAKE_CXX_STANDARD 11)

add_executable(dissertation main.cpp quicksortST.cpp quicksortST.h quicksortMT.cpp quicksortMT.h RadixSortST.cpp RadixSortST.h RadixSortMT.cpp RadixSortMT.h)