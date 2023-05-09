#include <stdio.h>
#include <stdlib.h>
#include "CPU.h"
#include "task.h"
#include "list.h"
#include "schedule_fcfs.h"
#include "driver.c"

// global variable for keeping track of system time
int system_time = 0;

// function to schedule tasks using the FCFS algorithm
void schedule() {
    struct node *head = NULL;
    Task *current_task = NULL;

    // create a list of tasks from the input file
    // in the format "[name], [priority], [burst]"
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen("rr-schedule.txt", "r");
    if (in == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(task, SIZE, in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp, ",");
        priority = atoi(strsep(&temp, ","));
        burst = atoi(strsep(&temp, ","));

        // add the task to the scheduler's list of tasks
        insert(&head, current_task);

        free(temp);
    }

    fclose(in);

    // loop until all tasks are completed
    while (head != NULL) {
        // get the first task in the list
        current_task = head->task;

        // run the current task until it is complete
        run(current_task, current_task->burst);

        // update the system time and remove the completed task from the list
        system_time += current_task->burst;
        delete(&head, current_task);
    }
}
