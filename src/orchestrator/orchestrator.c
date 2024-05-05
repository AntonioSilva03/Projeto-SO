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
    initDB();

    while(1){
        //printf("Leitura\n");
        fd_pipe = open(PIPE_READ_PATH, O_RDONLY);
        read(fd_pipe, request, sizeof(request));
        //printf("Ja volto\n");
        close(fd_pipe);

        char* buffer = strdup(request);
        char* savePtr;

        char* command = strtok_r(buffer, LIMITADOR_MENSAGENS, &savePtr);
        while(command != NULL){
            handle_command(strdup(command));
            command = strtok_r(NULL, LIMITADOR_MENSAGENS, &savePtr);
        }
        free(buffer);

        memset(request, '\0', sizeof(request));
    }
    return 0;
}