#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#define END 1
#define NOTEND 0

Node* createNode(BTree* tree, const int end) {
    Node* nextNode = malloc(sizeof(Node));
    if (nextNode == NULL){
        return NULL;
    }
    nextNode->keyCount = 0;
    nextNode->keys = malloc((tree->order * 2 - 1) * sizeof(int));
    if (nextNode->keys == NULL){
        free(nextNode);
        return NULL;
    }
    if (end == 0) {
        nextNode->children = malloc((tree->order * 2) * sizeof(Node*));
        if (nextNode->children == NULL){
            free(nextNode->keys);
            free(nextNode);
            return NULL;
        }
        return nextNode;
    }
    nextNode->children = NULL;
    return nextNode;
}

int fChild(Node* node, const int key) {
    int low = 0, high = node->keyCount - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (node->keys[mid] >= key) {
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return high + 1;
}

void move(Node* source, const int i, Node* dst, int j) {
    int n = source->keyCount - i;
    memmove(dst->keys + j, source->keys + i, n * sizeof(int));
    if (source->children == NULL) {
        return;
    }
    memmove(dst->children + j, source->children + i, (n + 1) * sizeof(struct Node*));
}

int full(BTree* tree, Node* node) {
    if (node->keyCount == 2 * tree->order - 1){
        return 1;
    }
    return 0;
}

void split(BTree* tree, Node* node, const int child) {
    Node* old = node->children[child];
    int isLeaf = 0;
    if (old->children == NULL){
        isLeaf = 1;
    }
    Node* new = createNode(tree, isLeaf);
    move(old, tree->order, new, 0);
    new->keyCount = tree->order - 1;
    old->keyCount = tree->order - 1;
    move(node, child, node, child + 1);
    node->children[child + 1] = new;
    node->keys[child] = old->keys[tree->order - 1];
    node->keyCount++;
}

void goodInsert(BTree* tree, Node* node, const int key) {
    if (node->children != NULL) {
        int child = fChild(node, key);
        if (full(tree, node->children[child]) == 1) {
            split(tree, node, child);
            if (key >= node->keys[child]) {
                child = child + 1;
            }
        }
        goodInsert(tree, node->children[child], key);
        return;
    }
    int i = fChild(node, key);
    move(node, i, node, i + 1);
    node->keys[i] = key;
    node->keyCount++;
}


void insert(BTree* tree, const int key) {
    if (tree->root == NULL) {
        tree->root = createNode(tree, END);
        tree->height++;
    }
    if (full(tree, tree->root) == 1) {
        Node* nextRoot = createNode(tree, NOTEND);
        nextRoot->children[0] = tree->root;
        split(tree, nextRoot, 0);
        tree->root = nextRoot;
        tree->height++;
    }
    goodInsert(tree, tree->root, key);
}
