// inclui os arquivos header necess�rios
#include "schedule_fcfs.h"
#include "list.h"
#include "task.h"
#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>

// declara��o da lista de tarefas
struct node *task_list = NULL;

// adiciona uma tarefa � lista
void add_fcfs(char *name, int priority, int burst)
{
    // aloca espa�o na mem�ria para a nova tarefa
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    // adiciona a nova tarefa � lista
    insert(&task_list, newTask);
}

// invoca o escalonador
void schedule_fcfs()
{
    // percorre a lista de tarefas e executa cada uma delas
    struct node *current_task = task_list;
    while (current_task != NULL)
    {
        run(current_task->task, current_task->task->burst);
        current_task = current_task->next;
    }
}
