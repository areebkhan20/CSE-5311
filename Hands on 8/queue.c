#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int front, rear;
    int size; 
} Queue;

void initialize(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool isEmpty(Queue *q) {
    return q->size == 0;
}

bool isFull(Queue *q) {
    return q->size == MAX_SIZE;
}

bool enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return false;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->arr[q->rear] = value;
    q->size++;
    return true;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1; 
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return value;
}

int front(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->arr[q->front];
}

int main() {
    Queue q;
    initialize(&q);
    
    printf("Enqueuing elements: 10, 20, 30\n");
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    
    printf("Front element: %d\n", front(&q));
    printf("Dequeued element: %d\n", dequeue(&q));
    printf("Front element after dequeue: %d\n", front(&q));
    
    return 0;
}