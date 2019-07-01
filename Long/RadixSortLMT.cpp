#include <iostream>
#include <random>
#include <ctime>
#include <thread>
#include <string.h>
#include "quicksortLST.h"


using namespace std;
const auto RANGE = 257;
void printVectorSP(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << " ";
    }
    printf("\n");
}

// this method is used for get the value of radix position of a number, which can be 1 or 0
int digitSP(UINT64 num, int radix) {
    return (long long)(num / pow(256, radix)) % 256;
}

// this method is used to get the number of each bucket
void countDigitsSP(int* count, UINT64 * mas, int radix, int start, int end)
{
    for (int i = start; i < end; ++i) {
        ++count[digitSP(mas[i], radix) + 1];
    }
}

// move data in parallel
void moveDataSP(UINT64 *t_mas, int* count, UINT64 * mas, int start, int end, int t_id, int radix)
{
    for (int i = start; i < end; ++i)
    {
        t_mas[(count[digitSP(mas[i], radix)]++) + t_id] = mas[i];
    }
}

// copy data from temp to result
void copyDataSP(UINT64 *t_mas, UINT64 *mas, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        mas[i] = t_mas[i];
    }
}

// sort the array for according to the radix position
void countingSortSP(UINT64 * mas, int n, int radix) {

    int i;
    int count[RANGE] = { 0 };


    for (i = 0; i < n; ++i) {
        ++count[digitSP(mas[i], radix) + 1];
    }

    for (i = 1; i < RANGE; ++i) {
        count[i] += count[i - 1];
    }

    auto *t_mas = new UINT64[n];

    for (i = 0; i < n; ++i) {
        t_mas[count[digitSP(mas[i], radix)]++] = mas[i];
    }
    memcpy((void*)mas, (void*)t_mas, n * sizeof(UINT64));


    //std::copy(t_mas, t_mas+n, mas);
    //memmove(mas, t_mas, sizeof(UINT64)*n);
    //printVector(mas, n);
    delete[]t_mas;
    //delete[]count;
}


void msdRadixPassSP(UINT64 * mas, int n, int radix) {
    if (n < 2) {
        return;
    }
    if (radix < 0) {
        return;
    }
    // thread container
    std::thread threads[256];
    countingSortSP(mas, n, radix);
    //printVector(mas, n);
    bool flag = true;
    int start = 0;
    int tNumber = 0;
    for (int i = 0; i < (n - 1); ++i) {
        if (digitSP(mas[i], radix) != digitSP(mas[i + 1], radix)) {
            if ((i-start) > 500000000 && tNumber < 256) {
                threads[tNumber++] = thread(msdRadixPassSP, &mas[start], (i - start + 1), radix - 1);
            }else { msdRadixPassSP(&mas[start], (i - start + 1), radix - 1); }
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
        msdRadixPassSP(mas, n, radix - 1);
    } else {
        msdRadixPassSP(&mas[start], (n - start), radix - 1);
    }


    /*if (t2.joinable()) {
        t2.join();
    }*/
}

void msdRadixSortLMT(UINT64 * mas, int n) {
    msdRadixPassSP(mas, n, 7);
}
