#include "commandsToBinary.h"

void markEntry(char* symbol)
{
    Symbol* sym;
    int i = 0;
    char name[strlen(symbol)];
    char* token;
    char delimiter[11] = " \t\n\v\f\r"; /* all of the whitespace chars*/
    token = strtok(symbol,delimiter);

    while(token != NULL)
    {
        if(i==1)
            strcpy(name,token);
        i++;
        token = strtok(NULL,delimiter);
    }
    if(i!=1)
    {
        if(i==0)
            /*ERROR : no openrands*/;
        if(i>1)
            /*ERROR : i opernands found,expected 1*/;
    }
    else
    {
        if((sym = doesExist(name)) != NULL)
        {
            sym->mark = ENTRY;
        }
        else
        {
            /* ERROR: symbol doesnt exist */
        }
    }
}
/*gets string operands and checks its type - imm, direct, struct, register*/
opType checkType(char *reqOp)
{
    opType operand;
    if(reqOp[0]=="#"){
        operand=Immediate;}
        /*label? to check if symbols need to be part of the func*/
    else if(doesExist(reqOp)){
        operand=Direct;}
    else if(isdigit(reqOp[0])&&reqOp[1]==','){
        operand=Struct;}
        /*r1..r9, check if 'r' 1st, digit 2nd, 2 chars word*/
    else if(*reqOp=='r' && isdigit(reqOp[1]) && strlen(reqOp)==2)
        operand=Register;
    else
        printf("ERROR");
    return operand;
}

int opSumRow(opType operand)
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
        //ERROR
        rowCnt=-1;
    }
    return rowCnt;
}

int instSumRow(char *first, char *second)
{
    /*IMPLEMENT*/
}
