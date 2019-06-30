folder for 64-bit numbers

# make file
CC=g++
main: main.cpp quicksortLMT.cpp quicksortLMT.h quicksortLST.cpp quicksortLST.h RadixSortLMT.cpp RadixSortLMT.h RadixSortLST.cpp RadixSortLST.h
    $(CC) -O3 -o main main.cpp quicksortMT.cpp quicksortST.cpp RadixSortMT.cpp RadixSortST.cpp -lpthread