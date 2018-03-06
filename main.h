#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 80 /*Max line length*/
#define NUM_OF_INSTRUCTS 16
#define NUM_OF_DATA_TYPES 3
#define NUM_OF_REGISTERS 8
#define MAX_SYMBOL_LEN 30
#define MAX_PARAMS 3
#define MAX_DIGITS 12
#define START_ADDRESS 100
#define MAX_FILE_LENGTH 256
#define EXTERN "extern"
#define ENTRY "entry"

typedef enum type { external,relocatable } Types;
typedef struct symbol
{
    char* name;
    int value;
    char* mark;
    Types type;
    struct symbol* next;
} Symbol;

extern char* instructions[NUM_OF_INSTRUCTS];
extern char* dataTypes[NUM_OF_DATA_TYPES];
extern char* registers[NUM_OF_REGISTERS];
extern int dataArray[MAX_FILE_LENGTH];
extern int instructionsArray[MAX_FILE_LENGTH];
extern int DC,IC;
extern int errorsFound;
void runProg(char* fileName);

#endif
