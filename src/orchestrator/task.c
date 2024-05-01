#include "task.h"
#include <string.h>
#include "program.h"

struct task{
    int id;
    Programa programa;
};

Tarefa novaTarefa(int id, char* name, char** args){
    Tarefa t = malloc(sizeof(struct task));
    t->id = id;
    Programa p = novoPrograma(name, args);
    t->programa = p;
    return t;
}