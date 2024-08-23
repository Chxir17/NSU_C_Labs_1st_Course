#ifndef PRIM
#define PRIM

typedef struct parametersOfEdge {
    int len;
    int start;
    int end;
} par;

void prim(par* edgePar, int vertex, const int edge);

#endif
