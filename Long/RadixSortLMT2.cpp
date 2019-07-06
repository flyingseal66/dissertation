#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <random>
#include <limits>
#include <ctime>
#include <thread>
#include <string.h>
#include <atomic>
#include "quicksortLST.h"

using namespace std;
const UINT64 RANGE = 257;

// this method is used for get the value of radix position of a number, which can be 0-255
int digitMT(UINT64 num, int radix) {
    UINT64 t_num = 255;
    if(num != 0) {
        for(int i = 0; i < radix; i++) {
            num = (num >> 8);
        }
    }
    return (num & t_num);
}

// sort the array for according to the radix position
void countingSortMT(UINT64* mas, UINT64 n, int radix, UINT64 *bucks) {
    //if (n <= 2) return;
    UINT64 i;
    UINT64 count[RANGE] = { 0 };

    // count the number of each bucket
    for (i = 0; i < n; ++i) {
        ++count[digitMT(mas[i], radix)+1];
    }
    bucks[0] = count[0];
    for (int m = 1; m < RANGE; ++m) {
        count[m] += count[m - 1];
        bucks[m] = count[m];
    }

    // sorted temp array
    auto *t_mas = new UINT64[n];
    for (i = 0; i < n; ++i) {
        t_mas[count[digitMT(mas[i], radix)]++] = mas[i];
    }

    // copy element from temp array to target array
    for (i = 0; i < n; i++) {
        mas[i] = t_mas[i];
    }
    delete[]t_mas;
}

// sort the array by radix
void msdRadixPassMT(UINT64* mas, UINT64 n, int radix) {
    if (n<2) return;
    if (radix < 0) return;

    // These buckets contains the number of each digit
    auto *buckets = new UINT64[RANGE]();
    countingSortMT(mas, n, radix, buckets);
    UINT64 start = 0;
    std::thread threads[RANGE];
    int tNumber = 0;
    // go through each bucket
    // thread container
    std::thread t1;
    for (int j = 0; j < RANGE; j++) {

        UINT64 diff = 0;
        if (j > 0) {
            diff = buckets[j] - buckets[j-1];

        }
        if (((j == 0 && buckets[0] > 1) || diff > 0)) {
            if(j==0) {
                /*if (buckets[0] > 50000 && tNumber<200) {
                    threads[tNumber++] = std::thread(msdRadixPassMT, &mas[start], buckets[0], radix - 1);
                } else {
                    msdRadixPassMT(&mas[start], buckets[0], radix - 1);
                }*/
                msdRadixPassMT(&mas[start], buckets[0], radix - 1);
                start = buckets[0];
            } else {
                if (diff > 10000 && tNumber<RANGE) {
                    //cout << "enter new thread" << tNumber++ <<endl;
                    threads[tNumber++] = thread(msdRadixPassMT, &mas[start], diff, radix - 1);
                } else {
                    msdRadixPassMT(&mas[start], diff, radix - 1);
                }
                start = buckets[j];
            }

        }
    }
    //if (t1.joinable()) t1.join();
    for (int i = 0; i < tNumber; i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
    delete []buckets;
}

void msdRadixSortMT(UINT64 * mas, UINT64 n) {
    msdRadixPassMT(mas, n, 7);
}