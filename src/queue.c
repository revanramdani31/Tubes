#include "../header/queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        perror("Failed to allocate Queue");
        exit(EXIT_FAILURE);
    }
    q->front = q->rear = NULL;
    q->count = 0;
    return q;
}

int isQueueEmpty(Queue* q) {
    return q == NULL || q->front == NULL;
}

void enqueue(Queue* q, void* data) {
    if (!q || !data) return;
    LinkedListNode* newNode = createLinkedListNode(data);
    if (!newNode) {
        free(data);
        perror("Failed to allocate Node for Queue");
        return;
    }
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

void* dequeue(Queue* q) {
    if (isQueueEmpty(q)) return NULL;
    LinkedListNode* temp = q->front;
    void* data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->count--;
    return data;
}

void freeQueue(Queue* q, void (*free_data_func)(void*)) {
    if (!q) return;
    freeList(&(q->front), free_data_func);
    free(q);
}