// utils.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

static long id_counter = 0;

void generateUniqueId(const char* prefix, char* id_buffer) {
    static long simple_counter_for_id = 0;
    if (id_counter == 0 && simple_counter_for_id == 0) {
        id_counter = time(NULL) / 100;
        if (id_counter == 0) id_counter = 1;
    }
    simple_counter_for_id++;
    sprintf(id_buffer, "%s_%ld", prefix, simple_counter_for_id);
    printf("DEBUG: generateUniqueId: prefix='%s', simple_counter_for_id=%ld, id_buffer Hasil='%s'\n", 
           prefix, simple_counter_for_id, id_buffer);
}

int getSubMenuChoice(int max_option) {
    int sub_choice = -1;
    if (scanf("%d", &sub_choice) != 1) {
        printf("Input sub-menu tidak valid.\n");
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');
    if (sub_choice < 0 || sub_choice > max_option) {
        printf("Pilihan sub-menu tidak valid.\n");
        return -1;
    }
    return sub_choice;
}
