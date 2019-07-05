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



// print array
void printVector(UINT64 * mas, int n) {
    for (int i = 0; i < n; ++i) {
        cout << mas[i] << " ";
    }
    printf("\n");
    cout << "end print" << endl;
}

// this method is used for get the value of radix position of a number, which can be 0-255
int digit(UINT64 num, int radix) {
    UINT64 t_num = 255;
    if(num != 0) {
        for(int i = 0; i < radix; i++) {
            num = (num >> 8);
        }
    }
    return (num & t_num);
}

// sort the array for according to the radix position
void countingSort(UINT64* mas, UINT64 n, int radix, UINT64 *bucks) {
    //if (n <= 2) return;
    UINT64 i;
    UINT64 count[RANGE] = { 0 };

    // count the number of each bucket
    for (i = 0; i < n; ++i) {
        ++count[digit(mas[i], radix)+1];
    }
    bucks[0] = count[0];
    for (int m = 1; m < RANGE; ++m) {
        count[m] += count[m - 1];
        bucks[m] = count[m];
        //cout << "m" << m << buckets[i] << endl;
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
    //printVector(count, n);
    delete[]t_mas;
}

// sort the array by radix
void msdRadixPass(UINT64* mas, UINT64 n, int radix) {
    if (n<2) return;
    if (radix <= 0) {
        return;
    }
    auto *buckets = new UINT64[RANGE]();
    countingSort(mas, n, radix, buckets);
    //printVector(mas, n);
    //bool flag = true;
    UINT64 start = 0;
    for (int j = 0; j < RANGE; j++) {
        //cout<< "j: " << j<<endl ;
        UINT64 diff = 0;
        if (j > 0) {
            //cout << "buckets: " << buckets[j] << " " << buckets[j-1]<< endl;
            diff = buckets[j] - buckets[j-1];

        }
        //if (j != 0 && diff == 0) return;
        if (((j == 0 && buckets[0] > 1) || diff > 0)) {
            //cout << "diff " << diff <<endl;
            if(j==0) {
                msdRadixPass(&mas[start], buckets[0], radix - 1);
                start = buckets[0];
            } else {
                msdRadixPass(&mas[start], diff, radix - 1);
                start = buckets[j];
            }


            //cout << "start " << start << " radix " << radix - 1 << "diff" << diff << endl;
        }


    }
    /*for (int i = 0; i < (n - 1); ++i) {
        if (digit(mas[i], radix) != digit(mas[i + 1], radix)) {
            msdRadixPass(&mas[start], (i - start + 1), radix - 1);
            start = i + 1;
            flag = false;
        }
    }*/

    /*if (flag) {

            //msdRadixPass(mas, n, radix - 1);

        //cout<<"flag: "<< flag<< " n"<< n <<" start" << start <<endl;

    } else {
        //cout<<"flag: "<< flag<< "n" << n <<  " start " << start<<endl;
        if (n > start) {
            //msdRadixPass(&mas[start], (n - start), radix - 1);
        }

    }
*/
    delete []buckets;
}

void msdRadixSort(UINT64 * mas, UINT64 n) {
    msdRadixPass(mas, n, 7);
}