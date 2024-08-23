#include <stdlib.h>
#include <stdio.h>
#include "topSort.h"
#include "errCheck.h"

void freeMatrix(char **adjacencyMat, const int vertex) {
    for (int i = 0; i < vertex; i++) {
        free(adjacencyMat[i]);
    }
    free(adjacencyMat);
}

int main() {
    int vertex, edge;
    if (scanf("%d %d", &vertex, &edge) != 2) {
        printf("bad number of lines");
        return 0;
    }
    if (errNum(vertex, edge) == 1) {
        return 0;
    }
    char **adjacencyMat = malloc(vertex * sizeof(char *));
    if (adjacencyMat != NULL) {
        for (int i = 0; i < vertex; i++) {
            adjacencyMat[i] = calloc(LEN, sizeof(char));
            if (adjacencyMat[i] == NULL) {
                freeMatrix(adjacencyMat, i);
                return 0;
            }
        }
        for (int i = 0; i < edge; i++) {
            int j, k;
            if (scanf("%d %d", &j, &k) != 2 || err(j, k, vertex)) {
                printf("bad number of lines");
                freeMatrix(adjacencyMat, vertex);
                return 0;
            }
            j = j - 1;
            k = k - 1;
            adjacencyMat[k][j / 8] |= (1 << (j % 8));
        }
        int *answer = calloc(vertex, sizeof(int));
        if (TopSort(adjacencyMat, vertex, answer)) {
            for (int k = 0; k < vertex; k++) {
                printf("%i ", answer[k]);
            }
        } 
        else {
            printf("impossible to sort");
        }
        free(answer);
    }
    freeMatrix(adjacencyMat, vertex);
    return 0;
}
