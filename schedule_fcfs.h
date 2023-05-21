#ifndef SCHEDULE_FCFS_H
#define SCHEDULE_FCFS_H

#include "list.h"
#include "task.h"

// function to add a task to the task list
void add_FCFS(char *name, int priority, int burst);

// function to execute the task scheduling
void schedule_FCFS();

#endif /* SCHEDULE_FCFS_H */
