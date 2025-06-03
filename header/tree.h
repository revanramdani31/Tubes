// tree.h
#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#define MAX_NAME 50
#define MAX_DESC 120
#define DATE_LEN 16
#define MAX_DEPTH 20

typedef enum {
    TODO,
    IN_PROGRESS,
    DONE
} Status;

typedef struct TreeNode {
    char name[MAX_NAME];
    char desc[MAX_DESC];
    int est_hours;
    char deadline[DATE_LEN];
    Status status;

    struct TreeNode* first_child;   // menunjuk ke anak pertama
    struct TreeNode* next_sibling;  // menunjuk ke saudara berikutnya
} TreeNode;

// Fungsi-fungsi utilitas
const char* statusStr(Status s);

// Membuat simpul baru
TreeNode* node_create(const char* name, const char* desc, int est_hours, const char* deadline);

// Menambahkan anak ke simpul induk
void node_add_child(TreeNode* parent, TreeNode* child);

// Mencari simpul berdasarkan nama
TreeNode* node_find(TreeNode* root, const char* target_name);

// Menampilkan pohon
void node_print(TreeNode* root, int level);

// Menghitung total dan tugas selesai
void node_count(TreeNode* root, int* total, int* done);

// Menyimpan dan memuat pohon ke/dari file
void node_save(FILE* file, TreeNode* root, int level);
TreeNode* node_load(FILE* file);

// Menghapus seluruh pohon dari memori
void free_tree(TreeNode* root);

// Menghapus simpul berdasarkan nama
int node_delete(TreeNode* parent, const char* target_name);

// Mengedit isi simpul
void node_edit(TreeNode* node);

#endif