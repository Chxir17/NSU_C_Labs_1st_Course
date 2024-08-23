#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        avlTree *AVLtree = malloc(sizeof(avlTree)*n);
        if(AVLtree == NULL){
            free(AVLtree);
            return 0;
        }
        avlTree *root = NULL;
        for (int i = 0, data; i < n; i++) {
            if (scanf("%d", &data) == 1) {
                root = bTree(AVLtree ,root, data, i);
            }
        }
        printf("%d", gHeight(root));
        free(AVLtree);
    }
    return 0;
}
