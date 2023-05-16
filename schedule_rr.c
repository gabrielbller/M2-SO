/*// inclui os arquivos header necess�rios
#include "schedule_rr.h"
#include "list.h"
#include "task.h"
#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>

// declara��o da lista de tarefas
struct node *task_list = NULL;

// adiciona uma tarefa � lista
void add_rr(char *name, int priority, int burst)
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
void schedule_rr()
{
    // percorre a lista de tarefas e executa cada uma delas por um tempo limitado (quantum)
    struct node *current_task = task_list;
    while (current_task != NULL)
    {
        // mant�m o controle do tempo restante para a tarefa atual
        int remaining_burst = current_task->task->burst;
        // executa a tarefa em segmentos de tamanho igual ao quantum
        while (remaining_burst > 0)
        {
            if (remaining_burst > QUANTUM)
            {
                // se o tempo restante for maior que o quantum, executa o quantum da tarefa
                run(current_task->task, QUANTUM);
                // subtrai o tempo do quantum do tempo restante da tarefa
                remaining_burst -= QUANTUM;
            }
            else
            {
                // se o tempo restante for menor ou igual ao quantum, executa o tempo restante da tarefa
                run(current_task->task, remaining_burst);
                // define o tempo restante como zero para sair do loop interno
                remaining_burst = 0;
            }
        }
        // passa para a pr�xima tarefa na lista
        current_task = current_task->next;
    }
}

*/
