#include <stdio.h>
#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice) {
    if (slice > 30) {
        printf("Running task = [%s] [%d] [%d] for %d units.\n", task->name, task->priority, task->burst, 30);
        task->burst -= 30;
    }
    else {
        printf("Running task = [%s] [%d] [%d] for %d units.\n", task->name, task->priority, task->burst, slice);
        task->burst -= slice;
    }
}
