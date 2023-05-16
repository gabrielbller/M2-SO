// inclui os arquivos header necessários
#include "schedule_fcfs.h"
#include "list.h"
#include "task.h"
#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>

// declaração da lista de tarefas
struct node *task_list = NULL;

// adiciona uma tarefa à lista
void add_fcfs(char *name, int priority, int burst)
{
    // aloca espaço na memória para a nova tarefa
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    // adiciona a nova tarefa à lista
    insert(&task_list, newTask);
}

// invoca o escalonador
void schedule_fcfs()
{
    // percorre a lista de tarefas e executa cada uma delas com um slice máximo de 30 unidades de tempo
    struct node *current_task = task_list;
    int slice = 0;
    while (current_task != NULL)
    {
        if (slice < 30) {
            int remaining_burst = current_task->task->burst - slice;
            run(current_task->task, remaining_burst);
            slice += remaining_burst;
            current_task = current_task->next;
        } else {
            // interrompe a execução da tarefa e a adiciona novamente à lista de tarefas
            int remaining_burst = current_task->task->burst - slice;
            current_task->task->burst = remaining_burst;
            delete(&task_list, current_task->task);
            insert(&task_list, current_task->task);
            current_task = task_list;
            slice = 0;
        }
    }
}
