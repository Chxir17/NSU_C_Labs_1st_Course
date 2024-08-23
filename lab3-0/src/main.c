#include <stdio.h>
#include <stdlib.h>

void swap(int *num1, int *num2){
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

void heapify(int *arr, int arrLen, int i){
    int root = i, lNode = 2*i + 1, rNode = 2*i + 2;
    if (lNode < arrLen && arr[lNode] > arr[root]){
        root = lNode;
    }
    if (rNode < arrLen && arr[rNode] > arr[root]){
        root = rNode;
    }
    if (root != i){
        swap(arr + i, arr + root);
        heapify(arr, arrLen, root);
    }
}

void heapSort(int *arr, int arrLen){
    for (int i = arrLen/2; i >= 0; i--){
        heapify(arr, arrLen, i);
    }
    for (int i = arrLen - 1; i >= 0; i--){
        swap(arr, arr + i);
        heapify(arr, i, 0);
    }
}

int main() {
    int arrLen;
    if (scanf("%d", &arrLen) == 1) {
        int *arr = malloc(arrLen * sizeof(int));
        if (arr != NULL && arrLen != 0) {
            for (int i = 0; i < arrLen; i++) {
                if (scanf("%d", &arr[i]) != 1) {
                    return 0;
                }
            }
            heapSort(arr, arrLen);
            for (int i = 0; i < arrLen; i++) {
                printf("%d ", arr[i]);
            }
        }
        free(arr);
    }
    return 0;
}
