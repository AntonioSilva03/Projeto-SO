#include "task.h"
#include <string.h>
#include "program.h"

struct task{
    int id;
    int p;
    Programa programa;
    Programa* pipeline;
};

Tarefa novaTarefa(int id, char* name, char** args, Programa* pipeline){
    if(pipeline == NULL){
        Tarefa t = malloc(sizeof(struct task));
        t->p = 0;
        t->id = id;
        Programa p = novoPrograma(name, args);
        t->programa = p;
        return t;
    }
    else{
        Tarefa t = malloc(sizeof(struct task));
        t->p = 1;
        t->id = id;
        t->pipeline = pipeline;
        return t;
    }
}

int getID(Tarefa t){
    return t->id;
}

Programa getPrograma(Tarefa t){
    return t->programa;
}

int getPipelineStatus(Tarefa t){
    return t->p;
}

Programa* getPipeline(Tarefa t){
    return t->pipeline;
}