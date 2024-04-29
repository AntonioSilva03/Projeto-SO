#include "task.h"
#include <string.h>

struct task{
    int id;
    char* name;
    char** argss; 
};

Tarefa novaTarefa(int id, char* name, char** args){
    Tarefa t = malloc(sizeof(struct task));
    t->id = id;
    t->name = strdup(name);
    t->argss = malloc(sizeof(args));
    int i = 0;
    while(args[i]){
        t->argss[i] = strdup(args[i]);
        i++;
    }
    return t;
}