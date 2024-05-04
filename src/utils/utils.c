#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

int new_fifo(){
    unlink(PIPE_READ_PATH);
    unlink(PIPE_WRITE_PATH);
    int fifo1 = mkfifo(PIPE_READ_PATH, 0666);
    int fifo2 = mkfifo(PIPE_WRITE_PATH, 0666);
    if(fifo1 != 0 && fifo2 != 0){
        return 1;
    }
    return 0;
}

char **parsePipeline(char *pipeline){
    char **splittedPipeline = malloc(MAX_ARGS_SIZE);

    int i = 0;
    char* program = strtok(pipeline, "|");
    while(program != NULL){
        splittedPipeline[i] = strdup(program);
        program = strtok(NULL, "|");
        i++;
    }
    return splittedPipeline;
}

char **parseProgram(char *program){
    char **splittedArgs = malloc(MAX_ARGS_SIZE);

    int i = 0;
    char *token = strtok(program, " ");
    while(token != NULL){
        splittedArgs[i] = strdup(token);
        token = strtok(NULL, " ");
        i++;
    }
    return splittedArgs;
}

char *buildPath(char* mainPath, int pid){
    char pidStr[40];
    snprintf(pidStr, sizeof(pidStr), "%d.txt", pid);

    char* fileName = malloc(128);
    strcpy(fileName, mainPath);
    strcat(fileName, pidStr);

    return fileName;
}

char *buildPathPipe(char* mainPath, char pid[]){
    char* fileName = malloc(128);
    strcpy(fileName, mainPath);
    strcat(fileName, pid);
    strcat(fileName, ".txt");

    return fileName;
}