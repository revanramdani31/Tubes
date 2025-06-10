#include <stdio.h>
#include <string.h> // Diperlukan untuk strdup
#include "header/linkedlist.h"
#include "header/queue.h"
#include "src/queue.c"
#include "src/linkedlist.c"

// Fungsi bantuan untuk mencetak data string dari linked list
void printStringList(LinkedListNode* head) {
    if (!head) {
        printf("List kosong.\n");
        return;
    }
    LinkedListNode* current = head;
    int index = 1;
    while (current != NULL) {
        printf("Node %d: \"%s\"\n", index++, (char*)current->data);
        current = current->next;
    }
}

// Fungsi bantuan untuk membebaskan data (dalam kasus ini, string dari strdup)
void free_string_data(void* data) {
    free(data);
}

int main() {

    //==================================================
    //            UJI COBA LINKED LIST
    //==================================================
    printf("--- UJI COBA LINKED LIST ---\n\n");

    LinkedListNode* list_head = NULL;

    // 1. Menambahkan item ke list
    printf("1. Menambahkan tiga item ke dalam list...\n");
    // `strdup` digunakan untuk membuat salinan string di heap
    char* data1 = strdup("Tugas A: Analisis");
    char* data2 = strdup("Tugas B: Desain");
    char* data3 = strdup("Tugas C: Implementasi");

    appendToList(&list_head, data1);
    appendToList(&list_head, data2);
    appendToList(&list_head, data3);

    printf("Isi list saat ini:\n");
    printStringList(list_head);
    printf("\n");

    // 2. Menghapus item dari tengah list
    printf("2. Menghapus item kedua ('Tugas B: Desain')...\n");
    // Untuk removeFromList, kita perlu pointer ke data yang sama
    removeFromList(&list_head, data2, 1); // free_data=1 untuk membebaskan memori data2

    printf("Isi list setelah penghapusan:\n");
    printStringList(list_head);
    printf("\n");
    
    // 3. Menghapus item dari awal list
    printf("3. Menghapus item pertama ('Tugas A: Analisis')...\n");
    removeFromList(&list_head, data1, 1);

    printf("Isi list setelah penghapusan:\n");
    printStringList(list_head);
    printf("\n");

    // 4. Membebaskan seluruh sisa list
    printf("4. Membebaskan seluruh sisa memori list...\n");
    freeList(&list_head, free_string_data);
    printf("List setelah dibebaskan:\n");
    printStringList(list_head);
    printf("Uji coba Linked List selesai.\n");

    printf("\n==================================================\n\n");

    //==================================================
    //                UJI COBA QUEUE
    //==================================================
    printf("--- UJI COBA QUEUE ---\n\n");

    Queue* myQueue = createQueue();
    printf("Queue berhasil dibuat.\n");
    printf("Apakah queue kosong? %s\n\n", isQueueEmpty(myQueue) ? "Ya" : "Tidak");

    // 1. Menambahkan item ke antrian (enqueue)
    printf("1. Enqueue tiga item: 'Tiket 001', 'Tiket 002', 'Tiket 003'\n");
    enqueue(myQueue, strdup("Tiket 001"));
    enqueue(myQueue, strdup("Tiket 002"));
    enqueue(myQueue, strdup("Tiket 003"));
    printf("Jumlah item dalam queue: %d\n\n", myQueue->count);

    // 2. Mengeluarkan item dari antrian (dequeue)
    printf("2. Dequeue item dari queue...\n");
    while (!isQueueEmpty(myQueue)) {
        char* item = (char*)dequeue(myQueue);
        if (item) {
            printf("  - Item keluar: \"%s\"\n", item);
            free(item); // Bebaskan memori dari strdup
        }
    }
    printf("\n");

    // 3. Memeriksa apakah queue sudah kosong
    printf("Apakah queue sekarang kosong? %s\n", isQueueEmpty(myQueue) ? "Ya" : "Tidak");
    printf("Jumlah item dalam queue: %d\n\n", myQueue->count);

    // 4. Membebaskan memori queue
    printf("4. Membebaskan memori queue...\n");
    freeQueue(myQueue, free_string_data); // Tidak ada data tersisa, tapi aman untuk dipanggil
    myQueue = NULL; // Praktik yang baik
    printf("Uji coba Queue selesai.\n");

    return 0;
}