#include "topSort.h"
#include <stdlib.h>
#include <stdio.h>

char isEmpty(char **adjacencyMat, const int vertex) {
    for (int horizontal = 0; horizontal < LEN; horizontal++) {
        if (adjacencyMat[vertex][horizontal] != 0) {
            return 0;
        }
    }
    return 1;
}

char TopSort(char **adjacencyMat, const int vertex, int *answer) {
    char *markers = calloc(vertex, sizeof(char));
    if (markers == NULL) {
        return 0;
    }
    int c = 0;
    while (1) {
        char flag = 0;
        for (int k = 0; k < vertex; k++) {
            if (isEmpty(adjacencyMat, k) && !markers[k]) {
                answer[c++] = k + 1;
                markers[k] = 1;
                if (c == vertex) {
                    free(markers);
                    return 1;
                }
                for (int j = 0; j < vertex; j++) {
                    adjacencyMat[j][k / 8] &= ~(1 << (k % 8));
                }
                flag = 1;
            }
        }
        if (flag == 0) {
            free(markers);
            return 0;
        }
    }
}
