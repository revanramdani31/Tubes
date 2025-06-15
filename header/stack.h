#ifndef STACK_H
#define STACK_H

#include "utils.h"
#include "undo.h"

typedef struct StackNode {
    void* data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
    int size;
} Stack;

typedef struct {
    char taskId[MAX_ID_LEN];
    TaskStatus oldStatus;
    TaskStatus newStatus;
    char timestamp[DATE_LEN];
    char userId[MAX_ID_LEN];
}TaskHistory;

// Basic stack operations
Stack* createStack();
void push(Stack* s, void* data);
void* pop(Stack* s);
void* peek(Stack* s);
int isEmpty(Stack* s);
void freeStack(Stack* s);

// Undo-specific operations
void pushUndoAction(Stack* s, UndoAction* action);
UndoAction* popUndoAction(Stack* s);
void freeStackAndActions(Stack* s);
void recordTaskStatusChange(const char* taskId, TaskStatus oldStatus, 
                          TaskStatus newStatus, const char* userId);
void displayTaskHistory(const char* taskId);
void analyzeTaskStatusChanges(const char* taskId);

// Task status string array
extern const char* taskStatusToString[];

#endif 