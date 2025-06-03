#include "queue.h"
#include <string.h>
#include <stdio.h>

void pq_init(PQueue* q){
    q->count = 0;
}

int pq_empty(PQueue* q){
    return q->count == 0;
}

void pq_enqueue(PQueue* q, const char* t, int p){
    if(q->count >= MAX_TUGAS){
        puts("Antrian penuh!");
        return;
    }
    int i = q->count - 1;
    while(i >= 0 && p < q->prio[i]){
        strcpy(q->tugas[i+1], q->tugas[i]);
        q->prio[i+1] = q->prio[i];
        i--;
    }
    strcpy(q->tugas[i+1], t);
    q->prio[i+1] = p;
    q->count++;
}

char* pq_dequeue(PQueue* q){
    static char ret[MAX_NAME];
    if(pq_empty(q)){
        puts("Antrian kosong!");
        return NULL;
    }
    strcpy(ret, q->tugas[0]);
    for(int i = 1; i < q->count; i++){
        strcpy(q->tugas[i-1], q->tugas[i]);
        q->prio[i-1] = q->prio[i];
    }
    q->count--;
    return ret;
}

void pq_print(PQueue* q){
    puts("\n-- Antrian Tugas (Prioritas Rendah → Tinggi) --");
    for(int i=0; i<q->count; i++){
        printf("%d. %s (P=%d)\n", i+1, q->tugas[i], q->prio[i]);
    }
}