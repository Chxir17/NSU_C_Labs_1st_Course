#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

int main() {
	int n;
	if (scanf("%d", &n) == 1) {
		if (n <= 0){
			printf("0");
			return 0;
		}
		rbTree* tree = (rbTree*)malloc(n * sizeof(rbTree));
		if (tree==NULL) {
			free(tree);
			return 0;
		}
		rbTree* root = NULL;
		for (int i = 0, data; i < n; i++) {
			if (scanf("%d", &data) != 1) {
				free(tree);
				return 0;
			}
			root = insert(root, tree, data, i);
		}
		root->col = 'B';
		printf("%d", height(root));
		free(tree);
	}
	return 0;
}
