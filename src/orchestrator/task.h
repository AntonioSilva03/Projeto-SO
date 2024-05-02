#include <stdlib.h>
#include <stdio.h>
#ifndef TASK_H
#define TASK_H

#include "program.h"

typedef struct task *Tarefa;

Tarefa novaTarefa(int id, char* name, char** args);
int getID(Tarefa t);
Programa getPrograma(Tarefa t);

#endif