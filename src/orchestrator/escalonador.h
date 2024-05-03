#include <stdlib.h>
#include "task.h"
#ifndef ESCALONADOR_H
#define ESCALONADOR_H

void addTask(Tarefa t);
char *getStatus(Tarefa* queue, Tarefa* exec, int maxSize);

#endif