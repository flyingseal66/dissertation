//
// Created by bubble on 2019/6/28.
//

#include "quicksortLST.h"
using namespace std;

void quickSortLST(UINT64 arr[], UINT64 left, UINT64 right) {
    UINT64 i = left, j = right;
    UINT64 tmp;
    UINT64 pivot = arr[right];
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j) {
        quickSortLST(arr, left, j);
    }
    if (i < right) {
        quickSortLST(arr, i, right);
    }

}