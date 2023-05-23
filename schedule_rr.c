#include <stdlib.h>
#include "CPU.h"
#include "list.h"
#include "task.h"
#include "schedule_rr.h"

int tid_counter_rr = 0;
struct node *task_list_rr = NULL;

// Add a new task to the Round Robin (RR) task list
void add_RR(char *name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->tid = ++tid_counter_rr;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&task_list_rr, newTask);
}

// Schedule tasks using the Round Robin (RR) scheduling algorithm
void schedule_RR()
{
    struct node *current_task = task_list_rr;
    while (current_task != NULL)
    {
        Task *task = current_task->task;
        if (task->burst > QUANTUM)
        {
            // Execute the task for the duration of the quantum
            run(task, QUANTUM);
            task->burst -= QUANTUM;
        }
        else
        {
            // Execute the remaining part of the task
            run(task, task->burst);
            // Remove the task from the list
            struct node *next_task = current_task->next;
            delete(&task_list_rr, task);
            current_task = next_task;
            continue; // Continue directly to avoid advancing current_task
        }
        current_task = current_task->next;
    }
}
