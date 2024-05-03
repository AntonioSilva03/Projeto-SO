#include <stdlib.h>
#ifndef DB_H
#define DB_H

#include "task.h"

void writeSettings(char* args[]);
void createNumProcess();
void incProcesses(int opt);
void createQueueFile();
void createFinishedFile();
void createTmpFiles();
int checkSpace();
char* getOutputFile();
void addFinished(Tarefa t, unsigned long time);
void addQueue(Tarefa t);
Tarefa removeQueue();
void addExecking(Tarefa t);
void removeExecking(Tarefa t);

#endif