#include "task.h"

struct task{
    int id;
    char* name;
    char** args; 
};

Tarefa novaTarefa(int id, char* name, char* args[]){
    Tarefa t = malloc(sizeof(struct task));
    t->id = id;
    t->name = name;
    t->args = args;
    return t;
}