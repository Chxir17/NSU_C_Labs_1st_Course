#ifndef DSU_H
#define DSU_H

typedef struct Dsu {
    int *parent;
} DSU;

DSU *cdsu(int vertex);
int fdsu(int vertex, DSU *dsu);
void dsuUnion(int x, int y, DSU *dsu);
void freedsu(DSU *dsu);

#endif
