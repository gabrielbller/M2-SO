#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "schedule_fcfs.h"
#include "schedule_rr.h"
#include "schedule_rr_p.h"
#define SIZE 100

char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}


int main(int argc, char *argv[])
{

    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen("rr-schedule.txt","r");

    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add_fcfs(name, priority, burst);

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    schedule_fcfs();

    return 0;
}
