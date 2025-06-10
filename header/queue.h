#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h"

typedef struct {
    LinkedListNode* front;
    LinkedListNode* rear;
    int count;
} Queue;

Queue* createQueue();
int isQueueEmpty(Queue* q);
void enqueue(Queue* q, void* data);
void* dequeue(Queue* q);
void freeQueue(Queue* q, void (*free_data_func)(void*));

#endif // QUEUE_H