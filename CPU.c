#include <stdio.h>
#include "task.h"

// run this task for the specified time slice
// run this task for the specified time slice
void run(Task *task, int slice)
{
    printf("Running task = [%s] [%d] [%d] for %d units.\n", task->name, task->priority, task->burst, slice);

    task->burst -= slice; // Subtrair a fatia de tempo da duração da tarefa

    if (task->burst < 0) {
        task->burst = 0; // Certificar-se de que a duração da tarefa não seja negativa
    }
}
