#include <stdio.h>
#include <stdlib.h>
#include "CPU.h"
#include "task.h"
#include "list.h"
#include "schedule_rr_p.h"
#include "driver.c"

// global variable for keeping track of system time
int system_time = 0;

// function to schedule tasks using the RR_p algorithm
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

    in = fopen("rr-schedule_pri.txt", "r");
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
        // find the task with the highest priority that is ready to run
        current_task = find_highest_priority(&head);

        // run the current task for a time quantum
        run(current_task, QUANTUM);

        // update the system time and the task's remaining burst time
        system_time += QUANTUM;
        current_task->burst -= QUANTUM;

        // if the task has completed, remove it from the list
        if (current_task->burst <= 0) {
            delete(&head, current_task);
        }
        // if the task still has burst time remaining, insert it back into the list
        else {
            insert(&head, current_task);
        }
    }
}
