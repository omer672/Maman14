#include "commandsToBinary.h"

StatusCode markEntry(char* symbol)
{
    Symbol* sym;
    int i = 0;
    char name[MAX_FILE_LENGTH];
    char* token;
    char delimiter[6] = " \t\n\v\f\r"; /* all of the whitespace chars*/
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
StatusCode checkType(char *reqOp)
{
    opType operand;
    if(reqOp[0]=='#'){
        operand=Immediate;}
    /*label? to check if symbols need to be part of the func*/
    else if(doesExist(reqOp)){
        operand=Direct;}
    else if(isdigit(reqOp[0])&&reqOp[1]==','){
        operand=Struct;}
    /*r1..r9, check if 'r' 1st, digit 2nd, 2 chars word*/
    else if(isRegister(reqOp))
        operand=Register;
    else{
        /*ERROR - second iteration, search symbol argument and implement into up if's*/
        operand='-';
        return symbol_not_reconized;
        }
    /*return operand; ERROR FIXING, NOTICE - OMER*/
    return success;
}
/*gets string operands and checks its type on second iterate - imm, direct, struct, register*/
StatusCode checkTypeSecIter(SymbolType num)
{
    opType operand;
    if(num==tData || num==tCode || num==tString)
        operand=Direct;
    else if(num==tStruct)
        operand=Struct;
    else
        return operand_type_error;
    /*return operand; ERROR FIXING, NOTICE - OMER*/
    return success;
}
/*The func calculated how many rows the operand inserted takes*/
StatusCode opSumRow(opType operand)
{
    int rowCnt=0;
    /*Struct operand takes 2 rows*/
    if(operand==Struct)
    {
        rowCnt=2;
    }
    /*Dir, Reg, Imm takes 1 row*/
    else if(operand==Direct || operand==Register || operand==Immediate)
    {
        rowCnt=1;
    }
    else
    {
        /*ERROR FIXING - NOTICE OMER*/
        /*rowCnt=-1;*/
        return row_count_error;
    }
    /*return rowCnt; ERROR FIXING - NOTICE OMER*/
    return success;
}
/*takes 2 operands and returns number of rows the command will take*/
StatusCode instSumRow(char *first, char *second)
{
    int firstOpSum=0;
    int secOpSum=0;
    int sumRows=0;
    opType firstTP, secondTP;
    /*check if only first operand exist*/
    if(first!=NULL && second==NULL)
    {
        /*get operand type*/
        firstTP=checkType(first);
        /*get sum of rows for operand*/
        firstOpSum=opSumRow(firstTP);
        if(firstOpSum==01){
            /*printf("ERROR") ERROR FIXING - NOTICE OMER;
            return 0;*/
            return inst_sum_error;
        }
    }

    if(second!=NULL)
    {
        secondTP=checkType(second);
        secOpSum=opSumRow(secondTP);
        if(secOpSum==-1) {
            /*printf("ERROR");
            return 0; ERROR FIXING - NOTICE OMER*/
            return inst_sum_error;
        }
    }
    /*EDGE CASE - both registers*/
    if(firstTP==Register && secondTP==Register)
        secOpSum=0;
    /*calculates sum: first operand, second operand, command*/
    sumRows=firstOpSum+secOpSum+1;
    /*return sumRows; ERROR FIXING - NOTICE OMER*/
    return success;
}
/*search the command, return his place(equals to his binary 4 bits)*/
int searchOp(char* opCode)
{
    int i=0;
    int found = -1;
    while(i!=16)
    {
        if(strcmp(opCode,instructions[i])==0) {
            found = i;
            return found;
        }
        else
            i++;
    }
    return -1;
}
