#include "avltree.h"
#include <stdio.h>

avlTree *newNode(avlTree *tree, const int data, const int i) {
    tree[i].height = 1;
    tree[i].data = data;
    tree[i].left = NULL;
    tree[i].right = NULL;
    return &tree[i];
}

int gHeight(avlTree *root) {
    if (root!=NULL) {
        return root->height;
    }
    return 0;
}

int difference(avlTree *root) {
    if (root!=NULL) {
        return gHeight(root->left) - gHeight(root->right);
    }
    return 0;
}

int cHeight(avlTree *root) {
    if (root!=NULL) {
        int lHeight = gHeight(root->left), rHeight = gHeight(root->right);
        return (lHeight > rHeight) ? lHeight+1 : rHeight+1;
    }
    return 0;
}

avlTree *lturn(avlTree *node) {
    avlTree *r = node->right;
    node->right = r->left;
    r->left = node;
    node->height = cHeight(node);
    r->height = cHeight(r);
    return r;
}

avlTree *rturn(avlTree *node) {
    avlTree *l = node->left;
    node->left = l->right;
    l->right = node;
    node->height = cHeight(node);
    l->height = cHeight(l);
    return l;
}

avlTree * balance(avlTree *node) {
    int delta = difference(node);
    if (delta == -2) {
        if (difference(node->right) == 1) {
            node->right = rturn(node->right);
            return lturn(node);
        } 
        else {
            return lturn(node);
        }
    } 
    else if (delta == 2) {
        if (difference(node->left) == -1) {
            node->left = lturn(node->left);
            return rturn(node);
        }
        else {
            return rturn(node);
        }
    }
    return node;
}


avlTree* bTree(avlTree* tree, avlTree* root, const int data, const int i) {
    if (root == NULL) {
        return newNode(tree, data, i);
    }
    if (data < root->data) {
        root->left = bTree(tree, root->left, data, i);
    } 
    else {
        root->right = bTree(tree, root->right, data, i);
    }
    root->height = cHeight(root);
    return balance(root);
}
