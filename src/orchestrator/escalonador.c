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
    if(checkSpace()){
        addExecking(t);
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
        }
    }
    else addQueue(t);
}

char *getStatus(){
    char* status = malloc(BUFSIZ);
    strcpy(status, "Boas mano ta tudo este e um status bue nice\n");
    return status;
}