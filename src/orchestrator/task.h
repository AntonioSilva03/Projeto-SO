#include <stdlib.h>
#include <stdio.h>
#ifndef TASK_H
#define TASK_H

#include "program.h"

typedef struct task *Tarefa;

Tarefa novaTarefa(int id, int time, char* name, char** args, Programa* pipeline);
int getID(Tarefa t);
Programa getPrograma(Tarefa t);
int getPipelineStatus(Tarefa t);
Programa* getPipeline(Tarefa t);
int getTime(Tarefa t);

#endif