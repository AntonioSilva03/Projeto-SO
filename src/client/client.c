#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../utils/messages.h"
#include "../utils/utils.h"

int main(int argc, char *argv[]){
    int fd_pipe;
    if(argc < 2){
        write(STDERR_FILENO, BOOT_ERROR, sizeof(BOOT_ERROR));
        _exit(1);
    }

    if(new_fifo()){
        write(STDERR_FILENO, PIPE_ERROR, sizeof(PIPE_ERROR));
        _exit(1);
    }

    char* command = argv[1];
    if(strcmp(command, "execute") == 0){
        if(argc < 4){
            write(STDERR_FILENO, EXECUTE_USAGE, sizeof(EXECUTE_USAGE));
            _exit(1);
        }
        int time = atoi(argv[2]);
        char *option = argv[3];
        if(strcmp(option, "-u") == 0){

        }
        else if(strcmp(option, "-p") == 0){

        }
        else{
            write(STDERR_FILENO, EXECUTE_USAGE, sizeof(EXECUTE_USAGE));
            _exit(1);
        }
    }
    else if(strcmp(command, "status") == 0){
        
    }
    else{

    }
    return 0;
}