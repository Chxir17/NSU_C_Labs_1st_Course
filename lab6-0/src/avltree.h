#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct tree {
    int height;
    int data;
    struct tree *left;
    struct tree *right;
} avlTree;

int gHeight(avlTree *root);
avlTree* bTree(avlTree* tree, avlTree* root, const int data, const int i);

#endif
