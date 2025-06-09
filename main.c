#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "queue.h"

int main() {
    printf("=== Memulai Uji Coba Modul ===\n\n");

    //------------------------------------//
    //      UJI COBA LINKED LIST          //
    //------------------------------------//
    printf("--- UJI COBA LINKED LIST ---\n");
    printf("1. Membuat node baru...\n");

    // Membuat data sederhana untuk disimpan di node
    char* data1 = "Data String Pertama";
    
    // 1. Menggunakan fungsi dari linkedlist.c
    LinkedListNode* node1 = createLinkedListNode(data1);

    if (node1) {
        printf("   -> Node berhasil dibuat dengan data: \"%s\"\n", (char*)node1->data);
    } else {
        printf("   -> Gagal membuat node.\n");
        return 1; // Keluar jika gagal
    }
    
    // Penting: Selalu bebaskan memori setelah selesai digunakan
    free(node1);
    printf("2. Memori untuk node linked list telah dibebaskan.\n\n");


    //------------------------------------//
    //         UJI COBA QUEUE             //
    //------------------------------------//
    printf("--- UJI COBA QUEUE ---\n");
    printf("1. Membuat queue baru...\n");

    // 2. Menggunakan fungsi dari queue.c
    Queue* myQueue = createQueue();

    if (isQueueEmpty(myQueue)) {
        printf("   -> Queue berhasil dibuat dan saat ini kosong.\n");
    }

    printf("2. Menambahkan 3 item ke dalam queue (enqueue)...\n");

    // Membuat dan menambahkan item 1
    BatchDeleteItem* item1 = (BatchDeleteItem*)malloc(sizeof(BatchDeleteItem));
    strcpy(item1->taskId, "TSK_A");
    enqueueBatchItem(myQueue, item1);
    printf("   -> Item '%s' ditambahkan. Jumlah item di queue: %d\n", item1->taskId, myQueue->count);

    // Membuat dan menambahkan item 2
    BatchDeleteItem* item2 = (BatchDeleteItem*)malloc(sizeof(BatchDeleteItem));
    strcpy(item2->taskId, "TSK_B");
    enqueueBatchItem(myQueue, item2);
    printf("   -> Item '%s' ditambahkan. Jumlah item di queue: %d\n", item2->taskId, myQueue->count);

    // Membuat dan menambahkan item 3
    BatchDeleteItem* item3 = (BatchDeleteItem*)malloc(sizeof(BatchDeleteItem));
    strcpy(item3->taskId, "TSK_C");
    enqueueBatchItem(myQueue, item3);
    printf("   -> Item '%s' ditambahkan. Jumlah item di queue: %d\n", item3->taskId, myQueue->count);

    printf("3. Mengeluarkan item dari queue (dequeue) untuk tes urutan FIFO...\n");
    // Selama queue tidak kosong, keluarkan item
    while (!isQueueEmpty(myQueue)) {
        BatchDeleteItem* dequeuedItem = dequeueBatchItem(myQueue);
        if (dequeuedItem) {
            printf("   -> Item dikeluarkan: %s\n", dequeuedItem->taskId);
            free(dequeuedItem); // Bebaskan memori item setelah diproses
        }
    }

    if (isQueueEmpty(myQueue)) {
        printf("4. Semua item telah dikeluarkan. Queue kembali kosong.\n");
    }

    // 3. Membebaskan memori queue itu sendiri
    freeQueue(myQueue);
    printf("5. Memori untuk struktur queue telah dibebaskan.\n\n");


    printf("=== Uji Coba Selesai ===\n");
    return 0;
}