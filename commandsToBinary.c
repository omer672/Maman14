#include "commandsToBinary.h"

StatusCode markEntry(char* symbol)
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
        return wrong_number_of_operands;
    else
    {
        if((sym = doesExist(name)) != NULL)
        {
            sym->mark = ENTRY;
        }
        else
            return symbol_doesnt_exsist;
    }
    return success;
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
/*takes 2 operands and returns number of rows the command will take*/
int instSumRow(char *first, char *second)
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
            printf("ERROR");
            return 0;
        }
    }

    if(second!=NULL)
    {
        secondTP=checkType(second);
        secOpSum=opSumRow(secondTP);
        if(secOpSum==-1) {
            printf("ERROR");
            return 0;
        }
    }

    /*EDGE CASE - both registers*/
    if(firstTP==Register && secondTP==Register)
        secOpSum=0;

    /*return sum:
     * first operand
     * second operand
     * command*/
    sumRows=firstOpSum+secOpSum+1;
    return sumRows;
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
