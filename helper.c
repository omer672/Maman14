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

/*The function checks for white spaces on line inserted*/
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

/*The function checks if string entered to function is an entry by definition*/
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

/*The function check if string inserted to the function is int by definition*/
int isInt(char* string)
{
    char *ptr;
    strtol(string, &ptr, 10);
    long int result = strtol(string, &ptr, 10);
    (void)result;
    return (isWhitespace(ptr) || *ptr == '\0'); /* If the rest of the string is empty it still counts as an int*/
}

/*The function checks if the source and destination operand are valid by instructions*/
int isValidSourceDest(OpCodes code,opType source, opType dest)
{
    int result = 0;
    switch(code)
    {
    case mov:
        result = dest != Immediate;
        break;
    case cmp:
        result = 1;
        break;
    case add:
    case sub:
    case nnot:
    case clr:
        result = dest != Immediate;
        break;
    case lea:
        result = (source == Direct || source == Struct) && dest != Immediate;
        break;
    case inc:
    case dec:
    case jmp:
    case bne:
    case red:
        result = dest != Immediate;
        break;
    case prn:
        result = 1;
        break;
    case jsr:
        result = dest != Immediate;
        break;
    case rts:
    case stop:
        result = 1;
        break;
    }
    return result;
}

/*The function checks if the operand is Struct pattern*/
int findStructField(char* operand)
{
    char* dotPtr;
    if((dotPtr = strchr(operand,'.')) != NULL)
    {
        return *(dotPtr+1) - '0'; /* 1 or 2 */
    }
    return 0;
}

/*The function inserts operand - Direct type*/
void insertDirect(Symbol* operand, int index)
{
    /* No need for validation because we already validated earlier */
    int numberToInsert;
    if(operand->type == external) /* If using external, we keep the adress of the command that used it */
    {
        numberToInsert = (operand->value) << 2;
        operand->references[operand->refCounter] = index;
        operand->refCounter++;
    }
    else
        numberToInsert = (operand->value+START_ADDRESS) << 2;
    numberToInsert += (operand->type + 1); /* External is 0, so we need to add 1 */
    instructionsArray[index] = numberToInsert;
}

/*The function inserts operand from type - Struct*/
void insertStructField(char* operand, int index)
{
    /* No need for validation because we already validated earlier */
    int numberToInsert = findStructField(operand);
    numberToInsert <<= 2;
    instructionsArray[index] = numberToInsert;
}
/*The function inserts operand to instructionsArray by Immediate type*/
void insertImmediate(char* operand, int index)
{
    /* No need for validation because we already validated earlier */
    int numberToInsert = twosComplements(atoi(operand+1),NUMBER_OF_BITS_INSTRUCTION); /* first char will be # */
    instructionsArray[index] = (numberToInsert<<2); /* Absolute, no need to add */
}

/*The function inserts source and destination operands - Registers type*/
void insertRegisters(char* srcRegister,char* destRegister, int index)
{
    int numberToInsert = 0;
    /* No need for validation because we already validated earlier */
    if(srcRegister != NULL && destRegister != NULL)
    {
        numberToInsert = *(srcRegister+1) - '0';
        numberToInsert <<= 4;
        numberToInsert += *(destRegister+1) - '0';
    }
    else
    {
        if(srcRegister != NULL)
        {
            numberToInsert = *(srcRegister+1) - '0';
            numberToInsert <<= 4;
        }
        else
            numberToInsert += *(destRegister+1) - '0';
    }
    instructionsArray[index] = (numberToInsert<<2); /* Absolute, no need to add */
}

StatusCode trimOperand(char* operand)
{
    char first[LINE_LENGTH];
    char second[LINE_LENGTH];
    if(sscanf(operand,"%s %s",first,second) != 1) /* Testing if there is more than 1 operand */
        return wrong_number_of_operands;
    else
        strcpy(operand,first);
    return success;
}

