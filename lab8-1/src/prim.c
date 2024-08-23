#include <stdio.h>
#include <stdlib.h>
#include "prim.h"

par *findEdge(par *edgePar, char *used, int edge) {
	for (int i = 0; i < edge; i++) {
		if (used[(edgePar + i)->end - 1] + used[(edgePar + i)->start - 1] == 1) {
			used[(edgePar + i)->end - 1] = 1;
			used[(edgePar + i)->start - 1] = 1;
			return edgePar + i;
		}
	}
	return NULL;
}

int compare(const void *one, const void *two) {
	return ((par *)one)->len - ((par *)two)->len;
}

void prim(par *edgePar, int vertex, const int edge) {
	char *used = calloc(vertex, sizeof(char));
	if (used == NULL) {
		return;
	}
	used[0] = 1;
	par *ans = malloc(vertex * sizeof(par));
	if (ans == NULL) {
		free(used);
		return;
	}
	qsort(edgePar, edge, sizeof(par), compare);
	par *cur = findEdge(edgePar, used, edge);
	int position = 0;
	for (; cur != NULL; position++) {
		ans[position] = *cur;
		cur = findEdge(edgePar, used, edge);
	}
	if (position == vertex - 1) {
		for (int i = 0; i < position; i++) {
			printf("%d %d\n", (ans + i)->start, (ans + i)->end);
		}
	}
	else {
		printf("no spanning tree");
	}
	free(ans);
	free(used);
}
