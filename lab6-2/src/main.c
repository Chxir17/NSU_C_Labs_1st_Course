#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

void freeN(Node* root) {
    if (root->children != NULL) {
        for (int i = 0; i < root->keyCount + 1; i++){
            freeN(root->children[i]);
        }
        free(root->children);
    }
    free(root->keys);
    free(root);
}

void freeT(BTree* tree) {
    if (tree->root != NULL) {
        freeN(tree->root);
    }
    free(tree);
}

int main() {
    int order, keyNum;
    if (scanf("%d %d", &order, &keyNum) != 2){
        return 0;
    }
    BTree* tree = malloc(sizeof(BTree));
    if (tree == NULL){
        return 0;
    }
    tree->order = order;
    tree->height = 0;
    tree->root = NULL;
    for (int i = 0; i < keyNum; i++) {
        int key;
        if (scanf("%d", &key) != 1) {
            freeT(tree);
            return 0;
        }
        insert(tree, key);
    }
    printf("%d", tree->height);
    freeT(tree);
    return 0;
}
