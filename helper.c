#include "helper.h"

int searchStringInArray(char* array[],int length, char* string)
{
    int i;
    for(i=0;i<length;i++)
    {
        if(strcmp(array[i],string))
            return 1;
    }
    return 0;
}

int isInstuction(char* string)
{
    return searchStringInArray(instructions,NUM_OF_INSTRUCTS,string);
}

int isDataType(char* string)
{
    return searchStringInArray(dataTypes,NUM_OF_DATA_TYPES,string);
}

int isRegister(char* string)
{
    return searchStringInArray(registers,NUM_OF_REGISTERS,string);
}

int isExtern(char* string)
{
    return strcmp(ENTRY,string);
}

int isEntry(char* string)
{
    return strcmp(ENTRY,string);
}

int isInt(char* string)
{

}

int isString(char* string)
{

}

/* TODO: please implement Tal - insert into data array, and increase DC */
void insertData(char* type, char* data)
{

    if(strcmp(type,dataTypes[0]))
    {
        //expect ints
    }
    else if(strcmp(type,dataTypes[1]))
    {
        //expect string
    }
    else
    {//expect struct

    }
}

/* TODO: please implement Tal - insert into symbol table */
void insertExtern(char* symbols)
{

}
/* TODO: please implement Tal - insert into instruction array, and increase IC by L (calc according to the table on the instructions) */
void insertInstruction(char* instruction, char* operands, int isSecondIteration)
{
    if(isSecondIteration) /*Tal: different behaviours depending on iteration - read on it please*/
    {

    }
    else
    {

    }
}
