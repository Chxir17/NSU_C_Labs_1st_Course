#include <stdlib.h>
#include <stdio.h>
#include "kmp.h"

int main() {
    char *pattern = malloc((NUMBER_OF_CHARS + 2) * sizeof(char)); 
    if (pattern != NULL){
        if (fgets(pattern, NUMBER_OF_CHARS + 2, stdin) == NULL) {
            free(pattern);
            return 0;
        }
        int size = 0;
        while (pattern[size] != '\n'){
            size++;
        }
        KMP(size, pattern);
        free(pattern);
    }
    return 0;
}
