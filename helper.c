#include "helper.h"
/*The functions searches if string exists in array*/
int searchStringInArray(char* array[],int length, char* string)
{
    int i;
    for(i=0;i<length;i++)
    {
        if(strcmp(array[i],string) == 0)
            return 1;
    }
    return 0;
}

int isWhitespace(char* line)
{
    while (*line != '\0') {
        if (!isspace((unsigned char)(*line)))
            return 0;
        line++;
    }
    return 1;
}
/*The function checks if string inserted to the function is an Instruction*/
int isInstuction(char* string)
{
    return searchStringInArray(instructions,NUM_OF_INSTRUCTS,string);
}

/*The functions checks if string inserted is a data type by definition*/
int isDataType(char* string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return searchStringInArray(dataTypes,NUM_OF_DATA_TYPES,string);
    }
    else
        return 0;
}

/*The function checks if string inserted is a register(r1..r9)*/
int isRegister(char* string)
{
    return searchStringInArray(registers,NUM_OF_REGISTERS,string);
}

/*The function checks if string inserted is a extern by definition*/
int isExtern(char* string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return (strcmp(EXTERN,string) == 0);
    }
    else
        return 0;
}

int isEntry(char* string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return (strcmp(ENTRY,string) == 0);
    }
    else
        return 0;
}

int isInt(char* string)
{
    char *ptr;
    strtol(string, &ptr, 10);
    return (isWhitespace(ptr) || *ptr == '\0'); /* If the rest of the string is empty it still counts as an int*/
}

int isString(char* string)
{

}

StatusCode insertTypeData(char* dataToInsert)
{
    int tempDataArray[MAX_FILE_LENGTH];
    int i = 0;
    int j;
    int endIndex;
    char* token;
    char line[MAX_FILE_LENGTH];
    if(isWhitespace(dataToInsert))
        return wrong_number_of_operands;
    strcpy(line,dataToInsert); /* strtok ruins the string */
    token = strtok(line, ",");

    while(token != NULL)
    {
        if(isInt(token)) /* Every token is suppose to contain one integer */
            tempDataArray[i] = twosComplements(atoi(token));
        else
            return data_syntax_error;
        token = strtok(NULL, ",");
        i++;
    }
    endIndex = DC+i;
    for(j=DC; j<endIndex && DC<MAX_FILE_LENGTH;j++,DC++)
    {
        dataArray[DC] = tempDataArray[j-DC]; /* Fill the real data array after we discovered no errors */
    }
    return success;
}

StatusCode insertTypeString(char* dataToInsert)
{
    char actualString[MAX_FILE_LENGTH];
    int i;
    int count = 0;
    char* token;
    char* savedPtr;
    char delimiter[1] = "\"";
    char line[MAX_FILE_LENGTH];

    if(isWhitespace(dataToInsert))
        return wrong_number_of_operands;

    strcpy(line,dataToInsert); /* strtok ruins the string */

    token = strtok_r(line, delimiter,&savedPtr);
    while (token != NULL)
    {
        if(strcmp(token,dataToInsert) == 0) /* Meaning no token were found, hence no " was found */
            return string_syntax_error;
        if (!isWhitespace (token)) /* seperate strings by ", and if the token isn't empty it means we found an actual string */
        {
            strcpy (actualString, token);
            count++;
        }
        token = strtok_r(NULL, delimiter,&savedPtr);
    }
    if (count != 1) /* Meaning no strings were found or more than 1 string was found */
        return string_syntax_error;

    /*INESRT chars to array*/
    for(i=0;i<strlen(actualString);i++,DC++)
    {
        dataArray[DC]= actualString[i];
    }
    dataArray[DC]='\0'; /*END OF ARRAY*/
    DC++;
    return success;
}

StatusCode insertTypeStruct(char* dataToInsert)
{
    char* token;
    char* savedPtr;
    char line[MAX_FILE_LENGTH];

    strcpy(line,dataToInsert); /* strtok ruins the string */
    token = strtok_r(line, ",",&savedPtr);
    if(insertTypeData(token) < 0) /* First token should be a number */
        return struct_syntax_error;
    token = strtok_r(NULL,"",&savedPtr); /* Get the rest of the string */

    /* At this point token should be a string */
    if(insertTypeString(token) < 0)
        return struct_syntax_error;
    return success;
}

