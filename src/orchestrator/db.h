#include <stdlib.h>
#ifndef DB_H
#define DB_H

void writeSettings(char* args[]);
void createNumProcess();
void createQueueFile();
void createFinishedFile();
void createTmpFiles();
int checkSpace();
char* getOutputFile();

#endif