#include <stdlib.h>
#include <stdio.h>
#ifndef TASK_H
#define TASK_H

#include "program.h"

typedef struct task *Tarefa;

Tarefa novaTarefa(int id, char* name, char** args, Programa* pipeline);
int getID(Tarefa t);
Programa getPrograma(Tarefa t);
int getPipelineStatus(Tarefa t);
Programa* getPipeline(Tarefa t);

#endif