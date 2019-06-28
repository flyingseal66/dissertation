#include <iostream>
#include <ctime>
#include <random>
#include <thread>
#include<string>
#include "quicksortST.h"
#include "quicksortMT.h"
#include "RadixSortST.h"
#include "RadixSortMT.h"

// the scope of array length
const int NMIN = 1000000;
const int NMAX = 10000001;
const int NAVG = 1;

// Execution switcher
#define QUICKSORTSTSW;
#define QUICKSORTMTSW;
#define RADIXSORTSTSW;
#define RADIXSORTMTSW;

using namespace std;
void initData(int *data, int size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 32767);
    for (int i = 0; i < size; ++i) {
        data[i] = dist(mt);
    }
}

void checkOrder(int *data, int i) {
    for (int j = 1; j < i; j++) {
        if (data[j] < data[j - 1]) {
            std::cout << "Wrong order is found in Radix sort MSD:" << j << " " << data[j] << " " << data[j - 1] << std::endl;
        }
    }
}
int main() {
    string result = "";
    string rangTitle = "";
    
    #ifdef QUICKSORTSTSW
    cout << "QuicksortST started!" << endl;
    for (int i = NMIN; i < NMAX; i *= 10) {
        rangTitle += to_string(i) + " ";
        double totalTime = 0;
        for (int j = 0; j < NAVG; ++j) {
            int  *data = new int[i];
            initData(data, i);
            auto start = chrono::steady_clock::now(); // start time
            quickSort(data, 0, i - 1);
            auto end = chrono::steady_clock::now();
            totalTime += chrono::duration <double, milli>(end - start).count();
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            checkOrder(data, i);
        }
        result += to_string(totalTime/NAVG) + "ms ";
    }
    cout << "size " + rangTitle << endl;
    cout << "time " + result<< endl;
    cout << endl;
    #endif

    #ifdef QUICKSORTMTSW
    cout << "QuicksortMT started!" << endl;
    result = "";
    rangTitle = "";
    for (int i = NMIN; i < NMAX; i *= 10) {
        rangTitle += to_string(i) + " ";
        double totalTime = 0;
        for (int j = 0; j < NAVG; ++j) {
            int  *data = new int[i];
            initData(data, i);
            auto start = chrono::steady_clock::now(); // start time
            quickSortMT(data, 0, i - 1);
            auto end = chrono::steady_clock::now();
            totalTime += chrono::duration <double, milli>(end - start).count();
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            checkOrder(data, i);
        }
        result += to_string(totalTime/NAVG) + "ms ";
    }
    cout << "size " + rangTitle << endl;
    cout << "time " + result<< endl;
    cout << endl;
    #endif

    #ifdef RADIXSORTSTSW
    cout << "RadixSortST started!" << endl;
    result = "";
    rangTitle = "";
    for (int i = NMIN; i < NMAX; i *= 10) {
        rangTitle += to_string(i) + " ";
        double totalTime = 0;
        for (int j = 0; j < NAVG; ++j) {
            int  *data = new int[i];
            initData(data, i);
            auto start = chrono::steady_clock::now(); // start time
            msdRadixSortS(data, i);
            auto end = chrono::steady_clock::now();
            totalTime += chrono::duration <double, milli>(end - start).count();
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            checkOrder(data, i);
        }
        result += to_string(totalTime/NAVG) + "ms ";
    }
    cout << "size " + rangTitle << endl;
    cout << "time " + result<< endl;
    cout << endl;
    #endif

    #ifdef RADIXSORTMTSW)
    cout << "RadixSortMT started!" << endl;
    result = "";
    rangTitle = "";
    for (int i = NMIN; i < NMAX; i *= 10) {
        rangTitle += to_string(i) + " ";
        double totalTime = 0;
        for (int j = 0; j < NAVG; ++j) {
            int  *data = new int[i];
            initData(data, i);
            auto start = chrono::steady_clock::now(); // start time
            radixsortMT(data, i, 1);
            auto end = chrono::steady_clock::now();
            totalTime += chrono::duration <double, milli>(end - start).count();
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            checkOrder(data, i);
        }
        result += to_string(totalTime/NAVG) + "ms ";
    }
    cout << "size " + rangTitle << endl;
    cout << "time " + result<< endl;
    #endif

    return 0;
}

