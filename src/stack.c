#include "stack.h"
#include <stdlib.h>

Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s) return NULL;
    s->top = NULL;
    s->size = 0;
    return s;
}

void push(Stack* s, void* data) {
    if (!s) return;
    
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) return;
    
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

void* pop(Stack* s) {
    if (!s || !s->top) return NULL;
    
    StackNode* temp = s->top;
    void* data = temp->data;
    s->top = temp->next;
    free(temp);
    s->size--;
    return data;
}

void* peek(Stack* s) {
    if (!s || !s->top) return NULL;
    return s->top->data;
}

int isEmpty(Stack* s) {
    return !s || !s->top;
}

void freeStack(Stack* s) {
    if (!s) return;
    
    while (!isEmpty(s)) {
        void* data = pop(s);
        if (data) free(data);
    }
    free(s);
} 

// Global stack for task history
static Stack* taskHistoryStack = NULL;

void recordTaskStatusChange(const char* taskId, TaskStatus oldStatus, 
                          TaskStatus newStatus, const char* userId) {
    if (!taskId || !userId) return;

    if (!taskHistoryStack) {
        taskHistoryStack = createStack();
        if (!taskHistoryStack) {
            printf("ERROR: Gagal membuat task history stack.\n");
            return;
        }
    }

    TaskHistory* history = (TaskHistory*)malloc(sizeof(TaskHistory));
    if (!history) {
        perror("Gagal alokasi TaskHistory");
        return;
    }

    strncpy(history->taskId, taskId, MAX_ID_LEN - 1);
    history->taskId[MAX_ID_LEN - 1] = '\0';

    history->oldStatus = oldStatus;
    history->newStatus = newStatus;

    time_t now = time(NULL);
    strftime(history->timestamp, DATE_LEN, "%Y-%m-%d", localtime(&now));

    strncpy(history->userId, userId, MAX_ID_LEN - 1);
    history->userId[MAX_ID_LEN - 1] = '\0';

    pushUndoAction(taskHistoryStack, (UndoAction*)history);
}

void displayTaskHistory(const char* taskId) {
    if (!taskId || !taskHistoryStack) return;

    printf("\nRiwayat Status Tugas [%s]:\n", taskId);
    printf("----------------------------------------\n");
    printf("Tanggal    | Status Lama -> Status Baru | User\n");
    printf("----------------------------------------\n");

    Stack* tempStack = createStack();
    if (!tempStack) return;

    // Pop all items to temp stack
    while (!isEmpty(taskHistoryStack)) {
        TaskHistory* history = (TaskHistory*)popUndoAction(taskHistoryStack);
        if (history && strcmp(history->taskId, taskId) == 0) {
            printf("%s | %s -> %s | %s\n",
                   history->timestamp,
                   taskStatusToString[history->oldStatus],
                   taskStatusToString[history->newStatus],
                   history->userId);
        }
        pushUndoAction(tempStack, (UndoAction*)history);
    }

    // Restore items back to original stack
    while (!isEmpty(tempStack)) {
        TaskHistory* history = (TaskHistory*)popUndoAction(tempStack);
        pushUndoAction(taskHistoryStack, (UndoAction*)history);
    }

    freeStack(tempStack);
    printf("----------------------------------------\n");
}

void analyzeTaskStatusChanges(const char* taskId) {
    if (!taskId || !taskHistoryStack) return;

    int statusCounts[TASK_STATUS_COUNT] = {0};
    int totalChanges = 0;

    Stack* tempStack = createStack();
    if (!tempStack) return;

    // Count status changes
    while (!isEmpty(taskHistoryStack)) {
        TaskHistory* history = (TaskHistory*)popUndoAction(taskHistoryStack);
        if (history && strcmp(history->taskId, taskId) == 0) {
            statusCounts[history->newStatus]++;
            totalChanges++;
        }
        pushUndoAction(tempStack, (UndoAction*)history);
    }

    // Restore items back to original stack
    while (!isEmpty(tempStack)) {
        TaskHistory* history = (TaskHistory*)popUndoAction(tempStack);
        pushUndoAction(taskHistoryStack, (UndoAction*)history);
    }

    freeStack(tempStack);

    // Display analysis
    printf("\nAnalisis Status Tugas [%s]:\n", taskId);
    printf("----------------------------------------\n");
    printf("Total perubahan status: %d\n", totalChanges);
    printf("\nDistribusi Status:\n");
    for (int i = 0; i < TASK_STATUS_COUNT; i++) {
        float percentage = totalChanges > 0 ? (float)statusCounts[i] / totalChanges * 100 : 0;
        printf("%s: %d kali (%.1f%%)\n", 
               taskStatusToString[i], statusCounts[i], percentage);
    }
    printf("----------------------------------------\n");
}

void countTasksAndStatus(Task* task, int* totalTasks, int* statusCounts) {
    if (!task) return;

    // Count this task
    (*totalTasks)++;
    statusCounts[task->status]++;

    // Count children
    Task* child = task->firstChild;
    while (child) {
        countTasksAndStatus(child, totalTasks, statusCounts);
        child = child->nextSibling;
    }
}
