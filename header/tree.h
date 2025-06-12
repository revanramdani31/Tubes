// tree.h
#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#define MAX_ID_LEN 50
#define MAX_NAME_LEN 100
#define MAX_DESC_LEN 500
#define DATE_LEN 11
#define MAX_LINE_LEN 1024

typedef enum {
    TASK_STATUS_BARU,
    TASK_STATUS_DIKERJAKAN,
    TASK_STATUS_SELESAI,
    TASK_STATUS_TERTUNDA,
    TASK_STATUS_COUNT
} TaskStatus;

typedef enum {
    TASK_PRIORITY_RENDAH,
    TASK_PRIORITY_SEDANG,
    TASK_PRIORITY_TINGGI,
    TASK_PRIORITY_COUNT
} TaskPriority;

extern const char* taskStatusToString[];
extern const char* taskPriorityToString[];

// Task structure using tree structure
typedef struct Task {
    char taskId[MAX_ID_LEN];
    char taskName[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    char projectId[MAX_ID_LEN];
    char parentTaskId[MAX_ID_LEN];  // Store parent task ID for loading/saving
    struct Task* parent;            // Parent node
    struct Task* firstChild;        // First child node
    struct Task* nextSibling;       // Next sibling node
    TaskStatus status;
    TaskPriority priority;
    char dueDate[DATE_LEN];
} Task;

TaskStatus getTaskStatusFromInput();
TaskPriority getTaskPriorityFromInput();
Task* createTaskInternal(const char* id, const char* name, const char* desc,
                        const char* projectId, const char* parentTaskId,
                        TaskStatus status, TaskPriority priority, const char* dueDate);
void addChildTask(Task* parentTask, Task* childTask);
Task* findTaskById(Task* root, const char* taskId);
void displayTaskTree(Task* task, int level);
void displayWBSTree(Task* task, int level, int isLastChild);
void displayWBSHeader();
void displayWBSFooter();
void editTaskDetails(Task* task);
void deepFreeTask(Task* task);
void findAndPrintTasksByStatus(Task* root, TaskStatus status, int* count, int level);
void findAndPrintTasksByPriority(Task* root, TaskPriority priority, int* count, int level);
void searchTasksByName(Task* root, const char* searchTerm, int* count, int level);



#endif /* TREE_H */