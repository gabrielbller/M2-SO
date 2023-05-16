#include "schedule_rr_p.h"
#include "list.h"
#include "task.h"
#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>

#define QUANTUM 10

// the list of tasks
struct node *task_list = NULL;

// add a task to the list
void add_rr_p(char *name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&task_list, newTask);
}

// invoke the scheduler
void schedule_rr_p()
{
    struct node *current_task = task_list;
    while (task_list != NULL)
    {
        for (int i = 0; i < QUANTUM && current_task != NULL; i++)
        {
            run(current_task->task, 1);
            current_task->task->burst -= 1;
            if (current_task->task->burst == 0)
            {
                delete (&task_list, current_task->task);
                current_task = task_list;
            }
            else
            {
                current_task = current_task->next;
            }
        }
        if (current_task != NULL)
        {
            delete (&task_list, current_task->task);
            insert(&task_list, current_task->task);
            current_task = task_list->next;
        }
    }
}
