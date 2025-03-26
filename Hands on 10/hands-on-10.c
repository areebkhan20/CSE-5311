#include <stdio.h>
#include <stdlib.h>

// Node for our doubly linked list
typedef struct Node {
    int key;
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

// Doubly linked list
typedef struct List {
    Node* head;
    Node* tail;
    int size;
} List;

// Hash table
typedef struct HashTable {
    List** buckets;
    int size;      
    int count;     
    int (*hash_func)(int key, int size); 
} HashTable;

// Functions
List* creatList();
void destroyList(List* list);
Node* createNode(int key, int value);
void insertNode(List* list, int key, int value);
Node* findNode(List* list, int key);
void deleteNode(List* list, int key);
HashTable* createHashTable(int size, int (*hash_func)(int, int));
void destroyHashTable(HashTable* table);
void insert(HashTable* table, int key, int value);
int search(HashTable* table, int key);
void delete(HashTable* table, int key);
void resize(HashTable* table, int newSize);
int hashDivision(int key, int size);
int hashMultiplication(int key, int size);
int hashCombined(int key, int size);

// New linked list
List* createList() {
    List* list = (List*)malloc(sizeof(List));
    if (list) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

// Destroy linked list and free memory
void destroyList(List* list) {
    if (!list) return;
    
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

// Create new node
Node* createNode(int key, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node) {
        node->key = key;
        node->value = value;
        node->next = NULL;
        node->prev = NULL;
    }
    return node;
}

// Insert or create a node into the list
void insertNode(List* list, int key, int value) {
    if (!list) return;
    
    Node* existing = findNode(list, key);
    if (existing) {
        existing->value = value; 
        return;
    }
    
    Node* node = createNode(key, value);
    if (!node) return;
    
    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    
    list->size++;
}

// Find node
Node* findNode(List* list, int key) {
    if (!list) return NULL;
    
    Node* current = list->head;
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

// Delete a node
void deleteNode(List* list, int key) {
    if (!list) return;
    
    Node* node = findNode(list, key);
    if (!node) return;
    
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
    
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }
    
    free(node);
    list->size--;
}

// Create a new hash table
HashTable* createHashTable(int size, int (*hash_func)(int, int)) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;
    
    table->size = size;
    table->count = 0;
    table->hash_func = hash_func;
    
    table->buckets = (List**)calloc(size, sizeof(List*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    
    for (int i = 0; i < size; i++) {
        table->buckets[i] = createList();
        if (!table->buckets[i]) {
            for (int j = 0; j < i; j++) {
                destroyList(table->buckets[j]);
            }
            free(table->buckets);
            free(table);
            return NULL;
        }
    }
    
    return table;
}

// Destroy hash table and free memory
void destroyHashTable(HashTable* table) {
    if (!table) return;
    
    for (int i = 0; i < table->size; i++) {
        destroyList(table->buckets[i]);
    }
    
    free(table->buckets);
    free(table);
}

// Insert a key-value pair into the hash table
void insert(HashTable* table, int key, int value) {
    if (!table) return;
    
    int index = table->hash_func(key, table->size);
    
    Node* existing = findNode(table->buckets[index], key);
    if (!existing) {
        table->count++;
    }
    
    insertNode(table->buckets[index], key, value);
    
    if (table->count >= table->size) {
        resize(table, table->size * 2);
    }
}

// Search for key in the hash table
int search(HashTable* table, int key) {
    if (!table) return -1;
    
    int index = table->hash_func(key, table->size);
    
    Node* node = findNode(table->buckets[index], key);
    if (node) {
        return node->value;
    }
    
    return -1;  
}
void delete(HashTable* table, int key) {
    if (!table) return;
    
    int index = table->hash_func(key, table->size);
    
    Node* node = findNode(table->buckets[index], key);
    if (node) {
        deleteNode(table->buckets[index], key);
        table->count--;
        
        if (table->size > 10 && table->count <= table->size / 4) {
            resize(table, table->size / 2);
        }
    }
}

void resize(HashTable* table, int newSize) {
    if (!table || newSize < 1) return;
    
    List** newBuckets = (List**)calloc(newSize, sizeof(List*));
    if (!newBuckets) return;
    
    for (int i = 0; i < newSize; i++) {
        newBuckets[i] = createList();
        if (!newBuckets[i]) {
            for (int j = 0; j < i; j++) {
                destroyList(newBuckets[j]);
            }
            free(newBuckets);
            return;
        }
    }
    
    for (int i = 0; i < table->size; i++) {
        Node* current = table->buckets[i]->head;
        while (current) {
            int newIndex = table->hash_func(current->key, newSize);
            
            insertNode(newBuckets[newIndex], current->key, current->value);
            
            current = current->next;
        }
        
        destroyList(table->buckets[i]);
    }
    
    free(table->buckets);
    table->buckets = newBuckets;
    table->size = newSize;
}

// Division method
int hashDivision(int key, int size) {
    return (key % size + size) % size;
}

// Multiplication method
int hashMultiplication(int key, int size) {
    const double A = 0.6180339887;
    
    key = key >= 0 ? key : -key;
    
    double product = key * A;
    double fractional = product - (int)product;
    
    return (int)(size * fractional);
}

int hashCombined(int key, int size) {
    const double A = 0.6180339887;
    
    key = key >= 0 ? key : -key;
    
    double product = key * A;
    double fractional = product - (int)product;
    int hash1 = (int)(size * fractional);
    
    return hash1 % size;
}

int main() {
    HashTable* table = createHashTable(10, hashCombined);
    if (!table) {
        printf("Failed to create hash table!\n");
        return 1;
    }
    
    printf("Inserting key-value pairs...\n");
    insert(table, 5, 500);
    insert(table, 15, 1500);
    insert(table, 25, 2500);
    insert(table, 35, 3500);
    insert(table, 45, 4500);
    
    printf("Searching for keys...\n");
    printf("Key 5: %d\n", search(table, 5));
    printf("Key 15: %d\n", search(table, 15));
    printf("Key 25: %d\n", search(table, 25));
    printf("Key 35: %d\n", search(table, 35));
    printf("Key 45: %d\n", search(table, 45));
    printf("Key 55 (not inserted): %d\n", search(table, 55));
    
    printf("Deleting keys 15 and 35...\n");
    delete(table, 15);
    delete(table, 35);
    
    printf("Searching after deletion...\n");
    printf("Key 15 (deleted): %d\n", search(table, 15));
    printf("Key 35 (deleted): %d\n", search(table, 35));
    
    printf("Inserting many keys to trigger resize...\n");
    for (int i = 100; i < 120; i++) {
        insert(table, i, i * 100);
    }
    
    printf("Current table size: %d\n", table->size);
    
    printf("Deleting many keys to trigger resize (shrink)...\n");
    for (int i = 100; i < 120; i++) {
        delete(table, i);
    }
    
    printf("Current table size after shrinking: %d\n", table->size);
    
    destroyHashTable(table);
    
    return 0;
}