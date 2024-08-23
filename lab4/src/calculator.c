#include "calculator.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int priority(char sym) {
    switch (sym) {
        case '/':
        case '*':
            return 3;
        case '+':
        case '-':
            return 2;
        case '(':
        case ')':
            return 1;
        default:
            return 0;
    }
}

int isOp(char symbol) {
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
}

int isNum(char symbol) {
    return (symbol >= '0' && symbol <= '9');
}

int calculator(st *numbers, char sym) {
    int a, b;
    if (sym == '(') {
        return 1;
    }
    if (emptyCheck(numbers)) {
        return 1;
    }
    a = pop(numbers);
    if (emptyCheck(numbers)) {
        return 1;
    }
    b = pop(numbers);
    switch (sym) {
        case '+':
            push(numbers, b + a);
            break;
        case '-':
            push(numbers, b - a);
            break;
        case '*':
            push(numbers, b * a);
            break;
        case '/':
            if (a == 0) {
                return 2;
            }
            push(numbers, b / a);
            break;
        default:
            break;
    }
    return 0;
}

int postfixForm(st *numbers, st *operators, char *expression) {
    int sym, j, i = 0;
    int newNumber, uselessBrackets = 0, brackets = 0, errorNumber = 0;
    while ((sym = getchar()) != '\n') {
        if (isNum(sym)) {
            expression[i] = sym;
            i++;
            while (isNum(sym = getchar())) {
                expression[i] = sym;
                i++;
            }
            newNumber = atoi(expression);
            uselessBrackets = 1;
            push(numbers, newNumber);
            for (j = 0; j < i; ++j){
                expression[j] = 0;
            }
            i = 0;
        }
        if (sym == '(') {
            uselessBrackets = 0;
            push(operators, sym);
            brackets++;
            continue;
        }
        else if (sym == ')') {
            brackets--;
            if (((uselessBrackets != 0) && (brackets >= 0))) {
                while (operators->expression[operators->head - 1] != '(') {
                    errorNumber = calculator(numbers, pop(operators));
                    if (errorNumber != 0) {
                        return errorNumber;
                    }
                }
                pop(operators);
            }
            else {
                return 1;
            }
        }
        else if (isOp(sym)) {
            while ((!emptyCheck(operators)) && (priority(operators->expression[operators->head - 1]) >= priority(sym))) {
                errorNumber = calculator(numbers, pop(operators));
                if (errorNumber != 0){
                    return errorNumber;
                }
            }
            push(operators, sym);
            continue;
        }
        else if ((sym != '\n') && (sym != EOF)){
            return 1;
        }
        else if (sym == '\n') {
            break;
        }
    }
    if (!emptyCheck(numbers)) {
        while (!emptyCheck(operators)) {
            errorNumber = calculator(numbers, pop(operators));
            if (errorNumber != 0) {
                return errorNumber;
            }
        }
    }
    else {
        return 1;
    }
    return 0;
}
