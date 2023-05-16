#ifndef SCHEDULE_RR_H
#define SCHEDULE_RR_H

#include "list.h"
#include "task.h"

// funcao para adicionar uma tarefa � lista de tarefas
void add_rr(char *name, int priority, int burst);

// funcao para executar o escalonamento das tarefas
void schedule_rr();

#endif / SCHEDULE_RR_H * /
