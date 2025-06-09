#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

// --- Definisi Struktur Dasar ---
// Node generik untuk linked list
typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

// --- Prototipe Fungsi ---
LinkedListNode* createLinkedListNode(void* data);

#endif // LINKEDLIST_H