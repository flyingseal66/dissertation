#include <iostream>
#include <ctime>
#include "quicksortShortSingle.h"

using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;

    int len = 100000000;
    int  *data = new int[len];
    clock_t startTime, endTime;

    srand((unsigned)time(NULL));
    for (int i = 0; i < len; i++)
    {
        data[i] =rand();
    }

    srand((unsigned)time(NULL));
    /*for (int i = 0; i < len; i++)
    {
        data[i] = rand();
    }*/


    startTime = clock();// start time
    quickSort(data, 0, len - 1);
    //sort(data, data+ len);
    endTime = clock();//end time
    cout << "The quicksortShort2 run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s " << endl;
    //cout << "total cnt" << cnt << endl;
    //std::copy(data, data + (sizeof(data) / sizeof(*data)), std::ostream_iterator<int>(std::cout, " "));
    for (int i = 1; i < len; i++) {
        if (data[i] < data[i - 1]) {
            std::cout << "Wrong order is found in Radix sort MSD:" << i << " " << data[i] << " " << data[i - 1] << std::endl;
        }
    }

    return 0;
}