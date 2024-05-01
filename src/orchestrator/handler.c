#include "handler.h"
#include <string.h>
#include "../utils/utils.h"
#include "task.h"
#include "escalonador.h"

void handle_command(int id, char* request){
    char* command = strtok(request, "\n");
    if(strcmp(command, "execute") == 0){
        int time = atoi(strtok(NULL, "\n"));
        char** prog = parseProgram(strtok(NULL, "\n"));
        Tarefa t = novaTarefa(id, prog[0], &prog[1]);
        free(prog);


    }
    else if(strcmp(command, "status") == 0){
        
    }
}