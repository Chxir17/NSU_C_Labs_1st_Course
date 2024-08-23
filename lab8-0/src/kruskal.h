#ifndef KRUSKAL
#define KRUSKAL

typedef struct parametersOfEdge {
    int len;
    int start;
    int end;
} par;

void kruskal(par* edgePar, const int edge, int vertex);

#endif
