#include <stdlib.h>
#include <stdio.h>
#ifndef PROGRAM_H
#define PROGRAM_H

typedef struct program *Programa;

Programa* novaPipeline(char* pipe);
Programa novoPrograma(char* name, char** args);
char* getName(Programa p);
char** getArgs(Programa p);

#endif