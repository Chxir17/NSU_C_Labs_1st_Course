#include "stack.h"

void push(st *stack, int sym) {
    if (stack->head < MAX_LEN) {
        stack->expression[stack->head] = sym;
        stack->head++;
    }
}

int emptyCheck(const st *Stack) {
    return ((Stack->head) == 0);
}

int pop(st *stack) {
    if ((stack->head) > 0) {
        stack->head--;
        return stack->expression[stack->head];
    }
    return 0;
}
