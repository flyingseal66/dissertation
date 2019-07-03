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
const int RANGE = 257;

// print array
void printVector(UINT64* mas, int n) {
    for (int i = 0; i < n; ++i) {
        cout << mas[i] << " ";
    }
    printf("\n");
}

// this method is used for get the value of radix position of a number, which can be 0-255
int digit(UINT64 num, int radix) {
    UINT64 t_num = 255;
    for(int i = 0; i < radix; ++i) {
        t_num = t_num << 8;
    }
    num = num & t_num;
    if(num != 0) {
        for(int i = 0; i < radix; ++i) {
            num = num >> 8;
        }
    }
    return num;
}

// sort the array for according to the radix position
void countingSort(UINT64* mas, UINT64 n, int radix) {
    //if (n <= 2) return;
    UINT64 i;
    int count[RANGE] = { 0 };

    // count the number of each bucket
    for (i = 0; i < n; ++i) {
        ++count[digit(mas[i], radix)+1];
    }
    for (int m = 1; m < RANGE; ++m) {
        count[m] += count[m - 1];
    }

    // temp array
    auto *t_mas = new UINT64[n];
    for (i = 0; i < n; ++i) {
        t_mas[count[digit(mas[i], radix)]++] = mas[i];
    }

    // copy element from temp array to target array
    for (i = 0; i < n; i++) {
        mas[i] = t_mas[i];
    }
    delete[]t_mas;
}

// sort the array by radix
void msdRadixPass(UINT64* mas, UINT64 n, int radix) {
    if (radix < 0) {
        return;
    }
    countingSort(mas, n, radix);
    bool flag = true;
    UINT64 start = 0;
    for (int i = 0; i < (n - 1); ++i) {
        if (digit(mas[i], radix) != digit(mas[i + 1], radix)) {
            msdRadixPass(&mas[start], (i - start + 1), radix - 1);
            start = i + 1;
            flag = false;
        }
    }
    if (flag) {
        msdRadixPass(mas, n, radix - 1);
    }
    else {
        msdRadixPass(&mas[start], (n - start), radix - 1);
    }
}

void msdRadixSort(UINT64 * mas, UINT64 n) {
    msdRadixPass(mas, n, 7);
}