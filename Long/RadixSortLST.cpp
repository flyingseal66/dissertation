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
int THREAD_NUMBER = 2;

atomic<int> _counter(0);  //使用原子变量

void printVector(UINT64* mas, int n) {
    for (int i = 0; i < n; ++i) {
        cout << mas[i] << " ";
    }
    printf("\n");
}

// this method is used for get the value of radix position of a number, which can be 1 or 0
int digit(UINT64 num, int radix) {
    return (long long)(num/pow(256, radix)) % 256;
}

// this method is used to get the number of each bucket
void countDigits(int* count, UINT64* mas, int radix, int start, int end)
{
    for (int i = start; i < end; ++i) {
        ++count[digit(mas[i], radix) + 1];
    }
}

// move data in parallel
void moveData(UINT64 *t_mas, int* count, UINT64* mas, int start, int end, int t_id, int radix)
{
    for (int i = start; i < end; ++i)
    {
        t_mas[(count[digit(mas[i], radix)]++) + t_id] = mas[i];
    }
}

// copy data from temp to result
void copyData(const UINT64 *t_mas, UINT64 * mas, int start, int end)
{
    for (int i = start; i< end; i ++)
    {
        mas[i] = t_mas[i];
    }
}


// sort the array for according to the radix position
void countingSort(UINT64* mas, UINT64 n, int radix) {
    //if (n <= 2) return;
    UINT64 i;
    int count[RANGE] = { 0 };
    int count0[RANGE] = { 0 };
    int count1[RANGE] = { 0 };
    int startPos[RANGE] = { 0 };
    thread t0, t1;
    /*if (n > 400000000) {
        for (i = 0; i < THREAD_NUMBER; ++i)
        {
            if (i == 0)
            {
                t0 = std::thread(countDigits, count0, mas, radix, (i * average), ((i + 1)*average));
            }

            if (i == 1)
            {
                t1 = std::thread(countDigits, count1, mas, radix, (i * average), n);
            }
        }
        if (t0.joinable()) {
            t0.join();
        }
        if (t1.joinable()) {
            t1.join();
        }
        for (i = 0; i < RANGE; ++i)
        {
            count[i] = count0[i] + count1[i];
        }
    }
    else
    {
        for (i = 0; i < n; ++i) {
            ++count[digit(mas[i], radix) ];
        }
    }*/
    for (i = 0; i < n; ++i) {
        ++count[digit(mas[i], radix)+1];
    }

    /*for (i = 0; i < n; ++i) {
        ++count[digit(mas[i], radix) + 1];
    }*/
    for (i = 1; i < RANGE; ++i) {
        count[i] += count[i - 1];
    }

    // confirm the start of each position
    /*for (i = 0; i < RANGE; ++i)
    {
        count1[i] += count0[i];
    }*/

    auto *t_mas = new UINT64[n];
    /*for (i = 0; i < THREAD_NUMBER; ++i)
    {
        if (i == 0)
        {
            moveData(t_mas, count, mas, 0, (i + 1)*average, i, radix);
        }
        else if (i==1)
        {
            moveData(t_mas, count, mas, i*average, (i + 1)*average, count[i], radix);
        }

    }*/

    for (i = 0; i < n; ++i) {
        t_mas[count[digit(mas[i], radix)]++] = mas[i];
    }

    for (i = 0; i < n; i++) {
        mas[i] = t_mas[i];
    }

    // copy data in parallel
    std::thread t4,t5,t6;
    /*if (_counter < 8 && n>500000000 && 1>2)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0)
            {
                t4 = std::thread{ copyData, t_mas, mas, j*n / 2, (j + 1)*(n / 2) };
                _counter++;
                //	std::cout << "result:=" << _counter << std::endl;
                //cout << 1 << endl;
            }
            if (j == 1)
            {
                //	t5 = std::thread(copyData, t_mas, mas, j*n / 2, n);
                copyData(t_mas, mas, j*n / 2, n);
                //	cout << 2 << endl;
            }
            *//*if (j == 2)
            {
                t6 = std::thread(copyData, t_mas, mas, j*n / 3, n);
            }*//*
            *//*if (j == 2)
            {
                t6 = std::thread(copyData, t_mas, mas, j*n / 3, n);
            }*//*
        }
        if (t4.joinable()) {
            t4.join();
            _counter--;
        }
        //	if (t5.joinable()) {
        //	t5.join();
        //}
        *//*if (t6.joinable()) {
            t6.join();
        }*//*

    }
    else {
        for (i = 0; i < n; ++i) {
            mas[i] = t_mas[i];
        }
        //memcpy((void*)mas, (void*)t_mas, n * sizeof(UINT64));
    }*/

    //std::cout << "result:=" << _counter << std::endl;

    //std::copy(t_mas, t_mas+n, mas);
    //memmove(mas, t_mas, sizeof(TUint64)*n);

    //memcpy(mas, t_mas, n);
    //*mas = *t_mas;



    //cout << "print:" << radix << endl;
    //printVector(mas, n);
    delete[]t_mas;
    //delete[]count;
}


void msdRadixPass(UINT64* mas, UINT64 n, int radix) {
    if (radix < 0) {
        return;
    }
    countingSort(mas, n, radix);
    //printVector(mas, n);
    bool flag = true;
    UINT64 start = 0;
    std::thread t1;
    std::thread t2;
    std::thread t3;
    for (int i = 0; i < (n - 1); ++i) {
        if (digit(mas[i], radix) != digit(mas[i + 1], radix)) {
            if ((i - start +1) > 8000000000) {
                t1 = std::thread(msdRadixPass, &mas[start], (i - start + 1), radix - 1);
            }
            else { msdRadixPass(&mas[start], (i - start + 1), radix - 1); }

            start = i + 1;
            //printVector(mas, n);
            flag = false;
        }
    }
    if (flag) {
        if (50000000000 < n)
        {
            t2 = std::thread(msdRadixPass, mas, n, radix - 1);
        }
        else { msdRadixPass(mas, n, radix - 1); }

    }
    else {
        if (n - start> 7000000000)
        {
            t3 = std::thread(msdRadixPass, &mas[start], (n - start), radix - 1);
        }
        else { msdRadixPass(&mas[start], (n - start), radix - 1); }
        //msdRadixPass(&mas[start], (n - start), radix - 1);
    }
    if (t1.joinable()) {
        t1.join();
    }
    if (t2.joinable()) {
        t2.join();
    }
    if (t3.joinable()) {
        t3.join();
    }
}

void msdRadixSort(UINT64 * mas, UINT64 n) {
    msdRadixPass(mas, n, 7);
}