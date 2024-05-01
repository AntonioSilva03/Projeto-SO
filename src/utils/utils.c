#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

int new_fifo(){
    unlink(PIPE_PATH);
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

void writeSettings(char* args[]){
    int fd = open(SETTINGS_PATH, O_WRONLY | O_CREAT, 0666);
    char string[BUFSIZ] = "";
    int i = 1;
    while(args[i]){
        strcat(string, args[i]);
        strcat(string, "\n");
        i++;
    }
    write(fd, string, strlen(string));
}