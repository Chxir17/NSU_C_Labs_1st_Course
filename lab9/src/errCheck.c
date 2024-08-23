#include "errCheck.h"
#include <limits.h>
#include <stdio.h>

int errNum(const int vertex, const int start, const int finish, const int edge) {
    if (vertex < 0 || vertex > MAX) {
        printf("bad number of vertices");
        return 1;
    }
    if (start < 1 || start > vertex || finish < 1 || finish > vertex) {
        printf("bad vertex");
        return 1;
    }
    if (edge < 0 || edge > ((vertex * (vertex + 1)) / 2)) {
        printf("bad number of edges");
        return 1;
    }
    return 0;
}

int err(const int vertex, const int edgeStart, const int edgeEnd, const long long edgeLen) {
    if (edgeStart < 1 || edgeStart > vertex || edgeEnd < 1 || edgeEnd > vertex) {
        printf("bad vertex");
        return 1;
    }
    if (edgeLen <= 0 || edgeLen > INT_MAX) {
        printf("bad length");
        return 1;
    }
    return 0;
}
