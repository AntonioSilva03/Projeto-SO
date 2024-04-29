#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

int new_fifo(){
    int fifo = mkfifo(PIPE_PATH, 0666);
    if(fifo != 0){
        return 1;
    }
    return 0;
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