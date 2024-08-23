#ifndef STRUCTS
#define STRUCTS
#define BUFFER_SIZE 1024
#define TREE_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	struct Node* side[2];
	int freq;
	unsigned char sym;
} Node;

typedef struct Data {
	FILE* file;
	unsigned int bitpos;
	int pos;
	int size;
	unsigned char buffer[BUFFER_SIZE];
} Data; 

void freeTree(Node* root);
void freeTable(unsigned char** table);

#endif