StatusCode insertTypeData(char* dataToInsert)
{
    int tempDataArray[MAX_FILE_LENGTH];
    int i = 0;
    int j;
    char* token;
    char line[MAX_FILE_LENGTH];
    if(isWhitespace(dataToInsert))
        return wrong_number_of_operands;
    strcpy(line,dataToInsert); /* strtok ruins the string */
    token = strtok(line, ",");

    while(token != NULL)
    {
        if(isInt(token)) /* Every token is suppose to contain one integer */
            tempDataArray[i] = twosComplements(atoi(token),NUMBER_OF_BITS_DATA);
        else
            return data_syntax_error;
        token = strtok(NULL, ",");
        i++;
    }
    for(j=0; j<i && DC<MAX_FILE_LENGTH;j++)
    {
        dataArray[DC+j] = tempDataArray[j]; /* Fill the real data array after we discovered no errors */
    }
    DC+=i;
    return success;
}

StatusCode insertTypeString(char* dataToInsert)
{
    char actualString[MAX_FILE_LENGTH];
    unsigned int i;
    int count = 0;
    char* token;
    char delimiter[1] = "\"";
    char line[MAX_FILE_LENGTH];

    if(isWhitespace(dataToInsert))
        return wrong_number_of_operands;

    strcpy(line,dataToInsert); /* strtok ruins the string */

    token = strtok(line, delimiter);
    while (token != NULL)
    {
        if(strcmp(token,dataToInsert) == 0) /* Meaning no token were found, hence no " was found */
            return string_syntax_error;
        if (!isWhitespace (token)) /* seperate strings by ", and if the token isn't empty it means we found an actual string */
        {
            strcpy (actualString, token);
            count++;
        }
        token = strtok(NULL, delimiter); /* Keep going from where we were last */
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
    char line[MAX_FILE_LENGTH];

    strcpy(line,dataToInsert); /* strtok ruins the string */
    token = strtok(line, ",");
    if(insertTypeData(token) < 0) /* First token should be a number */
        return struct_syntax_error;
    token = strtok(line+strlen(line)+1,""); /* Get the rest of the string */

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
        externFound = 1;
        return setSymbol(first, 0,tCode,0, external);
    }
    else
    {
        return wrong_number_of_operands;
    }
}

