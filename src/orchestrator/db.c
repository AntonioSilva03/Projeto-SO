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

void createNumProcess(){
    int fd = open(PROCESS_PATH, O_WRONLY | O_CREAT, 0666);
    char string[4] = "0";
    write(fd, string, strlen(string));
    close(fd);
}

void incProcesses(int opt){
    int fd_size;
    char size[4];

    fd_size = open(PROCESS_PATH, O_RDONLY, 0666);
    read(fd_size, size, sizeof(size));
    close(fd_size);
    int sizeT = atoi(size);

    fd_size = open(PROCESS_PATH, O_WRONLY | O_TRUNC, 0666);
    char newSize[4];
    if(opt == 1) sprintf(newSize, "%d\n", sizeT + 1);
    else sprintf(newSize, "%d\n", sizeT - 1);
    write(fd_size, newSize, strlen(newSize));
    close(fd_size);
}

void createQueueFile(){
    int fd = open(QUEUE_PATH, O_WRONLY | O_CREAT, 0666);
    close(fd);
}

void createFinishedFile(){
    int fd = open(FINISHED_PATH, O_WRONLY | O_CREAT, 0666);
    close(fd);
}

void createExecFile(){
    int fd = open(EXEC_PATH, O_WRONLY | O_CREAT, 0666);
    close(fd);
}

void createTmpFiles(){
    createNumProcess();
    createQueueFile();
    createFinishedFile();
    createExecFile();
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
    close(fd_opt);
    strtok(opt, "\n");
    int maxSize = atoi(strtok(NULL, "\n"));

    if(maxSize - sizeT > 0) return 1;
    return 0;
}

char* getOutputFile(){
    char file[BUFSIZ];
    int fd = open(SETTINGS_PATH, O_RDONLY, 0666);
    read(fd, file, sizeof(file));
    close(fd);
    return strtok(file, "\n");
}

void addFinished(Tarefa t, unsigned long time){
    int fd = open(FINISHED_PATH, O_WRONLY | O_APPEND, 0666);
    char data[96];
    sprintf(data, "%d ", getID(t));

    Programa p = getPrograma(t);
    strcat(data, getName(p));
    strcat(data, " ");

    char timeStr[28];
    sprintf(timeStr, "%ld ms\n", time);
    strcat(data, timeStr);
    write(fd, data, strlen(data));
    close(fd);
}

char* getFinished(){
    char *data = malloc(BUFSIZ);
    strcpy(data, "Finished:\n");
    char* buffer = malloc(BUFSIZ);
    int fd = open(FINISHED_PATH, O_RDONLY);
    read(fd, buffer, BUFSIZ);
    close(fd);
    strcat(data, buffer);
    strcat(data, "\n");
    free(buffer);

    return data;
}

void addQueue(Tarefa t){
    int fd = open(QUEUE_PATH, O_WRONLY | O_APPEND, 0666);
    char data[BUFSIZ];
    sprintf(data, "%d ", getID(t));
    Programa p = getPrograma(t);
    char* name = getName(p);
    strcat(data, name);
    char** args = getArgs(p);
    int i = 0;
    while(args[i]){
        strcat(data, " ");
        strcat(data, strdup(args[i]));
        i++;
    }
    strcat(data, "\n");
    write(fd, data, strlen(data));
    close(fd);
}

Tarefa removeQueue(){
    int fd = open(QUEUE_PATH, O_RDWR, 0666);
    char data[BUFSIZ];
    ssize_t bytes_lidos = read(fd, data, sizeof(data));

    if(bytes_lidos > 0){
        char* newDataa = strchr(data, '\n');
        size_t tamanho_restante = bytes_lidos - (newDataa - data) - 1;

        char primeira_linha[newDataa - data + 1];
        strncpy(primeira_linha, data, newDataa - data);
        primeira_linha[newDataa - data] = '\0';

        lseek(fd, 0, SEEK_SET);
        ssize_t bytes_escritos = write(fd, newDataa + 1, tamanho_restante);
        ftruncate(fd, bytes_escritos);
        close(fd);

        char* primeira_linhaa = strdup(primeira_linha);

        char** program = parseProgram(primeira_linhaa);
        Tarefa t = novaTarefa(atoi(program[0]), program[1], &program[2]);

        free(primeira_linhaa);

        return t;
    }
    return NULL;
}

char* getQueue(){
    char *data = malloc(BUFSIZ);
    strcpy(data, "Scheduled:\n");
    char* buffer = malloc(BUFSIZ);
    int fd = open(QUEUE_PATH, O_RDONLY);
    read(fd, buffer, BUFSIZ);
    close(fd);
    strcat(data, buffer);
    strcat(data, "\n");
    free(buffer);

    return data;
}

void addExecking(Tarefa t){
    int fd = open(EXEC_PATH, O_WRONLY | O_APPEND, 0666);
    char data[128];
    sprintf(data, "%d ", getID(t));
    char* name = getName(getPrograma(t));
    strcat(data, name);
    strcat(data, "\n");
    write(fd, data, strlen(data));
    close(fd);
}

void removeExecking(Tarefa t){
    int id = getID(t);

    int fd = open(EXEC_PATH, O_RDONLY);
    char data[BUFSIZ];
    read(fd, data, sizeof(data));
    close(fd);

    char newData[BUFSIZ];
    strcpy(newData, "");

    char* line = strtok(data, "\n");
    while(line){
        char* lineDup = strdup(line);
        char idText[40];
        sscanf(lineDup, "%[^;]%*c", idText);
        int idLine = atoi(idText);

        if(idLine != id){
            strcat(newData, line);
            strcat(newData, "\n");
        }
        free(lineDup);
        line = strtok(NULL, "\n");
    }
    fd = open(EXEC_PATH, O_WRONLY | O_TRUNC);
    if(strlen(newData) > 16) write(fd, newData, strlen(newData));
    close(fd);
}

char* getExecking(){
    char *data = malloc(BUFSIZ);
    strcpy(data, "Executing:\n");
    char* buffer = malloc(BUFSIZ);
    int fd = open(EXEC_PATH, O_RDONLY);
    read(fd, buffer, BUFSIZ);
    close(fd);
    strcat(data, buffer);
    strcat(data, "\n");
    free(buffer);

    return data;
}