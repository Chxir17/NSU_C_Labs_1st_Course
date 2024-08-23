#include <stdio.h>
#include <math.h>
#define MAX_START 14
#define MAX_END 60

int numberLen(const char *num){
    int lenNum = 0;
    for(int i = 0; num[i] != '\0'; i++){
        if (num[i]!='.'){
            lenNum++;
        }
    }
    return lenNum;
}

int lenIntegerPart(const char *num){
    int i = 0;
    for (;num[i]!='.' && num[i]!='\0';i++);
    return i;
}

int charToInt(const char num){
    if ((num <= '9') && (num >= '0')){
        return num - '0';
    }
    if ((num <= 'F') && (num >= 'A')){
        return num - 'A' + 10;
    }
    if ((num <= 'f')&&(num >= 'a')){
        return num - 'a' + 10;
    }
    return 0;
}

char intToChar(const long long int num){
    if (num <= 9){
        return '0' + num;
        }
    return 'A' + num - 10;
}

void reverse(char* num, int j){
    for (int i = 0;i < j; i++, j--) {
        char temp = num[i];
        num[i] = num[j];
        num[j] = temp;
    }
}
int isValidBase(const int base) {
    if (base < 2 || base > 16) {
        return 0;
    }
    return 1;
}

int isValid(const char *num, const int baseFrom){
    for (int i = 0; num[i] != '\0'; i++){
        if (num[i]=='.'){
            continue;
        }
        if (charToInt(num[i]) >= baseFrom || num[i] < '0' || (num[i] > '9' && num[i] < 'A') || (num[i] > 'F' && num[i] < 'a') || num[i] > 'f'){
            return 0;
        }
    }
    return 1;
}

int isValidNum(const char *num, const int lenNumber, const int IntLen){
    int fractionLen = lenNumber-IntLen;
    if (IntLen == 0 && fractionLen > 0){
        return 0;
    }
    for (int i = 0, dot = 0; num[i] != 0; i++) {
        if (num[i] == '.' && fractionLen == 0) {
            return 0;
        }
        if (num[i] == '.') {
            dot++;
        }
        if (dot > 1) {
            return 0;
        }
    }
    return 1;
}

long double To10(const char *num, const int baseFrom, const int lenInt){
    long double val10 = 0.0;
    long double maxPow = pow(baseFrom, lenInt);
    for (int i = 0; num[i] != '\0';i++) {
        if (num[i] == '.') {
            continue;
        }
        val10 += (charToInt(num[i])) * maxPow;
        maxPow/=baseFrom;
    }
    return val10;
}

char *ToAnotherBase(const long double val10, char *result, const int baseTo) {
    int i = 0;
    long long num10 = (long long) val10;
    long double remainderFrac = val10 - num10;
    if (num10 == 0) {
        result[0] = '0';
        i++;
    } else {
        while (num10 != 0) {
            long long remainder = num10 % baseTo;
            result[i] = intToChar(remainder);
            num10 /= baseTo;
            i++;
        }
    }
    result[i] = '\0';
    int intLenRes = numberLen(result)-1;
    reverse(result, intLenRes);
    if (remainderFrac == 0) {
        return result;
    }
    result[i++] = '.';
    for (int c = 0; remainderFrac != 0 && c <= 12;i++, c++) {
        remainderFrac *= baseTo;
        result[i] = intToChar((int) remainderFrac);
        remainderFrac -= (long long) remainderFrac;
    }
    result[i] = '\0';
    return result;
}

int main() {
    int baseFrom, baseTo;
    char number[MAX_START];
    if (scanf("%d %d %13s", &baseFrom, &baseTo, number) == 3) {
        int lenNumber = numberLen(number);
        int lenInt = lenIntegerPart(number);
        if (isValid(number, baseFrom) && isValidNum(number, lenNumber, lenInt) && isValidBase(baseFrom) && isValidBase(baseTo)){
            char result[MAX_END];
            printf("%s", ToAnotherBase(To10(number, baseFrom, lenInt-1), result, baseTo));
            return 0;
        }
    }
    printf("bad input");
    return 0;
}
