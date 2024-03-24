#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure to represent the stack
struct Stack {
    int items[MAX_SIZE];
    int top;
};

// Function to initialize the stack
void initialize(struct Stack *stack) {
    stack->top = -1;
}

// Function to push an element to the stack
void push(struct Stack *stack, int value) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

// Function to pop an element from stack
int pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

int main(int argc, char *argv[]) {
    struct Stack stack;
    initialize(&stack);

    push(&stack, 54);
    push(&stack, 62);
    push(&stack, 43);

    printf("Popped element: %d\n", pop(&stack));
    printf("Popped element: %d\n", pop(&stack));
    printf("Popped element: %d\n", pop(&stack));

    if (isEmpty(&stack)) {
        printf("Stack is empty\n");
    } else {
        printf("Stack is not empty\n");
    }

    return 0;
}