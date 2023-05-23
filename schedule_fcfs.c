#include "schedule_fcfs.h"
#include "list.h"
#include "task.h"
#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>

int tid_counter = 0;           // Global variable to keep track of task IDs
struct node *task_list_fcfs = NULL;

// Function to add a new task to the FCFS scheduler
void add_FCFS(char *name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task)); // Allocate memory for a new task
    newTask->name = name;                 // Set the name of the task
    newTask->tid = ++tid_counter;         // Assign a unique task ID
    newTask->priority = priority;         // Set the priority of the task
    newTask->burst = burst;               // Set the burst time of the task
    insert(&task_list_fcfs, newTask);          // Insert the task into the task list
}

// Function to schedule tasks using the FCFS algorithm
void schedule_FCFS()
{
    if (task_list_fcfs == NULL)
    {
        printf("A lista de tarefas esta vazia.\n");
        return;
    }

    struct node *current_task = task_list_fcfs; // Pointer to traverse the task list
    while (current_task != NULL)
    {
        printf("Executando tarefa: %s\n", current_task->task->name);

        int remaining_burst = current_task->task->burst; // Remaining burst time of the task
        while (remaining_burst > 0)
        {
            int slice = (remaining_burst < QUANTUM) ? remaining_burst : QUANTUM;
            // Run the task for a time slice (QUANTUM) or the remaining burst time, whichever is smaller
            run(current_task->task, slice);
            remaining_burst -= slice; // Decrement the remaining burst time
        }

        current_task = current_task->next; // Move to the next task in the list
    }

    printf("Todas as tarefas foram executadas.\n");
}
