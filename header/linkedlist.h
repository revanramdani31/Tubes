#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* createLinkedListNode(void* data);
void appendToList(LinkedListNode** head, void* data);
void removeFromList(LinkedListNode** head, void* data_to_remove, int free_data);
void freeList(LinkedListNode** head, void (*free_data_func)(void*));

#endif // LINKEDLIST_H