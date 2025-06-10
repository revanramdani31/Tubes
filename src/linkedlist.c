#include "../header/linkedlist.h"
#include <stdio.h>

LinkedListNode* createLinkedListNode(void* data) {
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (!newNode) {
        perror("Failed to allocate LinkedListNode");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendToList(LinkedListNode** head, void* data) {
    LinkedListNode* newNode = createLinkedListNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        LinkedListNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void removeFromList(LinkedListNode** head, void* data_to_remove, int free_data) {
    if (!*head || !data_to_remove) return;

    LinkedListNode* current = *head;
    LinkedListNode* prev = NULL;

    if (current->data == data_to_remove) {
        *head = current->next;
        if (free_data) free(current->data);
        free(current);
        return;
    }

    while (current != NULL && current->data != data_to_remove) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        prev->next = current->next;
        if (free_data) free(current->data);
        free(current);
    }
}

void freeList(LinkedListNode** head, void (*free_data_func)(void*)) {
    LinkedListNode* current = *head;
    LinkedListNode* next_node;
    while (current != NULL) {
        next_node = current->next;
        if (free_data_func && current->data) {
            free_data_func(current->data);
        }
        free(current);
        current = next_node;
    }
    *head = NULL;
}