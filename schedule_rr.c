#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "task.h"
#include "schedule_rr.h"

// length of a time quantum
#define QUANTUM 10

// the list of tasks
struct node *task_list = NULL;

// add a new task to the list of tasks
void add(char *name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->tid = rand() % 1000;
    newTask->priority = priority;
    newTask->burst = burst;

    insert(&task_list, newTask);
}

// invoke the scheduler
void schedule()
{
    int time = 0;
    struct node *current_task = task_list;

    while (task_list != NULL)
    {
        if (current_task == NULL)
        {
            current_task = task_list;
        }
        else
        {
            current_task = current_task->next;
        }

        if (current_task->task->burst > QUANTUM)
        {
            // run the task for a time slice of the quantum length
            run(current_task->task, QUANTUM);
            current_task->task->burst -= QUANTUM;
            time += QUANTUM;

            // move the task to the end of the list
            delete (&task_list, current_task->task);
            insert(&task_list, current_task->task);
        }
        else
        {
            // run the task for its entire remaining burst time
            run(current_task->task, current_task->task->burst);
            time += current_task->task->burst;

            // remove the task from the list
            delete (&task_list, current_task->task);
        }
    }

    printf("All tasks completed. Total time: %d\n", time);
}

// run the specified task for the following time slice
void run(Task *task, int slice)
{
    printf("Running task = [%s] [%d] [%d] for %d units.\n", task->name, task->priority, task->burst, slice);
}