#include "tree.h"

const char* taskStatusToString[] = {"Baru", "Dikerjakan", "Selesai", "Tertunda"};
const char* taskPriorityToString[] = {"Rendah", "Sedang", "Tinggi"};


TaskStatus getTaskStatusFromInput() {
    int choice = 0;
    printf("Pilih Status Tugas:\n");
    for (int i = 0; i < TASK_STATUS_COUNT; i++) {
        printf("%d. %s\n", i + 1, taskStatusToString[i]);
    }
    printf("Pilihan Status (1-%d): ", TASK_STATUS_COUNT);
    if (scanf("%d", &choice) != 1) choice = 0;
    while(getchar() != '\n');
    if (choice > 0 && choice <= TASK_STATUS_COUNT) return (TaskStatus)(choice - 1);
    printf("Pilihan tidak valid, status diatur ke BARU.\n");
    return TASK_STATUS_BARU;
}

TaskPriority getTaskPriorityFromInput() {
    int choice = 0;
    printf("Pilih Prioritas Tugas:\n");
    for (int i = 0; i < TASK_PRIORITY_COUNT; i++) {
        printf("%d. %s\n", i + 1, taskPriorityToString[i]);
    }
    printf("Pilihan Prioritas (1-%d): ", TASK_PRIORITY_COUNT);
    if (scanf("%d", &choice) != 1) choice = 0;
    while(getchar() != '\n');
    if (choice > 0 && choice <= TASK_PRIORITY_COUNT) return (TaskPriority)(choice - 1);
    printf("Pilihan tidak valid, prioritas diatur ke SEDANG.\n");
    return TASK_PRIORITY_SEDANG;
}

Task* createTaskInternal(const char* id, const char* name, const char* desc,
                        const char* projectId, const char* parentTaskId,
                        TaskStatus status, TaskPriority priority, const char* dueDate) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (!newTask) {
        perror("Gagal alokasi Task");
        return NULL;
    }

    strncpy(newTask->taskId, id, MAX_ID_LEN - 1);
    newTask->taskId[MAX_ID_LEN - 1] = '\0';

    strncpy(newTask->taskName, name, MAX_NAME_LEN - 1);
    newTask->taskName[MAX_NAME_LEN - 1] = '\0';

    strncpy(newTask->description, desc, MAX_DESC_LEN - 1);
    newTask->description[MAX_DESC_LEN - 1] = '\0';

    strncpy(newTask->projectId, projectId, MAX_ID_LEN - 1);
    newTask->projectId[MAX_ID_LEN - 1] = '\0';

    strncpy(newTask->parentTaskId, parentTaskId, MAX_ID_LEN - 1);
    newTask->parentTaskId[MAX_ID_LEN - 1] = '\0';

    newTask->status = status;
    newTask->priority = priority;

    if (dueDate && strlen(dueDate) > 0) {
        strncpy(newTask->dueDate, dueDate, DATE_LEN - 1);
    } else {
        newTask->dueDate[0] = '\0';
    }
    newTask->dueDate[DATE_LEN - 1] = '\0';

    newTask->parent = NULL;
    newTask->firstChild = NULL;
    newTask->nextSibling = NULL;

    return newTask;
}

void addChildTask(Task* parentTask, Task* childTask) {
    if (!parentTask || !childTask) return;
    childTask->parent = parentTask;

    if (!parentTask->firstChild) {
        parentTask->firstChild = childTask;
    } else {
        Task* sibling = parentTask->firstChild;
        while (sibling->nextSibling) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = childTask;
    }
}

Task* findTaskById(Task* root, const char* taskId) {
    if (!root || !taskId) return NULL;

    if (strcmp(root->taskId, taskId) == 0) {
        return root;
    }

    Task* found = findTaskById(root->firstChild, taskId);
    if (found) return found;

    return findTaskById(root->nextSibling, taskId);
}

void displayWBSHeader() {
    printf("\n╔════════════════════════ WORK BREAKDOWN STRUCTURE ════════════════════════╗\n");
}

void displayWBSFooter() {
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
}

void displayWBSTree(Task* task, int level, int isLastChild) {
    if (!task) return;

    // Print indentation and tree branches
    for (int i = 0; i < level - 1; i++) {
        printf("║   ");
    }
    
    if (level > 0) {
        if (isLastChild) {
            printf("╚═══");
        } else {
            printf("╠═══");
        }
    }

    // Print task status indicator
    char statusIndicator;
    switch (task->status) {
        case TASK_STATUS_BARU: statusIndicator = 'O'; break;
        case TASK_STATUS_DIKERJAKAN: statusIndicator = 'P'; break;
        case TASK_STATUS_SELESAI: statusIndicator = 'X'; break;
        case TASK_STATUS_TERTUNDA: statusIndicator = '-'; break;
        default: statusIndicator = '?'; break;
    }

    // Print priority indicator
    const char* priorityColor;
    switch (task->priority) {
        case TASK_PRIORITY_RENDAH: priorityColor = "[-]"; break;
        case TASK_PRIORITY_SEDANG: priorityColor = "[!]"; break;
        case TASK_PRIORITY_TINGGI: priorityColor = "[*]"; break;
        default: priorityColor = "[?]"; break;
    }

    // Print task information
    printf(" %c %s %s", statusIndicator, priorityColor, task->taskName);
    
    // Print additional task details
    if (strlen(task->dueDate) > 0) {
        printf(" (Due: %s)", task->dueDate);
    }
    printf(" [%s]\n", task->taskId);

    // Print task description with proper indentation
    if (strlen(task->description) > 0) {
        for (int i = 0; i < level; i++) {
            printf("║   ");
        }
        printf("    └─ %s\n", task->description);
    }

    // Process children
    Task* child = task->firstChild;
    while (child) {
        Task* nextChild = child->nextSibling;
        displayWBSTree(child, level + 1, nextChild == NULL);
        child = nextChild;
    }

    // Add spacing between siblings for better readability
    if (!isLastChild && level > 0) {
        for (int i = 0; i < level; i++) {
            printf("║   ");
        }
        printf("\n");
    }
}

void deepFreeTask(Task* task) {
    if (!task) return;

    // First free all children
    Task* child = task->firstChild;
    while (child) {
        Task* next = child->nextSibling;
        deepFreeTask(child);
        child = next;
    }

    // Then free this task
    free(task);
}

void findAndPrintTasksByStatus(Task* root, TaskStatus status, int* count, int level) {
    if (!root) return;

    if (root->status == status) {
        for (int i = 0; i < level; ++i) printf("  ");
        printf("|- [%s] %s (Prioritas: %s, Due: %s)\n",
               root->taskId, root->taskName,
               taskPriorityToString[root->priority],
               strlen(root->dueDate) > 0 ? root->dueDate : "N/A");
        (*count)++;
    }

    findAndPrintTasksByStatus(root->firstChild, status, count, level + 1);
    findAndPrintTasksByStatus(root->nextSibling, status, count, level);
}

void findAndPrintTasksByPriority(Task* root, TaskPriority priority, int* count, int level) {
    if (!root) return;

    if (root->priority == priority) {
        for (int i = 0; i < level; ++i) printf("  ");
        printf("|- [%s] %s (Status: %s, Due: %s)\n",
               root->taskId, root->taskName,
               taskStatusToString[root->status],
               strlen(root->dueDate) > 0 ? root->dueDate : "N/A");
        (*count)++;
    }

    findAndPrintTasksByPriority(root->firstChild, priority, count, level + 1);
    findAndPrintTasksByPriority(root->nextSibling, priority, count, level);
}

