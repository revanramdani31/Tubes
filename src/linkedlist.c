#include "linkedlist.h"
#include <stdio.h>

LinkedListNode* createLinkedListNode(void* data) {
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (!newNode) {
        perror("Gagal alokasi LinkedListNode");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}