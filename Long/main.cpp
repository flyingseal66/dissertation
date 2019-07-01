#include <iostream>
#include <ctime>
#include <random>
#include <thread>
#include <string>
#include "quicksortLST.h"
#include "quicksortLMT.h"
#include "RadixSortLST.h"
#include "RadixSortLMT.h"

// the scope of array length
const int NMIN = 1000000;
const int NMAX = 1000000001;
// the number of cycles
const int NAVG = 2;

// Execution switcher
#define QUICKSORTSTSW
#define QUICKSORTMTSW
#define RADIXSORTSTSW
//#define RADIXSORTMTSW
typedef unsigned long long UINT64;

using namespace std;

// generate an UINT64 array with a length of size
void randUint(UINT64 *data, int size) {
    UINT64 r = 1;
    for (UINT64 k = 0; k < size; ++k) {
        r ^= r >> 12;        // a
        r ^= r << 25;        // b
        r ^= r >> 27;        // c
        data[k] = r;
    }
}

// check the sorted array of data to see if there are numbers in wrong order
void checkOrder(UINT64 *data, int i, const string& sortType) {
    for (int j = 1; j < i; j++) {
        if (data[j] < data[j - 1]) {
            std::cout << "Wrong order is found in " << sortType << ": " << j << " " << data[j] << " " << data[j - 1] << std::endl;
        }
    }
}
int main() {
    // Test rand()
    auto currentTime = std::chrono::system_clock::now();
    std::time_t c_time = std::chrono::system_clock::to_time_t(currentTime);
    cout << std::ctime(&c_time);
    cout << "Google cloud instance, ubuntu 18.04, 64 bit, 16*8 cores" << endl;
    cout << "NCPUS=16, RAM=60GB, Intel Haswell,cpu family:6, model:63, model name: Intel(R) Xeon(R) CPU @ 2.30GHz" << endl;


    // The test of Quicksort with a single thread
    string result;
    string rangTitle;
    double totalTime;
    auto  *data = new UINT64[NMAX];
    #ifdef QUICKSORTSTSW
    cout << "QuicksortST started!" << endl;
    result = "";
    for (int i = NMIN; i < NMAX; i *= 10) {
        totalTime = 0;
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            auto initStart = chrono::steady_clock::now(); // start time
            randUint(data, i); // initialise data
            auto initEnd = chrono::steady_clock::now(); // start time
            cout << "size " << i << ", initialization time " << chrono::duration <double, milli>(initEnd - initStart)
                    .count()/1000 << "s" << endl;
            auto start = chrono::steady_clock::now(); // start time
            quickSortLST(data, 0, i - 1);
            auto end = chrono::steady_clock::now();
            double middleTime = chrono::duration <double, milli>(end - start).count()/1000;
            totalTime += middleTime;
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            string strTime = to_string(middleTime);
            string eachTime = strTime.substr(0,strTime.find(".")+4) + " ";
            cout << "length " << i << ", " << "Round" << j+1 << " " << eachTime << endl;
            if (j == 0) {
                checkOrder(data, i, "QuicksortST");
            }
        }
        string totalTimeStr = to_string(totalTime/NAVG);
        result += totalTimeStr.substr(0,totalTimeStr.find(".")+4) + " " ;

    }
    cout << "size " + rangTitle << endl;
    cout << "time " + result + "s" << endl;
    cout << endl;
    #endif

    // The test of Quicksort with multiple threads
    #ifdef QUICKSORTMTSW
    cout << "QuicksortMT started!" << endl;
    result = "";
    rangTitle = "";
    for (auto i = NMIN; i < NMAX; i *= 10) {
        totalTime = 0;
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            randUint(data, i);
            auto start = chrono::steady_clock::now(); // start time
            quickSortLMT(data, 0, i - 1);
            auto end = chrono::steady_clock::now();
            double middleTime = chrono::duration <double, milli>(end - start).count()/1000;
            totalTime += middleTime;
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            string strTime = to_string(middleTime);
            string eachTime = strTime.substr(0,strTime.find(".")+4) + " ";
            cout << "length " << i << ", " << "Round" << j+1 << " " << eachTime << endl;
            if (j==0) {
                checkOrder(data, i, "QuicksortMT");
            }
        }
        string totalTimeStr = to_string(totalTime/NAVG);
        result += totalTimeStr.substr(0,totalTimeStr.find(".")+4) + " " ;
    }
    cout << "size " + rangTitle << endl;
    cout << "time " + result + "s" << endl;
    cout << endl;
    #endif

    // the test of radix sort with a single thread
    #ifdef RADIXSORTSTSW
    cout << "RadixSortST started!" << endl;
    result = "";
    rangTitle = "";
    for (auto i = NMIN; i < NMAX; i *= 10) {
        totalTime = 0;
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            randUint(data, i);
            auto start = chrono::steady_clock::now(); // start time
            msdRadixSort(data, i);
            auto end = chrono::steady_clock::now();
            double middleTime = chrono::duration <double, milli>(end - start).count()/1000;
            totalTime += middleTime;
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            string strTime = to_string(middleTime);
            string eachTime = strTime.substr(0,strTime.find(".")+4) + " ";
            cout << "length " << i << ", " << "Round" << j+1 << " " << eachTime << endl;
            if (j==0) {
                checkOrder(data, i, "RadixSortST");
            }

        }
        string totalTimeStr = to_string(totalTime/NAVG);
        result += totalTimeStr.substr(0,totalTimeStr.find(".")+4) + " " ;
    }
    cout << "size " + rangTitle << endl;
    cout << "time " + result + "s" << endl;
    cout << endl;
    #endif

    // the test of Quicksort with multiple threads
    #ifdef RADIXSORTMTSW
    cout << "RadixSortMT started!" << endl;
    result = "";
    rangTitle = "";
    for (auto i = NMIN; i < NMAX; i *= 10) {
        totalTime = 0;
        rangTitle += to_string(i) + " ";
        for (auto j = 0; j < NAVG; ++j) {
            randUint(data, i);
            auto start = chrono::steady_clock::now(); // start time
            msdRadixSortLMT(data, i);
            auto end = chrono::steady_clock::now();
            double middleTime = chrono::duration <double, milli>(end - start).count()/1000;
            totalTime += middleTime;
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            string strTime = to_string(middleTime);
            string eachTime = strTime.substr(0,strTime.find(".")+4) + " ";
            cout << "length " << i << ", " << "Round" << j+1 << " " << eachTime << endl;
            if (j==0) {
                checkOrder(data, i, "RadixSortMT");
            }
        }
        string totalTimeStr = to_string(totalTime/NAVG);
        result += totalTimeStr.substr(0,totalTimeStr.find(".")+4) + " " ;
    }
    cout << "size " + rangTitle << endl;
    cout << "time " + result + "s"<< endl;
    cout << endl;
    #endif

    return 0;
}

