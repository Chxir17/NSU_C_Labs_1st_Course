#include <stdlib.h>
#include "dsu.h"

DSU *cdsu(int vertex) {
    DSU *dsu = malloc(sizeof(DSU));
    if (dsu != NULL) {
        dsu->parent = malloc(vertex * sizeof(int));
        if (dsu->parent != NULL) {
            for (int i = 0; i < vertex; ++i) {
                dsu->parent[i] = -1;
            }
            return dsu;
        } else {
            free(dsu);
        }
    }
    return NULL;
}

int fdsu(int vertex, DSU *dsu) {
    if (dsu->parent[vertex] != -1) {
        return fdsu(dsu->parent[vertex], dsu);
    }
    return vertex;
}

void dsuUnion(int x, int y, DSU *dsu) {
    int root_x = fdsu(x, dsu);
    int root_y = fdsu(y, dsu);
    if (root_x != root_y) {
        dsu->parent[root_x] = root_y;
    }
}

void freedsu(DSU *dsu) {
    free(dsu->parent);
    free(dsu);
}
