#include "main.h"
#include "symbolTable.h"
#include "helper.h"
#include <ctype.h>


StatusCode markEntry(char* symbol);

StatusCode checkType(char *reqOp, opType *result);

StatusCode checkTypeSecIter(SymbolType sType, opType *result);

StatusCode opSumRow(opType operand, int *result);

StatusCode opSumRow(opType operand, int *result);

StatusCode instSumRow(opType firstTP, opType secondTP, int numberOfOperands, int *result);

int searchOp(char* opCode);
