#include <stdio.h>
#include <stdlib.h>
#include "convexHull.h"

int main() {
    int pointsCount; 
    if (scanf("%d", &pointsCount) != 1) {
        return 0;
    }
    if (pointsCount < 0 || pointsCount > 100000) {
        printf("bad number of points");
        return 0;
    }
    hull *convexHull = malloc(sizeof(hull));
    if (convexHull == NULL){
		return 0;
	}
    convexHull->hullSize = pointsCount;
    convexHull->points = malloc(pointsCount * sizeof(cord *));
    if (convexHull->points == NULL) {
        freeH(convexHull);
        return 0;
    }
    for (int i = 0; i < pointsCount; i++) {
        cord *point = malloc(sizeof(cord));
        if (point == NULL) {
            convexHull->hullSize = i;
            freeH(convexHull);
            return 0;
        }
        if (scanf("%d %d", &point->x, &point->y) != 2) {
            printf("bad number of lines");
            free(point);
            convexHull->hullSize = i; 
            freeH(convexHull);
            return 0;
        }
        convexHull->points[i] = point;
    }
    find(convexHull);
    return 0;
}
