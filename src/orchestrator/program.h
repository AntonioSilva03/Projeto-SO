#include <stdlib.h>
#include <stdio.h>
#ifndef PROGRAM_H
#define PROGRAM_H

typedef struct program *Programa;

Programa novoPrograma(char* name, char** args);

#endif