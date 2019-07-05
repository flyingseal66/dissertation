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
const int NAVG = 1;

// Execution switcher
//#define QUICKSORTSTSW
//#define QUICKSORTMTSW
#define RADIXSORTSTSW
#define RADIXSORTMTSW
typedef unsigned long long UINT64;

using namespace std;

// generate an UINT64 array with a length of size
void randUint(UINT64 *data, UINT64 size) {
    UINT64 r = 2;
    for (UINT64 k = 0; k < size; k++) {
        r ^= r >> 12;        // a
        r ^= r << 25;        // b
        r ^= r >> 27;        // c
        data[k] = r;
    }
}

void rand64Bit(UINT64 *data, UINT64 size) {
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
    //and seed it with entropy.

    //Define the distribution, by default it goes from 0 to MAX(unsigned long long)
    //or what have you.
    std::uniform_int_distribution<unsigned long long> distr;

    //Generate random numbers
    for(int n=0; n<size; n++) {
        data[n] = distr(eng);
        // std::cout << distr(eng) << ' ';
    }

}


// check the sorted array of data to see if there are numbers in wrong order
void checkOrder(UINT64 *data, UINT64 i, const string& sortType) {
    for (UINT64 j = 1; j < i; j++) {
        if (data[j] < data[j - 1]) {
            std::cout << "Wrong order is found in " << sortType << ": " << j << " " << data[j] << " " << data[j - 1] << std::endl;
        }
    }
}
int main() {
    auto testStart = chrono::steady_clock::now(); // start time
    for (int k = 0; k < 100000000; ++k) {
        cout << digit(5542065385077511953, 0) <<endl;
        cout << digit(5542065385077511967, 0) << endl;
        //Sleep(100000);
    }
    /*auto testEnd = chrono::steady_clock::now(); // start time
    cout <<"ini time " << chrono::duration <double, milli>(testEnd - testStart).count()/1000 << "s" << endl;

    //cout << digit(10188706241164381559, 1) << endl;
    //cout << digit(10188706241164383079 ,1) <<endl;
    //Sleep(100000);
*/

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
    for (UINT64 i = NMIN; i < NMAX; i *= 10) {
        string eachSize = "";
        result = "";
        totalTime = 0;
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            auto initStart = chrono::steady_clock::now(); // start time
            randUint(data, i); // initialise data
            auto initEnd = chrono::steady_clock::now(); // start time
            cout << "size: " << i << ", initialization time " << chrono::duration <double, milli>(initEnd - initStart)
                    .count()/1000 << "s" << endl;
            auto start = chrono::steady_clock::now(); // start time
            quickSortLST(data, 0, i - 1);
            auto end = chrono::steady_clock::now();
            double middleTime = chrono::duration <double, milli>(end - start).count()/1000;
            totalTime += middleTime;
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            string strTime = to_string(middleTime);
            string eachTime = strTime.substr(0,strTime.find(".")+4) + " ";
            eachSize += eachTime;
            if (j == 0) {
                checkOrder(data, i, "QuicksortST");
            }
        }
        string totalTimeStr = to_string(totalTime/NAVG);
        result += totalTimeStr.substr(0,totalTimeStr.find(".")+4) + " " ;
        cout << "size: " << i << " " << eachSize << "avg=" << result << endl;
    }
    cout << endl;
    #endif

    // The test of Quicksort with multiple threads
    #ifdef QUICKSORTMTSW
    cout << "QuicksortMT started!" << endl;
    rangTitle = "";
    for (UINT64 i = NMIN; i < NMAX; i *= 10) {
        string eachSize = "";
        result = "";
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
            eachSize += eachTime;
            if (j==0) {
                checkOrder(data, i, "QuicksortMT");
            }
        }
        string totalTimeStr = to_string(totalTime/NAVG);
        result += totalTimeStr.substr(0,totalTimeStr.find(".")+4) + " " ;
        cout << "size: " << i << " " << eachSize << "avg=" << result << endl;
    }
    cout << endl;
    #endif

    // the test of radix sort with a single thread
    #ifdef RADIXSORTSTSW
    cout << "RadixSortST started!" << endl;
    rangTitle = "";
    for (auto i = NMIN; i < NMAX; i *= 10) {
        string eachSize = "";
        result = "";
        totalTime = 0;
        rangTitle += to_string(i) + " ";
        for (int j = 0; j < NAVG; ++j) {
            rand64Bit(data, i);
            auto start = chrono::steady_clock::now(); // start time
            msdRadixSort(data, i);
            auto end = chrono::steady_clock::now();
            double middleTime = chrono::duration <double, milli>(end - start).count()/1000;
            totalTime += middleTime;
            //cout <<"Array size " << i << ", Time " << chrono::duration <double, milli>(end - start).count() << " ms" << endl;
            string strTime = to_string(middleTime);
            string eachTime = strTime.substr(0,strTime.find(".")+4) + " ";
            eachSize += eachTime;
            if (j==0) {
                checkOrder(data, i, "RadixSortST");
            }

        }
        string totalTimeStr = to_string(totalTime/NAVG);
        result += totalTimeStr.substr(0,totalTimeStr.find(".")+4) + " " ;
        cout << "size: " << i << " " << eachSize << "avg=" << result << endl;
    }
    cout << endl;
    #endif

    // the test of Quicksort with multiple threads
    #ifdef RADIXSORTMTSW
    cout << "RadixSortMT started!" << endl;
    rangTitle = "";
    for (auto i = NMIN; i < NMAX; i *= 10) {
        string eachSize = "";
        result = "";
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
            eachSize += eachTime;
            if (j==0) {
                checkOrder(data, i, "RadixSortMT");
            }
        }
        string totalTimeStr = to_string(totalTime/NAVG);
        result += totalTimeStr.substr(0,totalTimeStr.find(".")+4) + " " ;
        cout << "size: " << i << " " << eachSize << "avg=" << result << endl;
    }
    cout << endl;
    #endif

    return 0;
}

