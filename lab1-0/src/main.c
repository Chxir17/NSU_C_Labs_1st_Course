#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 16
#define NUMBER_OF_CHARS 512

typedef struct pattern {
    unsigned char pattern[LEN + 1];
    unsigned int movesPat[NUMBER_OF_CHARS];
    unsigned int allocated;
    unsigned int len;
}pat;

typedef struct ringBuffer {
    unsigned char* rb;
    unsigned int len;
    unsigned int curIndexBegin;
    unsigned int curIndexEnd;
    unsigned int curIndexInput;
    unsigned int allocated;
}RB;

void initialisePattern(pat* p) {
    p->allocated = 0;
    if (scanf("%16[^\n]s", p->pattern) == 0) {
        return;
    }
    p->allocated = 1;
    p->len = strlen((char*)p->pattern);
    if (getchar() != '\n') {
        p->allocated = 0;
    }

}

void initialiseBuffer(RB* b, int patternLen) {
    b->allocated = 0;
    if (b->rb!= NULL) {
        free(b->rb);
    }
    b->rb = (unsigned char*)calloc(patternLen + 1, sizeof(unsigned char));
    if (b->rb == NULL) {
        free(b->rb);
        return;
    }
    if (fgets((char*)b->rb, patternLen + 1, stdin) == NULL) {
        free(b->rb);
        return;
    }
    b->len = strlen((char*)b->rb);
    b->curIndexBegin = 0;
    b->curIndexEnd = b->len - 1;
    b->curIndexInput = b->len;
    b->allocated = 1;
}

void move(pat* p) {
    for (int i = 0; i < NUMBER_OF_CHARS; i++) {
        p->movesPat[i] = p->len;
    }
    for (unsigned int i = 0; i < p->len - 1; i++) {
        p->movesPat[p->pattern[i]] = p->len - 1 - i;
    }
}

int compare(pat* p, RB* b) {
    for (unsigned int i = b->len-1; i > 0; i--) {
        printf("%u ", b->curIndexInput - (b->len - 1) + i);
        if (p->pattern[i] != b->rb[(b->len + b->curIndexEnd + i + 1) % b->len]) {
            break;
        }
        else if (i == 1) {
            printf("%u ", b->curIndexInput - b->len + 1);
        }
    }
    int curMove = p->movesPat[b->rb[b->curIndexEnd]];
    b->curIndexInput += curMove;
    return curMove;
}


void BoyerMooreSearch(pat* p, RB* b) {
    while (1) {
        int curMove = compare(p, b);
        b->curIndexBegin = (b->curIndexBegin + curMove) % b->len;
        int writeToBack = b->len - b->curIndexEnd - 1;
        if (fgets((char*)b->rb + (b->curIndexEnd + 1) % b->len, writeToBack + 1, stdin) == NULL) {
            return;
        }
        int secondRead = curMove - writeToBack;
        if (secondRead > 0) {
            if (fgets((char*)b->rb, secondRead + 1, stdin) == NULL) {
                return;
            }
        }
        b->curIndexEnd = (b->len + b->curIndexBegin - 1) % b->len;
        if (feof(stdin)) {
            return;
        }
    }
}


int main() {
    pat *pattern = calloc(1, sizeof(pat));
    initialisePattern(pattern);
    if (pattern->allocated) {
        move(pattern);
        RB *buffer = calloc(1, sizeof(RB));
        initialiseBuffer(buffer, pattern->len);
        if (buffer->allocated) {
            if (pattern->len <= buffer->len) {
                BoyerMooreSearch(pattern, buffer);
            }
            free(buffer->rb);
        }
        free(buffer);
    }
    free(pattern);
    return 0;
}
