#ifndef STACK_H
#define STACK_H

#ifndef MAX_NAME
#define MAX_NAME 50
#endif
#ifndef MAX_TUGAS
#define MAX_TUGAS 200
#endif

typedef struct {
    char data[MAX_TUGAS][MAX_NAME];
    int top;
} Stack;

void stack_init(Stack* s);
int  stack_empty(Stack* s);

#endif /* STACK_H */