#ifndef BTREE
#define BTREE

typedef struct BTree {
    int order;
    int height;
    struct Node* root;
} BTree;

typedef struct Node {
    int keyCount;
    int* keys;
    struct Node** children;
} Node;

void insert(BTree* tree, const int key);

#endif
