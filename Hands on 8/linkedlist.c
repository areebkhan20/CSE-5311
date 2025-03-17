#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data;
    int next; 
} Node;

typedef struct {
    Node nodes[MAX_SIZE];
    int head; 
    int free; 
    int size; 
} LinkedList;

void initialize(LinkedList *list) {
    list->head = -1; 
    list->size = 0;
    
    for (int i = 0; i < MAX_SIZE - 1; i++) {
        list->nodes[i].next = i + 1;
    }
    list->nodes[MAX_SIZE - 1].next = -1; 
    list->free = 0; 
}

bool isEmpty(LinkedList *list) {
    return list->size == 0;
}

bool isFull(LinkedList *list) {
    return list->size == MAX_SIZE;
}

int getNode(LinkedList *list) {
    if (list->free == -1) {
        return -1; 
    }
    
    int newNode = list->free;
    list->free = list->nodes[newNode].next;
    list->nodes[newNode].next = -1; 
    return newNode;
}

void releaseNode(LinkedList *list, int index) {
    list->nodes[index].next = list->free;
    list->free = index;
}

bool insertAtBeginning(LinkedList *list, int value) {
    if (isFull(list)) {
        printf("List is full\n");
        return false;
    }
    
    int newNode = getNode(list);
    if (newNode == -1) {
        return false; 
    }
    
    list->nodes[newNode].data = value;
    list->nodes[newNode].next = list->head;
    list->head = newNode;
    list->size++;
    return true;
}

bool insertAtEnd(LinkedList *list, int value) {
    if (isFull(list)) {
        printf("List is full\n");
        return false;
    }
    
    int newNode = getNode(list);
    if (newNode == -1) {
        return false; 
    }
    
    list->nodes[newNode].data = value;
    list->nodes[newNode].next = -1; 
    
    if (isEmpty(list)) {
        list->head = newNode; 
    } else {
        int current = list->head;
        while (list->nodes[current].next != -1) {
            current = list->nodes[current].next;
        }
        list->nodes[current].next = newNode;
    }
    
    list->size++;
    return true;
}

bool deleteNode(LinkedList *list, int value) {
    if (isEmpty(list)) {
        printf("List is empty\n");
        return false;
    }
    
    if (list->nodes[list->head].data == value) {
        int temp = list->head;
        list->head = list->nodes[list->head].next;
        releaseNode(list, temp);
        list->size--;
        return true;
    }
    
    int current = list->head;
    while (list->nodes[current].next != -1 && 
           list->nodes[list->nodes[current].next].data != value) {
        current = list->nodes[current].next;
    }
    
    if (list->nodes[current].next == -1) {
        printf("Value not found\n");
        return false;
    }
    
    int temp = list->nodes[current].next;
    list->nodes[current].next = list->nodes[temp].next;
    releaseNode(list, temp);
    list->size--;
    return true;
}

bool search(LinkedList *list, int value) {
    if (isEmpty(list)) {
        return false;
    }
    
    int current = list->head;
    while (current != -1) {
        if (list->nodes[current].data == value) {
            return true;
        }
        current = list->nodes[current].next;
    }
    
    return false;
}

void printList(LinkedList *list) {
    if (isEmpty(list)) {
        printf("List is empty\n");
        return;
    }
    
    printf("List: ");
    int current = list->head;
    while (current != -1) {
        printf("%d ", list->nodes[current].data);
        current = list->nodes[current].next;
    }
    printf("\n");
}

int main() {
    LinkedList list;
    initialize(&list);
    
    printf("Inserting elements: 5, 10, 20\n");
    insertAtBeginning(&list, 10);
    insertAtEnd(&list, 20);
    insertAtBeginning(&list, 5);
    
    printList(&list);
    
    printf("Searching for 20: %s\n", search(&list, 20) ? "Found" : "Not found");
    printf("Searching for 30: %s\n", search(&list, 30) ? "Found" : "Not found");
    
    printf("Deleting element 10\n");
    deleteNode(&list, 10);
    printList(&list);
    
    return 0;
}