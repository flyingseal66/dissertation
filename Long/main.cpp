#include <iostream>
#include <ctime>
#include <random>
#include <thread>
#include<string>
#include "quicksortLST.h"
#include "quicksortLMT.h"
#include "RadixSortLST.h"
#include "RadixSortLMT.h"

// the scope of array length
const int NMIN = 1000000;
const int NMAX = 1000001;
// the number of cycles
const int NAVG = 1;

// Execution switcher
#define QUICKSORTSTSW
#define QUICKSORTMTSW
#define RADIXSORTSTSW
#define RADIXSORTMTSW
typedef unsigned long long UINT64;

using namespace std;
void initData(int *data, int size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 32767);
    for (int i = 0; i < size; ++i) {
        data[i] = dist(mt);
    }
}


void randUint(UINT64 *data, int size) {
    UINT64 r = 1;
    for (UINT64 k = 0; k < size; ++k) {
        r ^= r >> 12;        // a
        r ^= r << 25;        // b
        r ^= r >> 27;        // c
        data[k] = r;
    }
}

void checkOrder(UINT64 *data, int i, string sortType) {
    for (int j = 1; j < i; j++) {
        if (data[j] < data[j - 1]) {
            std::cout << "Wrong order is found in " << sortType << ": " << j << " " << data[j] << " " << data[j - 1] << std::endl;
        }
    }
}
int main() {
    // Test rand()




    string result = "";
    string rangTitle = "";
    auto  *data = new UINT64[NMAX];
    #ifdef QUICKSORTSTSW
    cout << "QuicksortST started!" << endl;
    double totalTime = 0;
    for (int i = NMIN; i < NMAX; i *= 10) {
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            randUint(data, i); // initialise data
            auto start = chrono::steady_clock::now(); // start time
            quickSortLST(data, 0, i - 1);
            auto end = chrono::steady_clock::now();
            totalTime += chrono::duration <double, milli>(end - start).count();
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            checkOrder(data, i, "QuicksortST");
        }
    }
    cout << "size " + rangTitle << endl;
    printf("time = %.3f\n", totalTime/(NAVG*1000));
    cout << endl;
    #endif

    #ifdef QUICKSORTMTSW
    cout << "QuicksortMT started!" << endl;
    result = "";
    rangTitle = "";
    totalTime = 0;
    for (int i = NMIN; i < NMAX; i *= 10) {
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            randUint(data, i);
            auto start = chrono::steady_clock::now(); // start time
            quickSortLMT(data, 0, i - 1);
            auto end = chrono::steady_clock::now();
            totalTime += chrono::duration <double, milli>(end - start).count();
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            checkOrder(data, i, "QuicksortMT");
        }
    }
    cout << "size " + rangTitle << endl;
    printf("time = %.3f\n", totalTime/(NAVG*1000));
    cout << endl;
    #endif

    #ifdef RADIXSORTSTSW
    cout << "RadixSortST started!" << endl;
    result = "";
    rangTitle = "";
    totalTime = 0;
    for (int i = NMIN; i < NMAX; i *= 10) {
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            randUint(data, i);
            auto start = chrono::steady_clock::now(); // start time
            msdRadixSort(data, i);
            auto end = chrono::steady_clock::now();
            totalTime += chrono::duration <double, milli>(end - start).count();
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            checkOrder(data, i, "/*");
        }
    }
    cout << "size " + rangTitle << endl;
    printf("time = %.3f\n", totalTime/(NAVG*1000));
    cout << endl;
    #endif

    #ifdef RADIXSORTMTSW
    cout << "RadixSortMT started!" << endl;
    result = "";
    rangTitle = "";
    totalTime = 0;
    for (int i = NMIN; i < NMAX; i *= 10) {
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            randUint(data, i);
            auto start = chrono::steady_clock::now(); // start time
            msdRadixSortLMT(data, i);
            auto end = chrono::steady_clock::now();
            totalTime += chrono::duration <double, milli>(end - start).count();
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            checkOrder(data, i, "RadixSortMT");
        }
    }
    cout << "size " + rangTitle << endl;
    printf("time = %.3f\n", totalTime/(NAVG*1000));
    #endif

    return 0;
}

