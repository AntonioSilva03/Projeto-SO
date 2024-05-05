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

void executePipeline(Tarefa t){
    char* fileName = buildPath(getOutputFile(), getID(t));
    int fd_output = open(fileName, O_WRONLY | O_CREAT, 0666);
    int fd_anterior = -1, fd[2];
    struct timeval start;
    struct timeval end;
    int i = 0;
    Programa* pipeline = getPipeline(t);
    gettimeofday(&start, NULL);
    while(pipeline[i]){
        pipe(fd);
        int pid = fork();
        if(pid < 0){
            perror("Error fork start exec: ");
        }
        else if(pid == 0){
            close(fd[0]);

            if(fd_anterior != -1){
                dup2(fd_anterior, STDIN_FILENO);
            }

            if(pipeline[i + 1]) dup2(fd[1], STDOUT_FILENO);
            else dup2(fd_output, STDOUT_FILENO);

            execvp(getName(pipeline[i]), getArgs(pipeline[i]));
        }
        else if(pid > 0){
            close(fd[1]);

            waitpid(pid, NULL, 0);
            fd_anterior = fd[0];
            i++;
        }
    }
    gettimeofday(&end, NULL);
    addFinished(t, ((end.tv_sec - start.tv_sec) * 1000) + (abs(end.tv_usec) / 1000));
    int fd2 = open(PIPE_READ_PATH, O_WRONLY);
    char buffer[40] = "end\n";
    char tmp[24];
    snprintf(tmp, sizeof(tmp), "%d\n", getID(t));
    strcat(buffer, tmp);
    strcat(buffer, LIMITADOR_MENSAGENS);
    write(fd2, buffer, strlen(buffer));
    close(fd2);
}

void addTask(Tarefa t){
    if(getPipelineStatus(t)){
        executePipeline(t);
        return;
    }
    int fd_output;
    struct timeval start;
    struct timeval end;
    int pid = fork();
    if(pid < 0){
        perror("Error fork start exec: ");
    }
    else if(pid == 0){
        if(getID(t) == 0){
            _exit(0);
        }
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
        if(getID(t) == 0) addFinished(NULL, 0);
        else addFinished(t, ((end.tv_sec - start.tv_sec) * 1000) + (abs(end.tv_usec) / 1000));
        int fd = open(PIPE_READ_PATH, O_WRONLY);
        char buffer[40] = "end\n";
        char tmp[24];
        snprintf(tmp, sizeof(tmp), "%d\n", getID(t));
        strcat(buffer, tmp);
        strcat(buffer, LIMITADOR_MENSAGENS);
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
            if(!getPipelineStatus(exec[i])){
                char line[BUFSIZ] = "";
                sprintf(line, "%d ", getID(exec[i]));
                strcat(line, getName(getPrograma(exec[i])));
                strcat(line, "\n");
                strcat(execking, line);
            }
            else{
                char line[BUFSIZ] = "";
                sprintf(line, "%d ", getID(exec[i]));
                Programa* pipeline = getPipeline(exec[i]);
                int t = 0;
                while(pipeline[t]){
                    strcat(line, getName(pipeline[t]));
                    strcat(line, " | ");
                    t++;
                }
                strcat(line, "\n");
                strcat(execking, line);
            }
        }
    }
    strcpy(status, execking);

    char queueing[BUFSIZ];
    strcpy(queueing, "\nScheduled:\n");
    int i = 0;
    while(queue[i]){
        if(getID(queue[i]) == 0){
            i++;
            continue;
        }
        if(!getPipelineStatus(queue[i])){
            char line[BUFSIZ];
            sprintf(line, "%d ", getID(queue[i]));
            strcat(line, getName(getPrograma(queue[i])));
            strcat(line, "\n");
            strcat(queueing, line);
            i++;
        }
        else{
            char line[BUFSIZ];
            sprintf(line, "%d ", getID(queue[i]));
            Programa* pipeline = getPipeline(queue[i]);
            int t = 0;
            while(pipeline[t]){
                strcat(line, getName(pipeline[t]));
                strcat(line, " | ");
                t++;
            }
            strcat(line, "\n");
            strcat(queueing, line);
            i++;
        }
    }
    strcat(status, queueing);

    char buffer2[BUFSIZ];
    strcpy(buffer2, getFinished());
    strcat(status, buffer2);

    return status;
}