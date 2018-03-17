#include "main.h"
#include "symbolTable.h"
#include "helper.h"
#include <ctype.h>


StatusCode markEntry(char* symbol);

StatusCode checkType(char *reqOp, opType *result);

StatusCode checkTypeSecIter(SymbolType num, opType *result);

StatusCode opSumRow(opType operand, int *result);

StatusCode opSumRow(opType operand, int *result);

StatusCode instSumRow(char *first, char *second, int* result);

int searchOp(char* opCode);
