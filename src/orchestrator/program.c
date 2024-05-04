#include "program.h"
#include <string.h>
#include "../utils/utils.h"

struct program{
    char* name;
    char **argss;
};

Programa* novaPipeline(char* pipe){
    Programa* pipeline = malloc(sizeof(struct program) * 10);
    char* savePtr;
    int i = 0;
    char* program = strtok_r(pipe, "\n", &savePtr);
    while(program != NULL){
        char** singleProgram = parseProgram(program);
        Programa p = novoPrograma(singleProgram[0], &singleProgram[0]);
        pipeline[i] = p;
        i++;
        program = strtok_r(NULL, "\n", &savePtr);
    }
    return pipeline;
}

Programa novoPrograma(char* name, char** args){
    Programa p = malloc(sizeof(struct program));
    char path[256] = PROGRAM_PATH;
    p->name = strdup(name);
    p->argss = malloc(sizeof(args));
    int i = 0;
    while(args[i]){
        p->argss[i] = strdup(args[i]);
        i++;
    }
    return p;
}

char* getName(Programa p){
    return p->name;
}

char** getArgs(Programa p){
    return p->argss;
}