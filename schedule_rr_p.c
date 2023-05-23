#include <stdlib.h>
#include "CPU.h"
#include "list.h"
#include "task.h"

int tid_counter_p = 0;
struct node *TASK_LIST_p = NULL;
struct node *partition(struct node *low, struct node *high);

// Add a new task to the priority-based Round Robin (RR_P) task list
void add_RR_P(char *name, int priority, int burst) {
    Task *new_task = malloc(sizeof(Task));
    if (new_task == NULL) {
        // Handle memory allocation error
        return;
    }
    new_task->name = name;
    new_task->tid = ++tid_counter_p;
    new_task->priority = priority;
    new_task->burst = burst;
    insert(&TASK_LIST_p, new_task);
}

// Swap the positions of two tasks in the list
void swap(struct node *a, struct node *b) {
    Task *temp = a->task;
    a->task = b->task;
    b->task = temp;
}

// Sort the task list by priority using the Quick Sort algorithm
void quick_sort(struct node *low, struct node *high) {
    if (high != NULL && low != high && low != high->next) {
        struct node *pivot = partition(low, high);
        quick_sort(low, pivot->prev);
        quick_sort(pivot->next, high);
    }
}

// Partition the list for Quick Sort
struct node *partition(struct node *low, struct node *high) {
    Task *pivot = high->task;
    struct node *i = low->prev;

    for (struct node *j = low; j != high; j = j->next) {
        if (j->task->priority < pivot->priority) {
            i = (i == NULL) ? low : i->next;
            swap(i, j);
        }
    }

    i = (i == NULL) ? low : i->next;
    swap(i, high);
    return i;
}

// Execute the Round Robin with priority (RR_P) scheduling
void schedule_RR_P() {
    struct node *temp;
    while (TASK_LIST_p != NULL) {
        temp = TASK_LIST_p;
        quick_sort(temp, NULL);
        while (temp != NULL) {
            if (temp->task->burst > QUANTUM) {
                run(temp->task, QUANTUM);
                temp->task->burst -= QUANTUM;
            } else {
                run(temp->task, temp->task->burst);
                delete(&TASK_LIST_p, temp->task);
            }
            temp = temp->next;
        }
    }
}
