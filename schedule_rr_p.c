#include <stdlib.h>
#include "CPU.h"
#include "list.h"
#include "task.h"

int tid_counter_p = 0;
struct node *TASK_LIST_p = NULL;

// Definição da estrutura "node"
struct node {
    Task *task;
    struct node *prev;
    struct node *next;
};

// Adiciona uma nova tarefa na lista de tarefas com prioridade
void add_rp(char *name, int priority, int burst) {
    Task *new_task = malloc(sizeof(Task));
    if (new_task == NULL) {
        // Tratar erro de alocação de memória
        return;
    }
    new_task->name = name;
    new_task->tid = ++tid_counter_p;
    new_task->priority = priority;
    new_task->burst = burst;
    insert_task(&TASK_LIST_p, new_task);
}

// Troca a posição de duas tarefas na lista
void swap(struct node *a, struct node *b) {
    Task *temp = a->task;
    a->task = b->task;
    b->task = temp;
}

// Ordena a lista de tarefas por prioridade usando o algoritmo Quick Sort
void quick_sort(struct node *low, struct node *high) {
    if (high != NULL && low != high && low != high->next) {
        struct node *pivot = partition(low, high);
        quick_sort(low, pivot->prev);
        quick_sort(pivot->next, high);
    }
}

// Particiona a lista para o Quick Sort
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

// Executa o escalonamento Round-Robin com prioridade
void schedule_rr_p() {
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
                delete_task(&TASK_LIST_p, temp->task);
            }
            temp = temp->next;
        }
    }
}
