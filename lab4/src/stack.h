#ifndef STACK_H
#define STACK_H
#define MAX_LEN 1001

typedef struct Stack {
    int expression[MAX_LEN];
    int head;
} st;

void push(st *stack, int sym);
int emptyCheck(const st *Stack);
int pop(st *stack);

#endif
