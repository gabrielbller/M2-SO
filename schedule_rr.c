#include <stdlib.h>
#include "CPU.h"
#include "list.h"
#include "task.h"
#include "schedule_rr.h"

int tid_counter = 0;
struct node *task_list = NULL;

void add_RR(char *name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->tid = ++tid_counter;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&task_list, newTask);
}

void schedule_RR()
{
    struct node *current_task = task_list;
    while (current_task != NULL)
    {
        Task *task = current_task->task;
        if (task->burst > QUANTUM)
        {
            // Executa a tarefa pelo tempo do quantum
            run(task, QUANTUM);
            task->burst -= QUANTUM;
        }
        else
        {
            // Executa o restante da tarefa
            run(task, task->burst);
            // Remove a tarefa da lista
            struct node *next_task = current_task->next;
            delete(&task_list, task);
            current_task = next_task;
            continue; // Continue diretamente para evitar o avanço de current_task
        }
        current_task = current_task->next;
    }
}
