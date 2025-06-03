#ifndef QUEUE_H
#define QUEUE_H

#ifndef MAX_NAME
#define MAX_NAME 50
#endif
#ifndef MAX_TUGAS
#define MAX_TUGAS 200
#endif

typedef struct {
    char tugas[MAX_TUGAS][MAX_NAME];
    int prio[MAX_TUGAS];
    int count;
} PQueue;

void pq_init(PQueue* q);
int  pq_empty(PQueue* q);
void pq_enqueue(PQueue* q, const char* t, int p);
char* pq_dequeue(PQueue* q);
void pq_print(PQueue* q);

#endif /* QUEUE_H */