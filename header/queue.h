#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h" // Menggunakan definisi LinkedListNode

// --- Definisi Konstanta & Struktur Spesifik Queue ---
#define MAX_ID_LEN 50

// Item spesifik yang akan disimpan di dalam queue untuk batch delete
typedef struct BatchDeleteItem {
    char taskId[MAX_ID_LEN];
} BatchDeleteItem;

// Definisi struktur Queue
typedef struct Queue {
    LinkedListNode* front;
    LinkedListNode* rear;
    int count;
} Queue;

// --- Prototipe Fungsi Queue ---
Queue* createQueue();
int isQueueEmpty(Queue* q);
void enqueueBatchItem(Queue* q, BatchDeleteItem* item);
BatchDeleteItem* dequeueBatchItem(Queue* q);
void freeQueueAndItems(Queue* q);
void freeQueue(Queue* q);

#endif // QUEUE_H