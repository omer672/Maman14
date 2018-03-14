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

int isWhitespace(char* line)
{
    while (*line != '\0') {
        if (!isspace((unsigned char)(*line)))
            return 0;
        line++;
    }
    return 1;
}

int isInstuction(char* string)
{
    return searchStringInArray(instructions,NUM_OF_INSTRUCTS,string);
}

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
    char *ptr;
    strtol(string, &ptr, 10);
    return (isWhitespace(ptr) || *ptr == '\0'); /* If the rest of the string is empty it still counts as an int*/
}

int isString(char* string)
{

}

StatusCode insertTypeData(char* dataToInsert)
{
    int DC;
    int dataArray[MAX_FILE_LENGTH];
    int tempDataArray[MAX_FILE_LENGTH];
    int i = 0;
    int j;
    char* token;
    char line[strlen(dataToInsert)];

    if(isWhitespace(dataToInsert))
        return wrong_number_of_operands;
    strcpy(line,dataToInsert); /* strtok ruins the string */
    token = strtok(line, ",");

    while(token != NULL)
    {
        if(isInt(token)) /* Every token is suppose to contain one integer */
            tempDataArray[i] = atoi(token);
        else
            return data_syntex_error;
        token = strtok(NULL, ",");
        i++;
    }

    for(j=DC; j<DC+i && DC<MAX_FILE_LENGTH;j++,DC++)
    {
        dataArray[DC] = tempDataArray[j-DC]; /* Fill the real data array after we discovered no errors */
    }
    return success;
}

StatusCode insertTypeString(char* dataToInsert)
{
    int DC;
    int dataArray[MAX_FILE_LENGTH];

    char actualString[MAX_FILE_LENGTH];
    int i;
    int count = 0;
    char *token;
    char line[strlen(dataToInsert)];

    if(isWhitespace(dataToInsert))
        return wrong_number_of_operands;

    strcpy(line,dataToInsert); /* strtok ruins the string */
    token = strtok (line, "\"");
    while (token != NULL)
    {
        if(strcmp(token,dataToInsert) == 0) /* Meaning no token were found, hence no " was found */
            return string_syntex_error;
        if (!isWhitespace (token)) /* seperate strings by ", and if the token isn't empty it means we found an actual string */
        {
            strcpy (actualString, token);
            count++;
        }
        token = strtok (NULL, "\"");
    }
    if (count != 1) /* Meaning no strings were found or more than 1 string was found */
        return string_syntex_error;

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
    StatusCode code;
    int count = 0;
    char* token;
    char line[strlen(dataToInsert)];

    strcpy(line,dataToInsert); /* strtok ruins the string */
    token = strtok(line, ",");
    while (token != NULL) /* TODO: make sure string can't contain ',' or find a new way to implement */
    {
        if(count == 0) /* First token should be a number */
        {
            if((code = insertTypeData(token)) < 0)
                return code;
        }
        else if(count > 2) /* Only two tokens expected */
            return struct_syntex_error;
        count++;
        token = strtok (NULL, ",");
    }

    /* At this point token should be a string */
    if((code = insertTypeString(token)) < 0)
        return code;
    return success;
}

StatusCode insertData(char* type, char* data)
{
    if (strcmp(type, dataTypes[0]))
    { /* .data */
        return insertTypeData(data);
    }
    else if (strcmp(type, dataTypes[1]))
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
    char first[strlen(symbols)];
    char second[strlen(symbols)];

    if(sscanf(symbols,"%s %s",first,second) == 1) /* Used to check if there is more than 1 operand */
    {
        return setSymbol(first, 0, "extern", external);
    }
    else
    {
        return wrong_number_of_operands;
    }
}


/* TODO: please implement Tal - insert into instruction array, and increase IC by L (calc according to the table on the instructions) */
StatusCode insertInstruction(char* instruction, char* operands, int isSecondIteration)
{
    int instructionsArray[MAX_FILE_LENGTH];
    int sumL=0;
    int keepBin;//keep the binary num before insert to instruction array
    char* firstOp, secondOp;
    char* temp=strtok(operands,',');
    strcpy(firstOp,temp); //first operand
    temp=strtok(NULL,",");
    strcpy(secondOp,temp);//second operand
    sumL=instSumRow(firstOp,secondOp);//Sum of rows - to IC
    keepBin=searchOp(instruction);//will search the command and return its place(equals to his binary number)
    //insert 4 bits instruction binary to array
    instructionsArray[IC]=keepBin;
    opType typeOne,typeTwo;
    typeOne=checkType(firstOp);
    typeTwo=checkType(secondOp);
    /*First iterate*/
    if(isSecondIteration==0) /*Tal: different behaviours depending on iteration - read on it please*/
    {
        if (typeOne == '-' || typeTwo == '-')//unrecognized Symbol, enter '-'
        {
            instructionsArray[IC] = '-';//will return on second iteration
            IC++;//increases IC by '1' and continue;
        } else//casual operands
        {
            keepBin = typeOne;//get binary by enum place.
            /*insert 2 bits for source operand*/
            instructionsArray[IC] = (instructionsArray[IC] << 2) + keepBin;
            keepBin = typeTwo;
            /**insert 2 bits for destination operand**/
            instructionsArray[IC] = (instructionsArray[IC] << 2) + keepBin;
            /**insert 2 bits for A/R/E - OMER, can implement this one?**/
            instructionsArray[IC] =
            IC += sumL;//increases IC by the rows needed by the inserted command
        }
    }
    /*Second iterate*/
    else
    {
        if(instructionsArray[IC]=='-')
        {
            instructionsArray[IC]='0';
            //Will find symbol on checkType function
            keepBin = typeOne;//get binary by enum place.
            /*insert 2 bits for source operand*/
            instructionsArray[IC] = (instructionsArray[IC] << 2) + keepBin;
            keepBin = typeTwo;
            /**insert 2 bits for destination operand**/
            instructionsArray[IC] = (instructionsArray[IC] << 2) + keepBin;
            /**insert 2 bits for A/R/E - OMER, can implement this one?**/
            instructionsArray[IC] =
            IC += sumL;//increases IC by the rows needed by the inserted command
        }
        else//covered on first iterate
            IC++;
    }

    /*EDGE CASE ERROR - More than 2 operands at the same command*/



    /*to calculate L need to check how many rows the instruction will take*/
    /*Needed Functions
     * check operands type - checkType
     * check machine code the operand will take by his type - opSumRow
     * take the whole row and check how many rows will take - instSumRow
     * add instruction to array and increase by L - This func*/


}
