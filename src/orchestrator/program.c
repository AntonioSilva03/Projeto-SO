#include "program.h"
#include <string.h>
#include "../utils/utils.h"

struct program{
    char* name;
    char **argss;
};

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