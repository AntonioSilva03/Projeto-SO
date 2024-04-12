#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../utils/utils.h"
#include "../utils/messages.h"

int main(){
    int fd_pipe;

    char request[BUFSIZ];
    char response[BUFSIZ];

    if(new_fifo()){
        write(STDERR_FILENO, PIPE_ERROR, sizeof(PIPE_ERROR));
        _exit(1);
    }

    while(1){
        fd_pipe = open(PIPE_PATH, O_RDONLY);
        read(fd_pipe, request, sizeof(request));
        close(fd_pipe);

        int pid;
        pid = fork();

        if(pid < 0){
            perror("Error fork");
            _exit(1);
        }
        else if(pid == 0){
            // Child process
        }
        else if(pid > 0){
            // Parent process
        }
    }
    return 0;
}