#include "schedule_fcfs.h"
#include "list.h"
#include "task.h"
#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>

int tid_counter = 0;
struct node *task_list = NULL;

void add_FCFS(char *name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->tid = ++tid_counter;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&task_list, newTask);
}

void schedule_FCFS()
{
    if (task_list == NULL) {
        printf("A lista de tarefas esta vazia.\n");
        return;
    }

    struct node *current_task = task_list;
    while (current_task != NULL) {
        printf("Executando tarefa: %s\n", current_task->task->name);

        int remaining_burst = current_task->task->burst;
        while (remaining_burst > 0) {
            int slice = (remaining_burst < QUANTUM) ? remaining_burst : QUANTUM;
            run(current_task->task, slice);
            remaining_burst -= slice;
        }

        current_task = current_task->next;
    }

    printf("Todas as tarefas foram executadas.\n");
}
