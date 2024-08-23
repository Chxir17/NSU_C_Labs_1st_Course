#ifndef RBTREE
#define RBTREE

typedef struct tree {
	char col;
	int val;
	struct tree* link[2];
} rbTree;

int height(rbTree* root);
rbTree* insert(rbTree* root, rbTree* tree, const int value, const int i);

#endif
