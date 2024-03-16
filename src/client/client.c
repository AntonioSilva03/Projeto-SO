#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../defines/defines.h"

int main(int argc, char *argv[]){
    int fd_pipe;
    if(argc < 2){
        write(STDERR_FILENO, BOOT_ERROR, sizeof(BOOT_ERROR));
    }

    mkfifo("/tmp/pipe", 0666);

    char* command = argv[1];
    if(strcmp(command, "execute") == 0){

    }
    else if(strcmp(command, "status") == 0){

    }
    else{

    }
    return 0;
}