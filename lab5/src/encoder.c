#include "structs.h"

void writeBuffer(Data* out) {
    fwrite(out->buffer, 1, out->pos, out->file);
    memset(out->buffer, 0, BUFFER_SIZE);
    out->pos = 0;
}

void processBit(const int bit, unsigned int* bitpos, Data* out) {
    if (*bitpos > 7) {
        *bitpos = 0;
        out->pos++;
        if (out->pos >= BUFFER_SIZE) {
            writeBuffer(out);
        }
        out->buffer[out->pos] = 0;
    }
    if (bit == '1'){
        out->buffer[out->pos] |= 128u >> *bitpos;
    }
    (*bitpos)++;
}

void huffman(unsigned char** table, Data* data, Data* out) {
    unsigned int bitpos = out->bitpos;
    while (1) {
        for (int i = data->pos; i < data->size; i++) {
            int bit;
            for (int k = 0;(bit = table[data->buffer[i]][k]) != 0; k++) {
                processBit(bit, &bitpos, out);
            }
        }
        data->pos = 0;
        if ((data->size = fread(data->buffer, 1, BUFFER_SIZE - 1, data->file)) <= 0) {
            break;
        }
    }
    fwrite(out->buffer, sizeof(unsigned char), out->pos + (bitpos != 0), out->file);
}

void writesym(const unsigned char sym, Data* out) {
	if (out->bitpos != 0) {
        (out->buffer[out->pos]) |= sym >> (out->bitpos);
		(out->pos)++;
		if (out->pos < BUFFER_SIZE) {
            (out->buffer[out->pos]) |= sym << (8 - (out->bitpos));
		}
        else {
            fwrite(out->buffer, 1, out->pos, out->file);
			memset(out->buffer, 0, BUFFER_SIZE);
			out->pos = 0;
		    (out->buffer[out->pos]) |= sym << (8 - (out->bitpos));
        }
	}
	else {
		(out->buffer[out->pos]) = sym;
		(out->pos)++;
		if (out->pos < BUFFER_SIZE) {
            return;
		}
        else{
            fwrite(out->buffer, 1, out->pos, out->file);
			memset(out->buffer, 0, BUFFER_SIZE);
			out->pos = 0;
        }
	}
}

void bitWrite(Data* out, Node* root) {
	if (root->side[0] == NULL) {
	    (out->bitpos)++;
		if (out->bitpos < 8) {
            writesym(root->sym, out);
		}
        else{
            out->bitpos = 0;
			(out->pos)++;
			if (out->pos >= BUFFER_SIZE) {
				fwrite(out->buffer, 1, out->pos, out->file);
				memset(out->buffer, 0, BUFFER_SIZE);
				out->pos = 0;
			}
            writesym(root->sym, out);
        }
	}
	else {
        (out->buffer[out->pos]) |= 128 >> out->bitpos;
		(out->bitpos)++;
		if (out->bitpos < 8) {
            bitWrite(out, root->side[0]);
		    bitWrite(out, root->side[1]);
		}
        else{
            out->bitpos = 0;
			(out->pos)++;
			if (out->pos >= BUFFER_SIZE) {
				fwrite(out->buffer, 1, out->pos, out->file);
				memset(out->buffer, 0, BUFFER_SIZE);
				out->pos = 0;
			}
		    bitWrite(out, root->side[0]);
		    bitWrite(out, root->side[1]);
        }
	}
}

void fillT(Node* root, unsigned char** table, unsigned char* path, const int deep) {
	if (root->side[0] == NULL) {
        path[deep] = '\0';
		table[root->sym] = memcpy(malloc(deep + 1), path, deep + 1);
	}
	else {
 	    path[deep] = '0';
		fillT(root->side[0], table, path, deep + 1);
		path[deep] = '1';
		fillT(root->side[1], table, path, deep + 1);
	}
}

int compare(const void* a, const void* b) {
	return (int)(*(Node**)b)->freq - (int)(*(Node**)a)->freq;
}

Node* createTree(Node** slice, int* freq) {
    int n = 0;
	slice[n] = NULL;
	for (int i = 0; i < TREE_SIZE; i++) {
		if (freq[i] > 0) {
			Node* node = malloc(sizeof(Node));
            if(node == NULL){
                return NULL;
            }
            node->sym = (unsigned char)i;
			node->freq = freq[i];
            node->side[1] = NULL;
            node->side[0] = NULL;
			slice[n] = node;
            n++;
		}
	}
	while (n > 1) {
		qsort(slice, n, sizeof(Node*), compare);
		Node* node = malloc(sizeof(Node));
        if (node == NULL){
            return NULL;
        }
        node->sym = 0;
        node->freq = slice[n - 2]->freq + slice[n - 1]->freq;
        node->side[1] = slice[n - 1];
		node->side[0] = slice[n - 2];
		slice[n - 2] = node;
		n--;
	}
	return slice[0];
}

void freqCount(Data* data, int* freq) {
    while ((data->size = fread(data->buffer, 1, BUFFER_SIZE - 1, data->file)) > 0) {
        for (int i = data->pos; i < data->size; i++) {
            freq[data->buffer[i]]++;
        }
        data->pos = 0;
    }
    data->pos = 1;
}


int encode(Data* data) {
    Data* out = malloc(sizeof(Data));
    if (out == NULL) {
        return 0;
    }
    out->pos = 4;
    out->bitpos = 0;
    out->file = fopen("out.txt", "wb");
    memset(out->buffer, 0, sizeof(out->buffer));
    if (out->file == NULL) {
        free(out);
        return 0;
    }
    int* freq = (int*)calloc(TREE_SIZE, sizeof(int)); 
    if (freq == NULL) {
        fclose(out->file);
        free(out);
        return 0;
    }
    freqCount(data, freq);
    Node* slice[TREE_SIZE] = { NULL };
    Node* tree = createTree(slice, freq);
    if (tree == NULL) {
        fclose(out->file);
        free(out);
        free(freq);
        return 0;
    }
    unsigned char* path = malloc(TREE_SIZE * sizeof(unsigned char));
    if (path == NULL) {
        fclose(out->file);
        free(out);
        free(freq);
        freeTree(tree);
        return 0;
    }
    unsigned char *table[TREE_SIZE] = { 0 };
    fillT(tree, table, path, 0);
    int inSize = (int)ftell(data->file) - data->pos;
    fseek(data->file, (long)data->pos, SEEK_SET);
    out->buffer[3] = (unsigned char)(inSize);
    out->buffer[2] = (unsigned char)(inSize >> 8);
    out->buffer[1] = (unsigned char)(inSize >> 16);
    out->buffer[0] = (unsigned char)(inSize >> 24);
    bitWrite(out, tree);
    huffman(table, data, out);
    fclose(out->file);
    freeTable(table);
    free(path);
    freeTree(tree);
    free(freq);
    free(out);
    return 0;
}
