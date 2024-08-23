#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

typedef struct neparametres {
    char * used;
    short int * parent;
    unsigned int* minimal;
} neparametres;

int create(neparametres *par, const int vertex) {
	par->used = calloc(vertex, sizeof(char));
	if (par->used == NULL) {
		return 1;
	}
	par->minimal = malloc(sizeof(unsigned int) * vertex);
	if (par->minimal == NULL) {
		return 1;
	}
	for (int i = 0; i < vertex; ++i) {
		par->minimal[i] = UINT_MAX;
	}
	par->parent = malloc(sizeof(short int) * vertex);
	if (par->parent == NULL) {
		return 1;
	}
	return 0;
}

void freeS(neparametres *par) {
	free(par->used);
	free(par->parent);
	free(par->minimal);
	free(par);
}

int distance(neparametres *par, const int vertex, const int start, const int finish, unsigned int *len) {
	for (int i = 0; i < vertex; i++) {
		if (par->used[i] == 0) {
			printf("oo ");
		}
		else {
			if (par->minimal[i] <= INT_MAX) {
				printf("%u ", par->minimal[i]);
			}
			else {
				printf("INT_MAX+ ");
			}
		}
	}
	printf("\n");
	if (par->used[finish - 1] == 0) {
		printf("no path");
		return 0;
	}
	int maxCounter = 0;
	for (int i = 0; i < vertex; i++) {
		if (par->minimal[i] <= INT_MAX) {
			continue;
		}
		if (par->minimal[i] == UINT_MAX) {
			continue;
		}
		maxCounter++;
		for (int j = i; j < vertex; ++j) {
			if (len[vertex * i + j]) {
				maxCounter++;
			}
		}
	}
	if (maxCounter >= 2 && par->minimal[finish - 1] > INT_MAX) {
		printf("overflow");
		return 0;
	}
	for (int from = finish - 1; from != start - 1; from = par->parent[from]) {
		printf("%d ", from + 1);
	}
	printf("%d", start);
	return 0;
}

void updateDistances(neparametres *par, const int v, const int vertex, unsigned int *len) {
	for (int to = 0; to < vertex; to++) {
		if (len[vertex * v + to] == 0) {
			continue;
		}
		if (len[vertex * v + to] + par->minimal[v] < par->minimal[to] && !par->used[to]) {
			if (len[vertex * v + to] + par->minimal[v] > INT_MAX) {
				par->minimal[to] = UINT_MAX - 1;
			}
			else {
				par->minimal[to] = len[vertex * v + to] + par->minimal[v];
			}
			par->parent[to] = v;
		}
	}
}

int dijkstra(unsigned int *len, const int vertex, const int start, const int finish) {
	neparametres *par = malloc(sizeof(neparametres));
	if (par == NULL) {
		return 0;
	}
	create(par, vertex);
	par->minimal[start - 1] = 0;
	for (int i = 0; i < vertex; i++) {
		int v = -1;
		for (int j = 0; j < vertex; j++) {
			if ((v == -1 || par->minimal[j] < par->minimal[v]) && par->used[j] == 0) {
				v = j;
			}
		}
		if (par->minimal[v] == UINT_MAX) {
			distance(par, vertex, start, finish, len);
			freeS(par);
			return 0;
		}
		par->used[v] = 1;
		updateDistances(par, v, vertex, len);
	}
	distance(par, vertex, start, finish, len);
	freeS(par);
	return 0;
}
