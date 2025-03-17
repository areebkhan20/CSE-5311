#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

bool push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return false;
    }
    s->arr[++(s->top)] = value;
    return true;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1; 
    }
    return s->arr[(s->top)--];
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->arr[s->top];
}

int main() {
    Stack s;
    initialize(&s);
    
    printf("Pushing elements: 10, 20, 30\n");
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    
    printf("Top element: %d\n", peek(&s));
    printf("Popped element: %d\n", pop(&s));
    printf("Top element after pop: %d\n", peek(&s));
    
    return 0;
}