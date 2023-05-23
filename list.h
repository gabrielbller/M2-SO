#ifndef LIST_H
#define LIST_H
#include "task.h"

struct node {
    Task *task;
    struct node *next;
    struct node *prev;
};

// Function prototype for clear_list
void clear_list(struct node **head);
void insert(struct node **head, Task *task);
void delete(struct node **head, Task *task);
void traverse(struct node *head);
#endif
