#include "helper.h"

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

void insertData(char* type, char* data[] , int dataStart, int end)
{

    if(strcmp(str,dataTypes[0]))
    {
        //expect ints
    }
    else if(strcmp(str,dataTypes[1]))
    {
        //expect string
    }
    else
    {//expect struct

    }
}
