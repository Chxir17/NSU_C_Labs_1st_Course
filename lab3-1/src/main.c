#include <stdlib.h>
#include <stdio.h>
#include "quickSort.h"

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
            quickSort(arr, arrLen);
            for (int i = 0; i < arrLen; i++) {
                printf("%d ", arr[i]);
            }
        }
        free(arr);
    }
    return 0;
}
