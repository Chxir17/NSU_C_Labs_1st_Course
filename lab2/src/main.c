#include <stdio.h>
#include <string.h>
#define MAX_LEN 13

int isValid(const char *num, int len) {
    int uniqSim[10] = {0};
    for (int i = 0; i < len - 1; i++) {
        uniqSim[num[i] - '0'] += 1;
        if (num[i] < '0' || num[i] > '9' || uniqSim[num[i] - '0'] > 1)
            return 1;
    }
    return 0;
}

void swap(char* num, const int k, const int j){
    char tmp = num[j];
    num[j] = num[k];
    num[k] = tmp;
}

void reverseNum(char *num, int startIdx, int endIdx) {
    for (;startIdx < endIdx;startIdx++,endIdx--) {
        swap(num, startIdx,endIdx);
    }
}

int isDescending(const char *num, int len) {
    if (len-1==1) {
        return 1;
    }
    int c=0;
    for (int i = 0; i <= len-3; i++) {
        if (num[i] > num[i + 1]) {
            c++;
        }
        if (c==len-2) {
            return 1;
        }
    }
    return 0;
}

char *swaper(char *num, int len) {
    for (int j = len - 2; j > 0; j--) {
        if (num[j] <= num[j - 1]) {
            continue;
        }
        for (int k = len - 2; k >= j; k--) {
            if (num[k] <= num[j - 1]) {
                continue;
            }
            swap(num, k, j - 1);
            reverseNum(num, j, len - 2);
            return num;
        }
    }
    return 0;
}

int main() {
    char numbers[MAX_LEN];
    int n;
    if (fgets(numbers, MAX_LEN, stdin) != NULL && scanf("%d", &n) == 1) {
        int numLen = strlen(numbers);
        if (!isValid(numbers, numLen)) {
            int counter = 1;
            while (counter <= n && !isDescending(numbers, numLen)) {
                swaper(numbers, numLen);
                counter++;
                printf("%s", numbers);
            }
            return 0;
        }
    }
    printf("bad input");
    return 0;
}
