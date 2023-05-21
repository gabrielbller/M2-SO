#ifndef SCHEDULE_RR_H
#define SCHEDULE_RR_H

#include "list.h"
#include "task.h"

// funcao para adicionar uma tarefa � lista de tarefas
void add_RR(char *name, int priority, int burst);

// funcao para executar o escalonamento das tarefas
void schedule();

#endif / SCHEDULE_RR_H * /
