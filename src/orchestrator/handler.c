#include "handler.h"
#include <string.h>
#include "../utils/utils.h"
#include "task.h"
#include "escalonador.h"
#include "db.h"
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

Tarefa* queue;
Tarefa* exec;
int maxSize;

void initDB(){
    maxSize = getSpace();
    queue = calloc(15, sizeof(Tarefa));
    exec = calloc(maxSize, sizeof(Tarefa));
    srand(time(NULL));
}

void flushQueue(){
    if(queue[0] == NULL) return;
    for(int i = 0; i < maxSize; i++){
        if(exec[i] == NULL){
            exec[i] = queue[0];
            addExecking(exec, maxSize, exec[i]);
            int pid = fork();
            if(pid < 0){
                perror("Error forking exec: ");
            }
            else if(pid == 0){
                addTask(exec[i]);
                _exit(0);
            }
            else if(pid > 0){
                int t = 0;
                while(queue[t + 1]){
                    queue[t] = queue[t + 1];
                    t++;
                }
                queue[t] = NULL;
            }
        }
    }
}

void handle_command(char* request){
    int fd_pipe;

    char* command = strtok(request, "\n");
    if(strcmp(command, "close") == 0){
        Tarefa t = novaTarefa(0, 0, NULL, NULL, NULL);

        if(checkSpace(exec, maxSize)){
            addExecking(exec, maxSize, t);
            int pid = fork();
            if(pid < 0){
                perror("Error forking exec: ");
            }
            else if(pid == 0){
                addTask(t);
                _exit(0);
            }
        }
        else addQueue(queue, t);
    }
    else if(strcmp(command, "execute") == 0){
        int time = atoi(strtok(NULL, "\n"));
        char** prog = parseProgram(strtok(NULL, "\n"));
        Tarefa t = novaTarefa(rand() % LIM_ID, time, prog[0], &prog[0], NULL);

        if(checkSpace(exec, maxSize)){
            addExecking(exec, maxSize, t);
            int pid = fork();
            if(pid < 0){
                perror("Error forking exec: ");
            }
            else if(pid == 0){
                addTask(t);
                _exit(0);
            }
        }
        else addQueue(queue, t);

        char response[BUFSIZ];
        snprintf(response, sizeof(response), "Tarefa com ID: %d recebida com sucesso\n", getID(t));
        fd_pipe = open(PIPE_WRITE_PATH, O_WRONLY);
        write(fd_pipe, response, strlen(response));
        close(fd_pipe);
        free(prog);
    }
    else if(strcmp(command, "executep") == 0){
        int time = atoi(strtok(NULL, "\n"));
        Programa* pipeline = novaPipeline(strtok(NULL, "\0"));
        Tarefa t = novaTarefa(rand() % LIM_ID, time, NULL, NULL, pipeline);
        if(checkSpace(exec, maxSize)){
            addExecking(exec, maxSize, t);
            int pid = fork();
            if(pid < 0){
                perror("Error forking exec: ");
            }
            else if(pid == 0){
                addTask(t);
                _exit(0);
            }
        }
        else addQueue(queue, t);

        char response[BUFSIZ];
        snprintf(response, sizeof(response), "Pipeline com ID: %d recebida com sucesso\n", getID(t));
        fd_pipe = open(PIPE_WRITE_PATH, O_WRONLY);
        write(fd_pipe, response, strlen(response));
        close(fd_pipe);
    }
    else if(strcmp(command, "status") == 0){
        int pid = fork();

        if(pid < 0){
            perror("Error forking status: ");
        }
        else if(pid == 0){
            char* status = getStatus(queue, exec, maxSize);
            fd_pipe = open(PIPE_WRITE_PATH, O_WRONLY);
            write(fd_pipe, status, strlen(status));
            close(fd_pipe);
            free(status);
            _exit(0);
        }
        // O processo pai continua
    }
    else if(strcmp(command, "end") == 0){
        int pid = atoi(strtok(NULL, "\n"));
        removeExecking(exec, maxSize, pid);
        flushQueue();
    }
}