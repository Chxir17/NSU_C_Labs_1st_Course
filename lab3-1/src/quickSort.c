#include "quickSort.h"

void swap(int *num1, int *num2) {
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

void Qsort(int *arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(arr + i, arr + j);
            i++;
            j--;
        }
    }
    if (left < j) {
        Qsort(arr, left, j);
    }
    if (i < right) {
        Qsort(arr, i, right);
    }
}

void quickSort(int *arr, int arrLen) {
    Qsort(arr, 0, arrLen-1);
}
