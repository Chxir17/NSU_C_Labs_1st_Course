#include <stdio.h>
#include <stdlib.h>
#include "prim.h"
#include "errCheck.h"

int main() {
	int edge, vertex;
	if (scanf("%d %d", &vertex, &edge) != 2) {
		printf("bad number of lines");
		return 0;
	}
	if (errNum(vertex, edge) == 1 || vertex == 1) {
		return 0;
	}
	par *edgePar = malloc((edge + 1) * sizeof(par));
	if (edgePar != NULL) {
		for (int i = 0; i < edge; i++) {
			long long lenn;
			if (scanf("%d %d %lld", &edgePar[i].start, &edgePar[i].end, &lenn) != 3) {
				printf("bad number of lines");
				free(edgePar);
				return 0;
			}
			if (err(edgePar, vertex, i, lenn) == 1) {
				free(edgePar);
				return 0;
			}
			edgePar[i].len = (int)lenn;
		}
		prim(edgePar, vertex, edge);
	}
	free(edgePar);
	return 0;
}
