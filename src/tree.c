#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char* statusStr(Status s){
    switch(s){
        case TODO:        return "Belum dimulai";
        case IN_PROGRESS: return "Sedang dikerjakan";
        case DONE:        return "Selesai";
    }
    return "?";
}

TreeNode* node_create(const char* n,const char* d,int est,const char* dl){
    TreeNode* t = (TreeNode*)calloc(1, sizeof(TreeNode));
    strncpy(t->name, n, MAX_NAME);
    strncpy(t->desc, d, MAX_DESC);
    t->est_hours = est;
    strncpy(t->deadline, dl, DATE_LEN);
    t->status = TODO;
    t->first_child = NULL;
    t->next_sibling = NULL;
    return t;
}

void node_add_child(TreeNode* p, TreeNode* c){
    if(!p || !c) return;
    c->next_sibling = p->first_child;
    p->first_child = c;
}

TreeNode* node_find(TreeNode* r,const char* target){
    if(!r) return NULL;
    if(strcmp(r->name, target) == 0) return r;

    TreeNode* found = node_find(r->first_child, target);
    if(found) return found;
    return node_find(r->next_sibling, target);
}

void node_print(TreeNode* r, int lvl){
    if(!r) return;
    for(int i=0; i<lvl; i++) printf("  ");
    printf("- %s [%s] (ETC %dh, DL %s)\n", r->name, statusStr(r->status), r->est_hours, r->deadline);
    node_print(r->first_child, lvl+1);
    node_print(r->next_sibling, lvl);
}

void node_count(TreeNode* r, int* tot, int* done){
    if(!r) return;
    (*tot)++;
    if(r->status == DONE) (*done)++;
    node_count(r->first_child, tot, done);
    node_count(r->next_sibling, tot, done);
}

int node_delete(TreeNode* parent, const char* target){
    if(!parent) return 0;

    TreeNode* prev = NULL;
    TreeNode* curr = parent->first_child;
    while(curr){
        if(strcmp(curr->name, target) == 0){
            if(prev) prev->next_sibling = curr->next_sibling;
            else parent->first_child = curr->next_sibling;
            free_tree(curr);
            return 1;
        }
        if(node_delete(curr, target)) return 1;
        prev = curr;
        curr = curr->next_sibling;
    }
    return 0;
}