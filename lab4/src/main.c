#include <stdio.h>
#include "calculator.h"
#include "stack.h"
#define MAX_LEN 1001

int main() {
    st numbers = { .head = 0};
    st operators = { .head = 0};
    char expression[MAX_LEN]={0};
    int errorNumber = postfixForm(&numbers, &operators, expression);
    if (errorNumber == 1 || numbers.head <= -1) {
        printf("syntax error");
        return 0;
    }
    else if (errorNumber == 2) {
        printf("division by zero");
        return 0;
    }
    else {
        printf("%d", numbers.expression[numbers.head - 1]);
    }
    return 0;
}
