#include "structs.h"
#include <stdlib.h>

void freeTree(Node* root) {
	if (root->side[0] == NULL) {
        free(root);
	}
    else{
        freeTree(root->side[1]);
	    freeTree(root->side[0]); 
	    free(root);
    }
}

void freeTable(unsigned char** table) {
	for (int i = 0; i < TREE_SIZE; i++) {
		if (table[i] != NULL){
			free(table[i]);
        }
	}
}
