#include <iostream>
#include <ctime>
#include <random>
#include <thread>
#include "quicksortShortSingle.h"

const int NMIN = 1000000;
const int NMAX = 10000000;
const int NAVG = 2;
using namespace std;

int main() {
    cout << "Program started!" << endl;

    for (int i = NMIN; i < NMAX; i *= 10) {
        int  *data = new int[i];
        auto start = chrono::steady_clock::now(); // start time
        quickSort(data, 0, i - 1);
        auto end = chrono::steady_clock::now();
        cout << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
        for (int j = 1; j < i; j++) {
            if (data[i] < data[i - 1]) {
                std::cout << "Wrong order is found in Radix sort MSD:" << i << " " << data[i] << " " << data[i - 1] << std::endl;
            }
        }
    }
    return 0;
}

void initData(int *data, int size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 32767);
    for (int i = 0; i < size; ++i) {
        data[i] = dist(mt);
    }
}