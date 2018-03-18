#ifndef FIRST_ITERATION_H
#define FIRST_ITERATION_H

#include "main.h"
#include "helper.h"
#include "symbolTable.h"
#include "secondIteration.h"
#include "errorPrinter.h"
/*The function handles all global variables used by program*/
void iterate(FILE* file, char *fileName);

/*The function first iterate on file, gets File type and file name and runs through the file*/
void clearGlobals();

#endif
