#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 80
#define NUM_OF_INSTRUCTS 16
#define NUM_OF_DATA_TYPES 3
#define NUM_OF_REGISTERS 8
#define MAX_SYMBOL_LEN 30
#define MAX_DIGITS 12
#define EXTERN "extern"
#define ENTRY "entry"

extern char* instructions[NUM_OF_INSTRUCTS];
extern char* dataTypes[NUM_OF_DATA_TYPES];
extern char* registers[NUM_OF_REGISTERS];
extern char* dataArray[256];
extern char* instructionsArray[256];
extern int DC,IC;