StatusCode insertInstruction(char* instruction, char* operands, int isSecondIteration)
{
    StatusCode code;
    opType sourceType = Immediate;
    opType destType = Immediate; /* 0 as a default value */
    Symbol* op1;
    Symbol* op2;
    Symbol* op1 = NULL;
    Symbol* op2 = NULL;
    int sumL=0;
    int i;
    int bothRegisters = 0; /* boolean indicating if both operands are registers */
    int count = 0;
    int numberOfOperands;
    int keepBin;/*keep the binary num before insert to instruction array*/
    char firstOp[LINE_LENGTH];
    char secondOp[LINE_LENGTH];
    char line[LINE_LENGTH];
    char* token;
    strcpy(line,operands); /* strtok ruins the string */
    keepBin=searchOp(instruction);/*will search the command and return its place(equals to his binary number)*/

    if(keepBin <= FIRST_INSTRUCTION_GROUP_INDEX) /* Two operands */
    {
        numberOfOperands = 2;
        token = strtok(line, ",");
        if(token == NULL)
            return wrong_number_of_operands;
        strcpy(firstOp,token);
        if((code = trimOperand(firstOp)) < 0)
            return code;
        while(token != NULL)
        {
            if(count <= 1) /* Only copy the real operand, as we will search for extra , */
                strcpy(secondOp,token);
            token = strtok(NULL,","); /* get the rest, should be 1 more operand */
            count++;
        }
        if(count > numberOfOperands)
            return wrong_number_of_operands;
        if((code = trimOperand(secondOp)) < 0)
            return code;
        if((code = checkType(firstOp,&sourceType)) < 0) /*get the type of the first operand*/
            return code;
        if((code = checkType(secondOp,&destType)) < 0) /*get the type of the second operand*/
            return code;
    }
    else if(keepBin > FIRST_INSTRUCTION_GROUP_INDEX && keepBin <= SECOND_INSTRUCTION_GROUP_INDEX) /* One operand */
    {
        numberOfOperands = 1;
        if(sscanf(line,"%s %s",firstOp, secondOp) != numberOfOperands) /* using secondOp to test for extra text */
            return wrong_number_of_operands;
        if((code = checkType(firstOp,&destType)) < 0) /*get the type of the first operand*/
            return code;
    }
    else /* No operands */
    {
        numberOfOperands = 0;
        if(!isWhitespace(line))
            return wrong_number_of_operands;
    }
    /* Validate the operands */
    if(!isValidSourceDest(keepBin,sourceType,destType))
        return invalid_source_dest_operands;
    if((code = instSumRow(sourceType,destType,numberOfOperands,&sumL)) < 0)/*Sum of rows - to IC*/
        return code;
    /*First iteration*/
    if(isSecondIteration == 0)
    {
        /*insert 4 bits instruction binary to array*/
        instructionsArray[IC]= keepBin;/*4 bits command inserted first*/
        /*insert 2 bits for source operand*/
        instructionsArray[IC] = (instructionsArray[IC] << 2) + sourceType; /*get binary by enum place.*/
        instructionsArray[IC] = (instructionsArray[IC] << 2) + destType; /*insert 2 bits for destination operand*/
        /*shift left 2 bits for A/R/E - first iterate, will place 00 end of command*/
        instructionsArray[IC] = instructionsArray[IC] << 2;
        IC += sumL;/*increases IC by the rows needed by the inserted command*/
    }
    else /*Second iteration*/
    {
        if(numberOfOperands > 0)
        {
            if(numberOfOperands == 1)
            {
                if(destType == Struct || destType == Direct)
                {
                    if(destType == Direct)
                    {
                        if((op1 = doesExist(firstOp)) == NULL)
                            return symbol_doesnt_exist;
                    }
                    else
                    {
                        if((op1 = doesStructExist(firstOp)) == NULL)
                            return symbol_doesnt_exist;
                    }
                }
            }
            else /* Two operands */
            {
                if(sourceType == Struct || sourceType == Direct)
                {
                    if(sourceType == Direct)
                    {
                        if((op1 = doesExist(firstOp)) == NULL)
                            return symbol_doesnt_exist;
                    }
                    else
                    {
                        if((op1 = doesStructExist(firstOp)) == NULL)
                            return symbol_doesnt_exist;
                    }
                }
                if(destType == Struct || destType == Direct)
                {
                    if(destType == Direct)
                    {
                        if((op2 = doesExist(secondOp)) == NULL)
                            return symbol_doesnt_exist;
                    }
                    else
                    {
                        if((op2 = doesStructExist(secondOp)) == NULL)
                            return symbol_doesnt_exist;
                    }
                }
            }
        }
        /* Fill missing instructions, when number of operands > 0 */
        bothRegisters = (numberOfOperands == 2 && sourceType == Register && destType == Register);
        i=1;
        if(numberOfOperands == 1)
        {
            switch(destType)
            {
            case Immediate:
                insertImmediate(firstOp,i+IC);
                break;
            case Direct:
                insertDirect(op1,i+IC);
                break;
            case Struct:
                insertDirect(op1,i+IC);
                i++;
                insertStructField(firstOp,i+IC);
                break;
            case Register:
                insertRegisters(firstOp,NULL,i+IC);
                break;
            }
        }
        else /* 2 operands */
        {
            switch(sourceType)
            {
            case Immediate:
                insertImmediate(firstOp,i+IC);
                break;
            case Direct:
                insertDirect(op1,i+IC);
                break;
            case Struct:
                insertDirect(op1,i+IC);
                i++;
                insertStructField(firstOp,i+IC);
                break;
            case Register:
                insertRegisters(firstOp,bothRegisters ? secondOp : NULL,i+IC);
                break;
            }
            i++;
            switch(destType)
            {
            case Immediate:
                insertImmediate(secondOp,i+IC);
                break;
            case Direct:
                insertDirect(op2,i+IC);
                break;
            case Struct:
                insertDirect(op2,i+IC);
                i++;
                insertStructField(secondOp,i+IC);
                break;
            case Register:
                if(!bothRegisters) /* otherwise, we already inserted earlier */
                    insertRegisters(NULL,secondOp,i+IC);
                break;
            }
        }
        IC += sumL; /*increases IC by the rows needed by the inserted command*/
    }
    return success;
}
