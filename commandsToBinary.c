#include "commandsToBinary.h"

StatusCode markEntry(char* symbol)
{
    Symbol* sym;
    int i = 0;
    char name[MAX_FILE_LENGTH];
    char* token;
    char delimiter[7] = " \t\n\v\f\r"; /* all of the whitespace chars*/
    token = strtok(symbol,delimiter);

    while(token != NULL)
    {
        printf("token: %s\n",token);
        strcpy(name,token);
        i++;
        token = strtok(NULL,delimiter);
    }
    if(i!=1)
        return wrong_number_of_operands;
    else
    {
        if((sym = doesExist(name)) != NULL)
        {
            sym->isEntry = 1;
        }
        else
            return symbol_doesnt_exist;
    }
    return success;
}
/*gets string operands and checks its type on first iterate - imm, direct, struct, register*/
StatusCode checkType(char *reqOp, opType* result)
{
    opType operand;
    char* dotPtr;
    if(*reqOp=='#' && isInt(reqOp+1)) /* number literal */
        operand=Immediate;
    /*r1..r7, check if 'r' 1st, digit 2nd, 2 chars word*/
    else if(isRegister(reqOp))
        operand=Register;
    else
    {
        operand=Direct;
        if((dotPtr = strchr(reqOp,'.')) != NULL)
        {
            if(*(dotPtr+1) == '1' || *(dotPtr+1) == '2') /* struct */
                operand=Struct;
            else
                return operand_type_error;
        }
    }
    *result = operand;
    return success;
}
/*gets string operands and checks its type on second iterate - imm, direct, struct, register*/
StatusCode checkTypeSecIter(SymbolType num, opType* result)
{
    opType operand;
    if(num==tData || num==tCode || num==tString)
        operand=Direct;
    else if(num==tStruct)
        operand=Struct;
    else
        return operand_type_error;
    *result = operand;
    return success;
}
/*The func calculated how many rows the operand inserted takes*/
StatusCode opSumRow(opType operand, int* result)
{
    int rowCnt=0;
    /*Struct operand takes 2 rows*/
    if(operand==Struct)
        rowCnt=2;
    /*Dir, Reg, Imm takes 1 row*/
    else if(operand==Direct || operand==Register || operand==Immediate)
        rowCnt=1;
    else
        return row_count_error;
    *result = rowCnt;
    return success;
}
/*takes 2 operands and returns number of rows the command will take*/
StatusCode instSumRow(char *first, char *second, int* result)
{
    int firstOpSum=0;
    int secOpSum=0;
    int sumRows=0;
    StatusCode code;
    opType firstTP, secondTP;
    /*check if only first operand exist*/
    if(first!=NULL && second==NULL)
    {
        /*get operand type*/
        firstTP=checkType(first,&firstTP);
        /*get sum of rows for operand*/
        if((code=opSumRow(firstTP,&firstOpSum)) < 0)
            return code;
    }
    if(second != NULL)
    {
        if((code=checkType(second,&secondTP)) < 0)
            return code;
        if((code=opSumRow(secondTP,&secOpSum)) < 0)
            return code;
    }
    /*EDGE CASE - both registers*/
    if(firstTP==Register && secondTP==Register)
        secOpSum=0;
    /*calculates sum: first operand, second operand, command*/
    sumRows=firstOpSum+secOpSum+1;
    *result = sumRows;
    return success;
}
/*search the command, return his place(equals to his binary 4 bits)*/
int searchOp(char* opCode)
{
    int i=0;
    for(i=0;i<NUM_OF_INSTRUCTS;i++)
        if(strcmp(opCode,instructions[i])==0)
            return i;
    return -1;
}
