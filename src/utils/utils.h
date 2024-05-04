#ifndef utils_h
#define utils_h
#include <stdlib.h>

#define MAX_ARGS_SIZE 300
#define PIPE_READ_PATH "../so-orchestrator/tmp/read"
#define PIPE_WRITE_PATH "../so-orchestrator/tmp/write"
#define SETTINGS_PATH "../so-orchestrator/tmp/settings.txt"
#define PROCESS_PATH "../so-orchestrator/tmp/num_process.txt"
#define QUEUE_PATH "../so-orchestrator/tmp/queue.txt"
#define FINISHED_PATH "../so-orchestrator/tmp/finished.txt"
#define EXEC_PATH "../so-orchestrator/tmp/exec.txt"
#define PROGRAM_PATH "../so-orchestrator/programs/"

#define LIM_ID 100000

int new_fifo();
char **parsePipeline(char *pipeline);
char** parseProgram(char *program);
void writeSettings(char* args[]);
char *buildPath(char* mainPath, int pid);
char *buildPathPipe(char* mainPath, char pid[]);

#endif