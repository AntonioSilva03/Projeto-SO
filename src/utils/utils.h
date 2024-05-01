#ifndef utils_h
#define utils_h
#include <stdlib.h>

#define MAX_ARGS_SIZE 300
#define PIPE_PATH "../so-orchestrator/tmp/pipe"
#define SETTINGS_PATH "../so-orchestrator/tmp/settings.txt"

int new_fifo();
char** parseProgram(char *program);

#endif