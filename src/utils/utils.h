#ifndef utils_h
#define utils_h
#include <stdlib.h>

#define MAX_ARGS_SIZE 300
#define PIPE_PATH "../so-orchestrator/tmp/pipe"
#define SETTINGS_PATH "../so-orchestrator/tmp/settings.txt"
#define PROCESS_PATH "../so-orchestrator/tmp/num_process.txt"

int new_fifo();
char** parseProgram(char *program);
void writeSettings(char* args[]);
void createNumProcess();

#endif