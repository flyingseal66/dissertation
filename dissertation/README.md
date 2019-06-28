# dissertation
dissertation code

# make file
CC=g++
main: main.cpp quicksortMT.cpp quicksortMT.h quicksortST.cpp quicksortST.h RadixSortMT.cpp RadixSortMT.h RadixSortST.cpp RadixSortST.h
        $(CC) -O3 -o main main.cpp quicksortMT.cpp quicksortST.cpp RadixSortMT.cpp RadixSortST.cpp -lpthread
