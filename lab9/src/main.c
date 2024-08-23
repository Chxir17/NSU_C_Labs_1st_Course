#include "errCheck.h"
#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int vertex, start, finish, edge;
    if(scanf("%d %d %d %d", &vertex, &start, &finish, &edge) !=4 ){
        printf("bad number of lines");
        return 0;
    }
    if (errNum(vertex, start, finish, edge) == 1) {
        return 0;
    }
    int size = vertex * vertex;
    unsigned int * len = calloc(size, sizeof(unsigned int));
    if(len == NULL){
        return 0;
    }
    for (int i = 0; i < edge; i++) {
        int edgeStart, edgeEnd;
        long long edgeLen;
        if (scanf("%d %d %lld", &edgeStart, &edgeEnd, &edgeLen) != 3) {
            printf("bad number of lines");
            free(len);
            return 0;
        }
        if(err(vertex, edgeStart, edgeEnd, edgeLen)==1){
            free(len);
            return 0;
        }
        len[vertex * (edgeStart - 1) + (edgeEnd - 1)] = (unsigned int)edgeLen;
        len[vertex * (edgeEnd - 1) + (edgeStart - 1)] = (unsigned int)edgeLen;
    }
    dijkstra(len, vertex, start, finish);
    free(len);
    return 0;
}
