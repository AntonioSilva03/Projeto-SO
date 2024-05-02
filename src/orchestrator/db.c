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
}

void createNumProcess(){
    int fd = open(PROCESS_PATH, O_WRONLY | O_CREAT, 0666);
    char string[4] = "0";
    write(fd, string, strlen(string));
    close(fd);
}

void createQueueFile(){
    int fd = open(QUEUE_PATH, O_WRONLY | O_CREAT, 0666);
    close(fd);
}

void createFinishedFile(){
    int fd = open(FINISHED_PATH, O_WRONLY | O_CREAT, 0666);
    close(fd);
}

void createTmpFiles(){
    createNumProcess();
    createQueueFile();
    createFinishedFile();
}

int checkSpace(){
    int fd_size, fd_opt;
    char size[4], opt[BUFSIZ];

    fd_size = open(PROCESS_PATH, O_RDONLY, 0666);
    read(fd_size, size, sizeof(size));
    close(fd_size);
    int sizeT = atoi(size);

    fd_opt = open(SETTINGS_PATH, O_RDONLY, 0666);
    read(fd_opt, opt, sizeof(opt));
    strtok(opt, "\n");
    int maxSize = atoi(strtok(NULL, "\n"));

    if(maxSize - sizeT > 0) return 1;
    return 0;
}

char* getOutputFile(){
    char file[BUFSIZ];
    int fd = open(SETTINGS_PATH, O_RDONLY, 0666);
    read(fd, file, sizeof(file));
    return strtok(file, "\n");
}

void addFinished(Tarefa t, int time){
    int fd = open(FINISHED_PATH, O_WRONLY, 0666);
    char data[96];
    sprintf(data, "%d ", getID(t));

    Programa p = getPrograma(t);
    strcat(data, getName(p));
    strcat(data, " ");

    char timeStr[28];
    sprintf(timeStr, "%d", time);
    strcat(data, timeStr);
    write(fd, data, strlen(data));
}