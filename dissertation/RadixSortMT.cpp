//
// Created by bubble on 2019/6/28.
//

#include "RadixSortMT.h"
#include <iostream>
#include <thread>
#include <math.h>
#include <string.h>

using namespace std;
const int RANGE = 257;
void printVectorSP(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << " ";
    }
    printf("\n");
}

// this method is used for get the value of radix position of a number, which can be 1 or 0
int digitSP(int num, int radix) {
    /*int t_num = 1;
    for (int i = 0; i < radix; ++i) {
        num = num >> 1;
    }
    num = num & t_num;*/
    return (long)(num / pow(256, radix)) % 256;
}

// this method is used to get the number of each bucket
void countDigitsSP(int* count, int* mas, int radix, int start, int end)
{
    for (int i = start; i < end; ++i)
    {
        ++count[digitSP(mas[i], radix) + 1];
    }
}

// move data in parallel
void moveDataSP(int *t_mas, int* count, int* mas, int start, int end, int t_id, int radix)
{
    for (int i = start; i < end; ++i)
    {
        t_mas[(count[digitSP(mas[i], radix)]++) + t_id] = mas[i];
    }
}

// copy data from temp to result
void copyDataSP(int *t_mas, int* mas, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        mas[i] = t_mas[i];
    }
}

// sort the array for according to the radix position
void countingSortSP(int* mas, int n, int radix) {

    int i;
    int count[RANGE] = { 0 };


    for (i = 0; i < n; ++i) {
        ++count[digitSP(mas[i], radix) + 1];
    }

    for (i = 1; i < RANGE; ++i) {
        count[i] += count[i - 1];
    }

    int *t_mas = new int[n];

    for (i = 0; i < n; ++i) {
        t_mas[count[digitSP(mas[i], radix)]++] = mas[i];
    }
    //memcpy((void*)mas, (void*)t_mas, n * sizeof(int));


    //std::copy(t_mas, t_mas+n, mas);
    memmove(mas, t_mas, sizeof(int)*n);
    //printVector(mas, n);
    delete[]t_mas;
    //delete[]count;
}


void radixsortMT(int* mas, int n, int radix) {
    int i;
    // thread container
    std::thread threads[256];

    if (n < 2) {
        return;
    }
    if (radix < 0) {
        return;
    }
    countingSortSP(mas, n, radix);
    //printVector(mas, n);
    bool flag = true;
    int start = 0;
    int tNumber = 0;
    for (int i = 0; i < (n - 1); ++i) {
        if (digitSP(mas[i], radix) != digitSP(mas[i + 1], radix)) {
            if ((i-start) > 50000 && tNumber < 256) {
                threads[tNumber++] = thread(radixsortMT, &mas[start], (i - start + 1), radix - 1);
            }else { radixsortMT(&mas[start], (i - start + 1), radix - 1); }
            start = i + 1;
            flag = false;
        }
    }
    for (int i = 0; i < tNumber; i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }

    if (flag) {
        radixsortMT(mas, n, radix - 1);
    } else {
        radixsortMT(&mas[start], (n - start), radix - 1);
    }
}