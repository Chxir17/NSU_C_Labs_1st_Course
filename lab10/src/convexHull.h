#ifndef CONVEXHULL_H
#define CONVEXHULL_H

typedef struct cordinates {
    int x;
    int y;
} cord;

typedef struct hull {
    cord **points;
    int hullSize;
} hull;


void find(hull *convexHull);
void freeH(hull *convexHull);

#endif
