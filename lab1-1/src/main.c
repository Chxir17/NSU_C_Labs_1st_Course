#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERN 16
#define SIZE_OF_RB 8192

typedef struct pattern {
    unsigned char pattern[MAX_PATTERN + 1];
    unsigned int len;
    unsigned int hash;
    unsigned int allocated;
} Pat;

typedef struct ringBuffer {
    unsigned char rb[SIZE_OF_RB + 1];
    unsigned int len;
    unsigned int hash;
    unsigned int allocated;
} RB;

void calculateDegrees(unsigned int *arr) {
    for (int i = 0; i < MAX_PATTERN; i++) {
        if (i == 0) {
            arr[i] = 1;
        }
        else {
            arr[i] = arr[i - 1] * 3;
        }
    }
}

void recalculationHash(unsigned char first, unsigned char new, Pat* p, RB* b, unsigned int *arr) {
    unsigned int firstSym = (b->hash - (first % 3)) / 3;
    unsigned int secondSym = (new % 3) * arr[p->len - 1];
    b->hash = firstSym + secondSym;
}

unsigned int calculateHash(const unsigned char* pattern, int len, unsigned int *arr) {
    unsigned int hash = 0;
    for (int i = 0; i < len; i++) {
        unsigned int firstPart = ((int)pattern[i] % 3);
        unsigned int secondPart = arr[i];
        hash += firstPart * secondPart;
    }
    return hash;
}

void initialisePattern(Pat* p, unsigned int *arr) {
    p->allocated = 0;
    if (scanf("%16[^\n]s", p->pattern) == 0) {
        free(p);
        return;
    }
    p->allocated = 1;
    p->len = strlen((char*)p->pattern);
    p->hash = calculateHash(p->pattern, p->len, arr);
    printf("%u ", p->hash);
    if (getchar() != '\n') {
        p->allocated = 0;
    }
}

void initialiseBuffer(RB* b) {
    b->allocated = 0;
    if (scanf("%8192[^\xff]s", b->rb) == 0) {
        return;
    }
    b->allocated = 1;
    b->len = strlen((char*)b->rb);
}

void compare(const unsigned char* first, const unsigned char* second, int i) {
    for (unsigned int index = 0; index < strlen((char*)first); index++) {
        printf("%u ", i + index);
        if (first[index] != second[index]) {
            break;
        }
    }
}

void RabinKarp(Pat* p, RB* b, unsigned int *arr) {
    int currentIndex = 1, beginBuffer = 1;
    unsigned char previous = 0;
    unsigned char *equalLen = (unsigned char*)calloc(p->len + 1, sizeof(unsigned char));
    while (1) {
        for (unsigned int i = 0; i < b->len - p->len + 1; i++) {
            if (i == 0) {
                memcpy(equalLen, b->rb, p->len);
            }
            else {
                previous = equalLen[0];
                for (unsigned int j = 1; j < p->len; j++) {
                    equalLen[j - 1] = equalLen[j];
                }
                equalLen[p->len - 1] = b->rb[p->len + i - 1];
                currentIndex++;
            }
            if (beginBuffer) {
                b->hash = calculateHash(equalLen, p->len, arr);
                beginBuffer = 0;
            }
            else {
                recalculationHash(previous, equalLen[p->len - 1], p, b, arr);
            }
            if (p->hash == b->hash) {
                compare(p->pattern, equalLen, currentIndex);
            }
        }
        if (!feof(stdin) && b->len == SIZE_OF_RB) {
            beginBuffer = 1;
            initialiseBuffer(b);
            currentIndex += p->len;
        }
        else {
            break;
        }
    }
    free(equalLen);
}

int main() {
    unsigned int arr[MAX_PATTERN];
    calculateDegrees(arr);
    Pat *pattern = calloc(1, sizeof(Pat));
    initialisePattern(pattern, arr);
    if (pattern->allocated) {
        RB *buffer = calloc(1, sizeof(RB));
        initialiseBuffer(buffer);
        if (buffer->allocated) {
            RabinKarp(pattern, buffer, arr);
            free(pattern);
            free(buffer);
            return 0;
        }
        free(buffer);
        free(pattern);
    }
    return 0;
}
