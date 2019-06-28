//
// Created by bubble on 2019/6/28.
//

#include "quicksortMT.h"
#include <thread>

void quickSortMT(int arr[], int left, int right) {
    //cnt++;
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot) {
            //cout << "quick sort i:" << i << endl;
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        //j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    std::thread t1;
    if (i < right) {
        if ((i + 600000 < right)) {
            t1 = std::thread(quickSortMT, arr, i, right); // create new thread
        }
        else {
            quickSortMT(arr, i, right);
        }

    }
    /* recursion */
    if (left < j) {
        quickSortMT(arr, left, j); //original code
    }

    if (t1.joinable()) {
        t1.join();
    }
}