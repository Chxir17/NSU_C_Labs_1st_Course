#include "kmp.h"
#include <stdlib.h>
#include <stdio.h>

void prefix(char* table, char* pattern, const int size) {
    for (int i = 1; i < size; i++) {
        int j = table[i - 1];
        while ((pattern[i] != pattern[j]) && (j > 0)){
            j = table[j - 1];
        }
        if (pattern[j] == pattern[i]) {
            j++;
        }
        table[i] = j;
    }
}

void KMP(const int size, char* pattern) { 
    char* text = malloc(NUMBER_OF_CHARS * sizeof(char)); 
    if (text == NULL){ 
        return; 
    } 
    int tLen = fread(text, sizeof(char), NUMBER_OF_CHARS, stdin); 
    char* table = malloc(size * sizeof(char));
    if (table == NULL) {
        free(text);
        return;
    }
    table[0] = 0;
    prefix(table, pattern, size); 
    for (int i = 0; i < size; i++) {
        printf("%d ", table[i]); 
    }
    if (size > tLen) {
        free(table);
        free(text);
        return;
    }
    for (int tPos = 0, bPos = 0, shift ;size <= tLen;) {
        int match = 0;
        while (pattern[match] == text[bPos + match]) {
            match++;
            if (match >= size){
                break;
            }
        }
        if (match == 0) {
            shift = 1;
        }
        else{
            printf("%d %d ", tPos + 1, match);
            shift = match - table[match - 1];
        }
        int shift2 = bPos + shift;
        if (size + shift2 <= tLen) {
            bPos += shift;
        }
        else{
            int size2 = tLen - shift2;
            for (int i = 0; i < size2; i++) {
                text[i] = text[shift2 + i];
            }
            tLen = size2 + fread(&text[size2], sizeof(char), NUMBER_OF_CHARS - size2, stdin);
            bPos = 0;
        }
        tPos += shift;
    }
    free(table);
    free(text);
}
