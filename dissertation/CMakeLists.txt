cmake_minimum_required(VERSION 3.14)
project(dissertation)

set(CMAKE_CXX_STANDARD 11)

add_executable(-O3 -o dissertation main.cpp quicksortShortSingle.cpp quicksortShortSingle.h)