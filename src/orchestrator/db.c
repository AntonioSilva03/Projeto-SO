#include "db.h"
#include <fcntl.h>
#include <stdio.h>
#include "../utils/utils.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "task.h"

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
    close(fd);
}

void createFinishedFile(){
    int fd = open(FINISHED_PATH, O_WRONLY | O_CREAT, 0666);
    close(fd);
}

void createTmpFiles(){
    createFinishedFile();
}

int checkSpace(Tarefa* queue, int maxSize){
    for(int i = 0; i < maxSize; i++){
        if(queue[i] == NULL){
            return 1;
        }
    }
    return 0;
}

int getSpace(){
    char opt[BUFSIZ];
    int fd_opt = open(SETTINGS_PATH, O_RDONLY, 0666);
    read(fd_opt, opt, sizeof(opt));
    close(fd_opt);
    strtok(opt, "\n");
    int maxSize = atoi(strtok(NULL, "\n"));
    return maxSize;
}

char* getOutputFile(){
    char file[BUFSIZ];
    int fd = open(SETTINGS_PATH, O_RDONLY, 0666);
    read(fd, file, sizeof(file));
    close(fd);
    return strtok(file, "\n");
}

char *getPolitics(){
    char file[BUFSIZ];
    int fd = open(SETTINGS_PATH, O_RDONLY, 0666);
    read(fd, file, sizeof(file));
    close(fd);
    strtok(file, "\n");
    strtok(NULL, "\n");
    return strtok(NULL, "\n");
}

void addFinished(Tarefa t, unsigned long time){
    int fd = open(FINISHED_PATH, O_WRONLY | O_APPEND, 0666);
    char data[BUFSIZ];
    sprintf(data, "%d ", getID(t));

    if(!getPipelineStatus(t)){
        Programa p = getPrograma(t);
        strcat(data, getName(p));
        strcat(data, " ");

        char timeStr[28];
        sprintf(timeStr, "%ld ms\n", time);
        strcat(data, timeStr);
        write(fd, data, strlen(data));
        close(fd);
    }
    else{
        Programa* pipeline = getPipeline(t);
        int i = 0;
        while(pipeline[i]){
            strcat(data, getName(pipeline[i]));
            strcat(data, " | ");
            i++;
        }

        char timeStr[28];
        sprintf(timeStr, "%ld ms\n", time);
        strcat(data, timeStr);
        write(fd, data, strlen(data));
        close(fd);
    }
}

char* getFinished(){
    char *data = malloc(BUFSIZ);
    strcpy(data, "\nFinished:\n");
    char* buffer = malloc(BUFSIZ);
    int fd = open(FINISHED_PATH, O_RDONLY);
    read(fd, buffer, BUFSIZ);
    close(fd);
    strcat(data, buffer);
    strcat(data, "\n");
    free(buffer);

    return data;
}

void addQueue(Tarefa* queue, Tarefa t){
    int slot = 0;
    while(queue[slot]){
        slot++;
    }
    queue[slot] = t;
    if(strcmp(getPolitics(), "SJF") == 0){
        sortQueue(queue);
    }
}

void addExecking(Tarefa* exec, int maxSize, Tarefa t){
    for(int i = 0; i < maxSize; i++){
        if(exec[i] == NULL){
            exec[i] = t;
            break;
        }
    }
}

void removeExecking(Tarefa* exec, int maxSize, int pid){
    for(int i = 0; i < maxSize; i++){
        if(exec[i] != NULL && getID(exec[i]) == pid){
            exec[i] = NULL;
        }
    }
}

void sortQueue(Tarefa* queue){
    int size = 0;
    while(queue[size]) size++;
    for(int i = 0; i < size; i++){
        Tarefa aux = queue[i];
        int j = i - 1;
        while(j >= 0 && getTime(aux) < getTime(queue[j])){
            queue[j + 1] = queue[j];
            --j;
        }
        queue[j + 1] = aux;
    }
}