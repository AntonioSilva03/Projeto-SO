#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "../utils/utils.h"
#include "../utils/messages.h"
#include "db.h"
#include "handler.h"

int main(int argc, char *argv[]){
    int fd_pipe;

    char request[BUFSIZ];
    char response[BUFSIZ];

    if(new_fifo()){
        write(STDERR_FILENO, PIPE_ERROR, sizeof(PIPE_ERROR));
        _exit(1);
    }

    writeSettings(argv);
    createTmpFiles();

    while(1){
        fd_pipe = open(PIPE_PATH, O_RDONLY);
        read(fd_pipe, request, sizeof(request));
        close(fd_pipe);

        handle_command(strdup(request));

        /*int pid = fork();

        if(pid < 0){
            perror("Error: ");
            _exit(1);
        }
        else if(pid == 0){
            handle_command(getpid(), strdup(request)); // Child process
            break;
        }
        else if(pid > 0){
            snprintf(response, sizeof(response), "Pedido com ID: %d recebida com sucesso\n", pid);
            fd_pipe = open(PIPE_PATH, O_WRONLY);
            write(fd_pipe, response, strlen(response));
            close(fd_pipe);
        }*/
    }
    return 0;
}