#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "task.h"
#include "list.h"
#include "schedule_fcfs.h"
#include "schedule_rr.h"
#include "schedule_rr_p.h"

#define SIZE 100

char *strsep(char **stringp, const char *delim)
{
    char *rv = *stringp;
    if (rv)
    {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0;
    }
    return rv;
}

int menu()
{
    int option;
    while (1)
    {
        printf("Selecione uma opcao:\n");
        printf("1. Metodo FCFS\n");
        printf("2. Metodo Round Robin sem prioridade (RR)\n");
        printf("3. Metodo Round Robin com prioridade (RR_P)\n");
        scanf("%d", &option);
        if (option >= 1 && option <= 3)
            break;
    }
    return option;
}

int main(int argc, char *argv[])
{

    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    int option = menu();
    in = fopen("rr-schedule.txt", "r");
    if (option == 3)
    {
        in = fopen("rr-schedule_pri.txt", "r");
    }

    while (fgets(task, SIZE, in) != NULL)
    {
        temp = strdup(task);
        name = strsep(&temp, ",");
        priority = atoi(strsep(&temp, ","));
        burst = atoi(strsep(&temp, ","));

        if (option == 1)
        {
            add_FCFS(name, priority, burst);
        }
        else if (option == 2)
        {
            add_RR_P(name, priority, burst);
        }
        else
        {
            add_RR_P(name, priority, burst);
        }

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    if (option == 1)
    {
        schedule_FCFS();
    }
    else if (option == 2)
    {
        schedule_RR();
    }
    else
    {
        schedule_RR_P();
    }

    return 0;
}
