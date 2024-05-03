#include <stdlib.h>
#ifndef DB_H
#define DB_H

#include "task.h"

void writeSettings(char* args[]);
void createTmpFiles();
int checkSpace(Tarefa* queue, int maxSize);
int getSpace();
char* getOutputFile();
void addFinished(Tarefa t, unsigned long time);
char* getFinished();
void addQueue(Tarefa* queue, Tarefa t);
void addExecking(Tarefa* exec, int maxSize, Tarefa t);
void removeExecking(Tarefa* exec, int maxSize, int pid);

#endif