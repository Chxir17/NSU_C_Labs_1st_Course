#include <stdlib.h>
#include "rbtree.h"

rbTree* turn(rbTree* root, const int dir) {
	rbTree* tmp = root->link[!dir];
	root->link[!dir] = tmp->link[dir];
	tmp->link[dir] = root;
	tmp->col = root->col;
	root->col = 'R';
	return tmp;
}

char recol(rbTree* root) {
	if (root->col == 'B') {
		return 'R';
	}
	return 'B';
}

void ccolor(rbTree* root) {
	root->col = recol(root);
	root->link[1]->col = recol(root->link[1]);
	root->link[0]->col = recol(root->link[0]);
}

rbTree* bigturn(rbTree* root, const int dir) {
	root->link[!dir] = turn(root->link[!dir], !dir);
	return turn(root, dir);
}

int maxx(const int a, const int b) {
	if (a > b){
		return a;
	}
	return b;
}

int height(rbTree* root) {
	if (root == NULL) {
		return 1;
	}
	int leftHeight = height(root->link[0]), rightHeight = height(root->link[1]), col;
	if (root->col == 'R'){
		col = 0;
	}
	else{
		col = 1;
	}
	return maxx(leftHeight, rightHeight) + col;

}

rbTree* balance(rbTree* root, const int dir) {
	if (((root->link[dir]->link[dir] != NULL || root->link[dir]->link[!dir] != NULL)) && root->link[dir]->col == 'R'){
		if (root->link[!dir] == NULL || root->link[!dir]->col == 'B') { 
			if (root->link[dir]->link[!dir] != NULL && root->link[dir]->link[!dir]->col == 'R') {
				root = bigturn(root, !dir);
			}
			else if (root->link[dir]->link[dir] != NULL && root->link[dir]->link[dir]->col == 'R') {
				root = turn(root, !dir);
			}
		}
		else { 
			if ((root->link[dir]->link[0] != NULL && root->link[dir]->link[0]->col == 'R') || (root->link[dir]->link[1] != NULL && root->link[dir]->link[1]->col == 'R')) {
				ccolor(root);
			}
		}
	}
	return root;
}

rbTree* insert(rbTree* root, rbTree* tree, const int value, const int i) {
    if (root != NULL) {
        if (value <= root->val) {
            root->link[0] = insert(root->link[0], tree, value, i);
            return balance(root, 0);
        }
        root->link[1] = insert(root->link[1], tree, value, i);
        return balance(root, 1);
    }
    (tree + i)->val = value;
    (tree + i)->col = 'R';
    (tree + i)->link[0] = NULL;
    (tree + i)->link[1] = NULL;
    root = tree + i;
    return root;
}
