#include <stdio.h>
#include <stdlib.h>
#include "dsu.h"
#include "kruskal.h"

int backParent(const int vertex, int * parent) {
    if (parent[vertex] != -1) {
        return backParent(parent[vertex], parent);
    }
    return vertex;
}


int compare(const void * one, const void * two) {
    return ((par*)one)->len - ((par*)two)->len;
}

void kruskal(par* edgePar, const int edge, int vertex) {
    DSU *dsu = cdsu(vertex);
    if (dsu != NULL) {
        par* result = malloc((vertex - 1) * sizeof(par));
        if (result != NULL) {
            qsort(edgePar, edge, sizeof(par), compare);
            int newEdge = 0;
            for (int i = 0; newEdge < vertex - 1 && i < edge; i++) {
                par current = edgePar[i];
                int start = backParent(current.start, dsu->parent);
                int end = backParent(current.end, dsu->parent);
                if (start != end) {
                    result[newEdge++] = current;
                    dsuUnion(start, end, dsu);
                }
            }
            for (int i = 0; i < vertex - 1; i++) {
                if ((result+i)->start >= (result+i)->end) {
                    printf("%d %d\n", (result+i)->end + 1, (result+i)->start + 1);
                }
                else {
                    printf("%d %d\n", (result+i)->start + 1, (result+i)->end + 1);
                }                
            }
            free(result);
        }
        freedsu(dsu);
    }
}
