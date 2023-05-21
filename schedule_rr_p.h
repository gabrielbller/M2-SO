#ifndef SCHEDULE_RR_P_H
#define SCHEDULE_RR_P_H

#include "list.h"
#include "task.h"

// funcao para adicionar uma tarefa � lista de tarefas
void add_RR_P(char *name, int priority, int burst);
void swap(struct node *a, struct node *b);
void quick_sort(struct node *low, struct node *high);
struct node *partition(struct node *low, struct node *high);
// funcao para executar o escalonamento das tarefas
void schedule_RR_P();

#endif / SCHEDULE_RR_P_H * /
