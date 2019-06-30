cmake_minimum_required(VERSION 3.14)
project(dissertation)

set(CMAKE_CXX_STANDARD 11)

add_executable(dissertation mainS.cpp quicksortST.cpp quicksortST.h quicksortMT.cpp quicksortMT.h RadixSortST.cpp RadixSortST.h RadixSortMT.cpp RadixSortMT.h)
add_executable(dissertation2 Long/main.cpp Long/quicksortLST.cpp Long/quicksortLST.h Long/quicksortLMT.cpp Long/quicksortLMT.h Long/RadixSortLST.cpp Long/RadixSortLST.h Long/RadixSortLMT.cpp Long/RadixSortLMT.h)