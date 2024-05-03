#include <stdlib.h>
#include "escalonador.h"
#include "task.h"
#include "db.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../utils/utils.h"
#include "program.h"
#include <sys/time.h>

Tarefa* emExec;
Tarefa* queue;
int numProcess = 0;

void addTask(Tarefa t){
    int fd_output;
    struct timeval start;
    struct timeval end;
    int pid = fork();
    if(pid < 0){
        perror("Error fork start exec: ");
    }
    else if(pid == 0){
        char* fileName = buildPath(getOutputFile(), getID(t));
        fd_output = open(fileName, O_WRONLY | O_CREAT, 0666);

        Programa p = getPrograma(t);
        dup2(fd_output, STDOUT_FILENO);
        dup2(fd_output, STDERR_FILENO);
        execvp(getName(p), getArgs(p));
    }
    else if(pid > 0){
        gettimeofday(&start, NULL);
        waitpid(pid, NULL, 0);
        gettimeofday(&end, NULL);
        close(fd_output);
        addFinished(t, (end.tv_sec - start.tv_sec) * 1000000 + abs(end.tv_usec));
        int fd = open(PIPE_READ_PATH, O_WRONLY);
        char buffer[40] = "end\n";
        char tmp[24];
        snprintf(tmp, sizeof(tmp), "%d\n", getID(t));
        strcat(buffer, tmp);
        write(fd, buffer, strlen(buffer));
        close(fd);
    }
}

char *getStatus(Tarefa* queue, Tarefa* exec, int maxSize){
    char* status = malloc(BUFSIZ);
    char execking[BUFSIZ];
    strcpy(execking, "Executing:\n");
    for(int i = 0; i < maxSize; i++){
        if(exec[i] != NULL){
            char line[BUFSIZ] = "";
            sprintf(line, "%d ", getID(exec[i]));
            strcat(line, getName(getPrograma(exec[i])));
            strcat(line, "\n");
            strcat(execking, line);
        }
    }
    strcpy(status, execking);

    char queueing[BUFSIZ];
    strcpy(queueing, "\nScheduled:\n");
    int i = 0;
    while(queue[i]){
        char line[BUFSIZ];
        sprintf(line, "%d ", getID(queue[i]));
        strcat(line, getName(getPrograma(queue[i])));
        strcat(line, "\n");
        strcat(queueing, line);
        i++;
    }
    strcat(status, queueing);

    char buffer2[BUFSIZ];
    strcpy(buffer2, getFinished());
    strcat(status, buffer2);

    return status;
}