folder for 64-bit numbers

# make file
CC=g++
main: main.cpp quicksortLMT.cpp quicksortLMT.h quicksortLST.cpp quicksortLST.h RadixSortLMT.cpp RadixSortLMT.h RadixSortLST.cpp RadixSortLST.h
    $(CC) -O3 -o main main.cpp quicksortLMT.cpp quicksortLST.cpp RadixSortLMT.cpp RadixSortLST.cpp -lpthread
    
# run command
install: sudo apt install screen
screen -S dis
./main | tee result.txt
screen -r dis