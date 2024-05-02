#include <stdlib.h>
#ifndef DB_H
#define DB_H

#include "task.h"

void writeSettings(char* args[]);
void createNumProcess();
void createQueueFile();
void createFinishedFile();
void createTmpFiles();
int checkSpace();
char* getOutputFile();
void addFinished(Tarefa t, unsigned long time);
void addQueue(Tarefa t);
void addExecking(Tarefa t);

#endif