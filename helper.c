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
void insertData(char* type, char* data)/*NEED TO ADD EDGE CASES - check illegal cases*/
{
    if (data!=NULL) {
        if (strcmp(type, dataTypes[0])) {
            if(DC<MAX_FILE_LENGTH)
            {
                int takeNum;
                char *ptr;
                takeNum=(int)strtol(data,&ptr,10);//takes int number from array
                dataArray[DC]=takeNum;
                DC++;
            }
            else
                printf("ERROR");
        } else if (strcmp(type, dataTypes[1])) {
            /*"abcdef" - check if quotation mark exists at start and end*/
            int endStr=strlen(data)-1;
            if(data[0]=='"' && data[strlen(data)-1]=='"')
            {
                /*INESRT chars to array*/
                for(data+1;*data!='"'&&DC<MAX_FILE_LENGTH;data++,DC++)
                {
                    dataArray[DC]=*data;
                }
                dataArray[DC]='\0'; /*END OF ARRAY*/
                DC++;
            }
            else
                printf("ERROR");
        } else {//expect struct - Implement int and string adding to struct with cases
            if(DC<MAX_FILE_LENGTH)
            {
                /*(int),("string")*/
                if(data+1==',')/*half way to correct struct*/
                {
                    int takeNum;
                    char *ptr;
                    takeNum=(int)strtol(data,&ptr,10);//takes int number from array
                    dataArray[DC]=takeNum;
                    DC++;
                    data++;
                    if(ptr!=NULL&&ptr[0]=='"')/*Checks if after ',' exists '"' for string*/
                    {
                        int endStr=strlen(data)-1;
                        if(data[0]=='"' && data[strlen(data)-1]=='"')
                        {
                            /*INESRT chars to array*/
                            for(data+1;*data!='"'&&DC<MAX_FILE_LENGTH;data++,DC++)
                            {
                                dataArray[DC]=*data;
                            }
                            dataArray[DC]='\0'; /*end struct array*/
                            DC++;
                        }
                    }

                }
            }
        }
    }
}

/* TODO: please implement Tal - insert into symbol table */
void insertExtern(char* symbols)
{
    /*got extern - uses functions from Symbol table and linkedList*/
    /***** to figure up use of MARK*****/
    int value = stringToBinary(symbols);
    if(isLegal(symbols))//check if Symbol found is legal
    {   /*checks symbol doesnt exist on table, else - do nothing*/
        if(!doesExist(symbols)) {
            /*name - symbols var, value - decimal base, mark - , type - external by definition*/
            setSymbol(symbols, value, mark, 0);//the func adds the symbol to table
        }

    }
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