#include <limits.h>
#include <stdio.h>
#include "errCheck.h"

int errNum(const int vertex, const int edge) {
    if (vertex < 0 || vertex > MAX) {
        printf("bad number of vertices");
        return 1;
    }
    if (edge < 0 || edge > ((vertex * (vertex + 1)) / 2)) {
        printf("bad number of edges");
        return 1;
    }
    if (vertex == 0 || (vertex > 1 && edge == 0)) {
        printf("no spanning tree");
        return 1;
    }
    return 0;
}

int err(par *edgePar, const int vertex, const int i, const long long lenn) {
    if (lenn < 0 || lenn > INT_MAX) {
        printf("bad length");
        return 1;
    }
    if ((edgePar+i)->start < 1 || (edgePar+i)->start > vertex) {
        printf("bad vertex");
        return 1;
    }
    if ((edgePar+i)->end < 1 || (edgePar+i)->end > vertex){
        printf("bad vertex");
        return 1;
    }
    return 0;
}
