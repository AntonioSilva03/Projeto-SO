#include "handler.h"
#include <string.h>
#include "../utils/utils.h"
#include "task.h"
#include "escalonador.h"
#include <unistd.h>
#include <fcntl.h>

void handle_command(char* request){
    int fd_pipe;

    char* command = strtok(request, "\n");
    if(strcmp(command, "execute") == 0){
        int time = atoi(strtok(NULL, "\n"));
        char** prog = parseProgram(strtok(NULL, "\n"));

        int pid = fork();
        if(pid < 0){
            perror("Error forking exec: ");
        }
        else if(pid == 0){
            Tarefa t = novaTarefa(getpid(), prog[0], &prog[1]);
            addTask(t);
            _exit(0);
        }
        else if(pid > 0){
            char response[BUFSIZ];
            snprintf(response, sizeof(response), "Pedido com ID: %d recebida com sucesso\n", pid);
            fd_pipe = open(PIPE_PATH, O_WRONLY);
            write(fd_pipe, response, strlen(response));
            close(fd_pipe);
            free(prog);
        }
    }
    else if(strcmp(command, "status") == 0){
        int pid = fork();

        if(pid < 0){
            perror("Error forking status: ");
        }
        else if(pid == 0){
            char* status = getStatus();
            fd_pipe = open(PIPE_PATH, O_WRONLY);
            write(fd_pipe, status, strlen(status));
            close(fd_pipe);
            free(status);
            _exit(0);
        }
        // O processo pai continua
    }
}