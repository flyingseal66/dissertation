//
// Created by bubble on 2019/6/28.
//

#include "RadixSortST.h"
#include <iostream>
#include <math.h>
using namespace std;
const size_t RANGE = 257;

void printVectorS(int* mas, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << mas[i] << " ";
    }
    printf("\n");
}

// this method is used for get the value of radix position of a number, which can be 1 or 0
int digitS(int num, int radix) {
    /*int t_num = 1;
    for (int i = 0; i < radix; ++i) {
        num = num >> 1;
    }
    num = num & t_num;*/
    return (long)(num / pow(256, radix)) % 256;
}

// copy data from temp to result
void copyDataS(int *t_mas, int* mas, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        mas[i] = t_mas[i];
    }
}


// sort the array for according to the radix position
void countingSortS(int* mas, size_t n, int radix) {
    /*if(n == 2)
    {
        cout << "print:" << radix << endl;
        printVector(mas, n);
    }*/

    //if (n <= 2) return;
    size_t i;
    int count[RANGE] = { 0 };


    for (i = 0; i < n; ++i) {
        ++count[digitS(mas[i], radix) + 1];
    }

    for (i = 1; i < RANGE; ++i) {
        count[i] += count[i - 1];
    }

    int *t_mas = new int[n];

    for (i = 0; i < n; ++i) {
        t_mas[count[digitS(mas[i], radix)]++] = mas[i];
    }
    memcpy((void*)mas, (void*)t_mas, n * sizeof(int));


    //std::copy(t_mas, t_mas+n, mas);
    //memmove(mas, t_mas, sizeof(int)*n);
    //printVector(mas, n);
    //delete[]t_mas;
    //delete[]count;
}


void msdRadixPassS(int* mas, size_t n, int radix) {
    if (n < 2) {
        return;
    }
    if (radix < 0) {
        return;
    }
    countingSortS(mas, n, radix);
    //printVector(mas, n);
    bool flag = true;
    int start = 0;
    for (int i = 0; i < (n - 1); ++i) {
        if (digitS(mas[i], radix) != digitS(mas[i + 1], radix)) {
            msdRadixPassS(&mas[start], (i - start + 1), radix - 1);
            start = i + 1;
            //printVector(mas, n);
            flag = false;
        }
    }
    if (flag) {
        msdRadixPassS(mas, n, radix - 1);

    }else {
        msdRadixPassS(&mas[start], (n - start), radix - 1);
    }
}

void msdRadixSortS(int* mas, int n) {
    msdRadixPassS(mas, n, 1);
}