StatusCode insertData(char* type, char* data)
{
    type++; /* starts with . so we skip it */
    if (strcmp(type, dataTypes[0]) == 0)
    { /* .data */
        return insertTypeData(data);
    }
    else if (strcmp(type, dataTypes[1]) == 0)
    { /* .string */
        return insertTypeString(data);
    }
    else
    { /* .struct */
        return insertTypeStruct(data);
    }
}

StatusCode insertExtern(char* symbols)
{
    /*got extern - uses functions from Symbol table and linkedList*/
    char first[MAX_FILE_LENGTH];
    char second[MAX_FILE_LENGTH];
    if(sscanf(symbols,"%s %s",first,second) == 1) /* Used to check if there is more than 1 operand */
    {
        return setSymbol(first, 0,tCode,0, external);
    }
    else
    {
        return wrong_number_of_operands;
    }
}


/* TODO: please implement Tal - insert into instruction array, and increase IC by L (calc according to the table on the instructions) */
StatusCode insertInstruction(char* instruction, char* operands, int isSecondIteration)
{
    int sumL=0;
    int keepBin;/*keep the binary num before insert to instruction array*/
    char* firstOp, secondOp;
    char* temp=strtok(operands,",");
    strcpy(firstOp,temp); /*first operand*/
    temp=strtok(NULL,",");
    strcpy(secondOp,temp);/*second operand*/
    sumL=instSumRow(firstOp,secondOp);/*Sum of rows - to IC*/
    keepBin=searchOp(instruction);/*will search the command and return its place(equals to his binary number)*/
    /*insert 4 bits instruction binary to array*/
    instructionsArray[IC]=(int)keepBin;/*4 bits command inserted first*/
    opType typeOne,typeTwo;
    typeOne=checkType(firstOp);/*get the type of the first operand*/
    typeTwo=checkType(secondOp);/*get the type of the second operand*/
    /*First iterate*/
    if(isSecondIteration==0) /*Tal: different behaviours depending on iteration - read on it please*/
    {
        if (typeOne == '-' || typeTwo == '-')/*case got on unrecognized Symbol, enter '-'*/
        {
            instructionsArray[IC] = '-';/*will enter '-' as flag for second iterate - and continues*/
            IC++;/*increases IC by '1' and continue;*/
        } else/*casual operands recognized*/
        {
            keepBin = typeOne;/*get binary by enum place.*/
            /*insert 2 bits for source operand*/
            instructionsArray[IC] = (instructionsArray[IC] << 2) + keepBin;
            keepBin = typeTwo;
            /**insert 2 bits for destination operand**/
            instructionsArray[IC] = (instructionsArray[IC] << 2) + keepBin;
            /*shift left 2 bits for A/R/E - first iterate, will place 00 end of command*/
            instructionsArray[IC] = 0<<2;
            IC += sumL;/*increases IC by the rows needed by the inserted command*/
        }
    }
        /*Second iterate*/
    else
    {
        Symbol* op1, *op2;/*gets the type of Symbols that found on second iterate, similar to first iterate by definition*/
        if(doesExist(firstOp))
            op1=doesExist(firstOp);
        if(doesExist(secondOp))
            op2=doesExist(secondOp);
        SymbolType opType1=op1->symbolType;
        SymbolType opType2=op2->symbolType;
        typeOne=checkTypeSecIter(opType1);
        typeTwo=checkTypeSecIter(opType2);

        if(instructionsArray[IC]=='-')/*if found flag '-' for symbols that have not recognized on first iterate*/
        {
            instructionsArray[IC]='0';
            /*Will find symbol on checkType function*/
            keepBin = typeOne;/*get binary by enum place.*/
            /*insert 2 bits for source operand*/
            instructionsArray[IC] = (instructionsArray[IC] << 2) + keepBin;
            keepBin = typeTwo;
            /**insert 2 bits for destination operand**/
            instructionsArray[IC] = (instructionsArray[IC] << 2) + keepBin;
            /**insert 2 bits for A/R/E - OMER, can implement this one?**/
            instructionsArray[IC] = (instructionsArray[IC] << 2) +opType1;
            IC += sumL;/*increases IC by the rows needed by the inserted command*/
        }
        else/*covered on first iterate*/
            IC++;
    }
    return success;
