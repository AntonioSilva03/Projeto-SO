#include <stdlib.h>
#include <stdio.h>
#ifndef TASK_H
#define TASK_H

typedef struct task *Tarefa;

Tarefa novaTarefa(int id, char* name, char** args);

#endif