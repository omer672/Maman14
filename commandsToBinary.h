#include "main.h"
#include "symbolTable.h"
#include "helper.h"
#include <ctype.h>


/*The function checks if the symbol inserted is entry and marks it*/
StatusCode markEntry(char* symbol);

/*The function gets string operands and checks its type on first iterate - imm, direct, struct, register*/
StatusCode checkType(char *reqOp, opType *result);

/*The function gets string operands and checks its type on second iterate - imm, direct, struct, register*/
StatusCode checkTypeSecIter(SymbolType sType, opType *result);

/*The function calculated how many rows the operand inserted takes*/
StatusCode opSumRow(opType operand, int *result);

/*The function takes 2 operands and returns number of rows the command will take*/
StatusCode instSumRow(opType firstTP, opType secondTP, int numberOfOperands, int *result);

/*The function search the command, return his place(equals to his binary 4 bits)*/
int searchOp(char* opCode);
