#include "errCheck.h"
#include <stdio.h>

char errNum(int vertex, const int edge) {
    if (vertex < 0 || vertex > MAX) {
        printf("bad number of vertices");
        return 1;
    }
    if (edge < 0 || edge > (vertex * (vertex - 1) / 2)) {
        printf("bad number of edges");
        return 1;
    }
    return 0;
}

char err(const int j, const int k, const int vertex) {
    if ((j <= 0 || j > vertex) || (k <= 0 || k > vertex)) {
        printf("bad vertex");
        return 1;
    }
    if (j == k) {
        printf("impossible to sort");
        return 1;
    }
    return 0;
}
