#include "main.h"
#include <string.h>

int isInstuction(char* string);

int isDataType(char* string);

int isRegister(char* string);

int isExtern(char* string);

int isEntry(char* string);

void insertData(char* type, char *data);

void insertExtern(char* symbols);

void insertInstruction(char* instruction, char* operands, int isSecondIteration);
