#include "convexHull.h"
#include <stdio.h>
#include <stdlib.h>

void freeH(hull *convexHull) {
    for (int i = 0; i < convexHull->hullSize; i++) {
        free(convexHull->points[i]);
    }
    free(convexHull->points);
    free(convexHull);

}

double place(cord *p1, cord *p2, cord *p3) {
    return ((double)p3->y - p1->y) * ((double)p2->x - p1->x) - ((double)p3->x - p1->x) * ((double)p2->y - p1->y);
}

int compare(const void *x, const void *y) {
    const cord *first = *(const cord **)x;
    const cord *second = *(const cord **)y;
    return (first->x > second->x) || (first->x == second->x && first->y > second->y);
}

void find(hull *convexHull) {
    if (convexHull->hullSize == 1) {
    	for (int i = 0; i < convexHull->hullSize; i++) {
        	printf("%d %d\n", convexHull->points[i]->x, convexHull->points[i]->y);
    	}
        freeH(convexHull);
        return;
    }
    qsort(convexHull->points, convexHull->hullSize, sizeof(cord *), compare);
	hull *end = malloc(sizeof(hull));
    if (end == NULL) {
        freeH(convexHull);
        return;
    }
	end->hullSize = convexHull->hullSize * 2;
    end->points = malloc(convexHull->hullSize * 2 * sizeof(cord *));
    if (end->points == NULL) {
		freeH(convexHull);
		free(end); 
	}
    int j = 0;
    for (int i = 0; i < convexHull->hullSize; i++) {
        while (j >= 2 && place(end->points[j - 2], end->points[j - 1], convexHull->points[i]) <= 0)
            j--;
        end->points[j++] = convexHull->points[i];
    }

    for (int i = convexHull->hullSize - 2, k = j + 1; i >= 0; i--) {
        while (j >= k && place(end->points[j - 2], end->points[j - 1], convexHull->points[i]) <= 0)
            j--;
        end->points[j++] = convexHull->points[i];
    }
    end->hullSize = j - 1;
    for (int i = 0; i < end->hullSize; i++) {
        printf("%d %d\n", end->points[i]->x, end->points[i]->y);
    }
    free(end->points);  
    free(end);          
    freeH(convexHull);
}

