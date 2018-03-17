#include "main.h"
#include "symbolTable.h"
#include "Parsing.h"

int isInstuction(char* string);

int isDataType(char* string);

int isRegister(char* string);

int isExtern(char* string);

int isWhitespace(char* line);

int isEntry(char* string);

StatusCode insertData(char* type, char *data);

StatusCode insertExtern(char* symbols);

StatusCode insertInstruction(char* instruction, char* operands, int isSecondIteration);
