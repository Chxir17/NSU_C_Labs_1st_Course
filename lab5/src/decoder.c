#include "structs.h"

unsigned char getbyte(Data* data) {
	unsigned char byte = data->buffer[data->pos];
	unsigned char sym = byte << data->bitpos;
	(data->pos)++;
	if (data->pos < data->size){
		byte = data->buffer[data->pos];
		sym |= byte >> (8 - data->bitpos);
	}
	else{
		data->size = fread(data->buffer, 1, BUFFER_SIZE - 1, data->file);
		data->pos = 0;
		byte = data->buffer[data->pos];
		sym |= byte >> (8 - data->bitpos);
	}
	return sym;
}

int getbit(Data* data) {
	char byte = data->buffer[data->pos];
	char bit = ((byte << data->bitpos) & 128) >> 7;
	(data->bitpos)++;
	if ((data->bitpos) < 8) {
		return bit;
	}
	data->bitpos = 0;
	(data->pos)++;
	if (data->pos >= data->size){
		data->size = fread(data->buffer, 1, BUFFER_SIZE - 1, data->file);
		data->pos = 0;
	}
	return bit;
}

void dhuffman(Node* tree, Data* data, Data* out, const int count) {
	for (int i = 0; i < count; i++) {
		Node* cur = tree;
		for (;cur->side[0] != NULL;) {
			cur = cur->side[getbit(data)];
		}
		out->buffer[out->pos++] = cur->sym;
		if (out->pos >= BUFFER_SIZE) {
			fwrite(out->buffer, 1, out->pos, out->file);
			out->pos = 0;
		}
	}
	fwrite(out->buffer, sizeof(char), out->pos, out->file);
}

Node* restore(Data* data) {
	Node* node = malloc(sizeof(Node));
	int bit = getbit(data);
	if (bit != 0) {
		node->side[0] = restore(data);
		node->side[1] = restore(data);
	}
	else {
		node->side[0] = node->side[1] = NULL;
		node->sym = getbyte(data);
	}
	return node;
}

int decode(Data* data) {
	Data* out = malloc(sizeof(Data));
    if (out == NULL) {
        return 0;
    }
	out->pos = 0;
    out->bitpos = 0;
    out->file = fopen("out.txt", "wb");
    if (out->file == NULL) {
        free(out);
        return 0;
    }
	unsigned char var = 0;
	int size = 0;
	for (int i = 0; i < 4; i++) {
		size <<= 8;
		if ((fread(&var, 1, 1, data->file)) == 0) {
			fclose(out->file);
			free(out);
			return 0;
		}
		size += var;
	}
	if ((data->size = fread(data->buffer, 1, BUFFER_SIZE - 1, data->file)) != 0) {
		Node* tree = restore(data);
		dhuffman(tree, data, out, size);
		freeTree(tree);
	}
	fclose(out->file);
	free(out);
	return 0;
}
