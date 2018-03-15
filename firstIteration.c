#include "firstIteration.h"

void clearGlobals()
{
    int i;
    for(i=0;i<MAX_FILE_LENGTH;i++)
    {
        dataArray[i] = 0;
        instructionsArray[i] = 0;
    }
    DC = 0;
    IC = 0;
    errorsFound = 0;
    freeSymbolTable();
}

void iterate(FILE* file, char* fileName)
{
    int errorsFound = 0;
    StatusCode code;
    SymbolType sType;
    int foundSymbol = 0;            /*Auxiliary flag - checks if symbol found*/
    int numberOfLines = 0;          /*Auxiliary integer - counts lines*/
    char* symbolPos;               /*Auxiliary pointer - to position of symbol*/
    char* command;
    char* restOfLine = NULL;
    char* symbol;
    char* delimit = " \t";          /*Auxiliary flag for tabs*/
    char lineBuffer[LINE_LENGTH];
    char linebufferCopy[LINE_LENGTH]; /*Copy of the line buffer because strtok destroys the string*/

    IC = 0;
    DC = 0;
    while(fgets(lineBuffer,LINE_LENGTH,file) != NULL)
    {
        if(isWhitespace(lineBuffer) || (unsigned char)(*lineBuffer) == ';') /* Checking for empty line or comment line */
        {
            numberOfLines++;
            break;
        }

        strcpy(linebufferCopy,lineBuffer);
        command = strtok(lineBuffer,delimit);
        if((symbolPos = strchr(command,':')) != NULL)   /*Checks if there is a symbol*/
        {
            symbol = strtok(command,":");
            foundSymbol = 1;
            command = strtok(NULL,delimit); /*Should contain instruction/data command*/
            restOfLine = strtok(NULL,""); /*Gets the rest of the line*/
        }
        if(isDataType(command)) /*Data type*/
        {
            if(foundSymbol)
            {
                if(strcmp(command,dataTypes[0]) == 0) /* .data */
                    sType = tData;
                else if(strcmp(command,dataTypes[1]) == 0) /* .string */
                    sType = tString;
                else /* .struct */
                    sType = tStruct;
                if((code = setSymbol(symbol,DC,sType,0,relocatable)) < 0)
                {
                    printError(code,numberOfLines,fileName);
                    errorsFound = 1;
                }
            }
            if((code = insertData(command,restOfLine)) < 0)
            {
                printError(code,numberOfLines,fileName);
                errorsFound = 1;
            }
        }
        else
        {
            if(isExtern(command) || isEntry(command)) /*Extern/Entry*/
            {
                if(isExtern(command))
                    if((code = insertExtern(restOfLine)) < 0)
                    {
                        printError(code,numberOfLines,fileName);
                        errorsFound = 1;
                    }
            }
            else /*Instuction*/
            {
                if(foundSymbol)
                {
                    if((code = setSymbol(symbol,IC,tCode,0,relocatable)) < 0)
                    {
                        printError(code,numberOfLines,fileName);
                        errorsFound = 1;
                    }
                }
                if(isInstuction(command))
                {
                    if((code = insertInstruction(command,restOfLine, 0)) < 0)
                    {
                        printError(code,numberOfLines,fileName);
                        errorsFound = 1;
                    }
                }
                else /* Unrecognized command */
                {
                    code = unrecognized_command;
                    printError(code,numberOfLines,fileName);
                    errorsFound = 1;
                }
            }
        }
        numberOfLines++;
    }
    if(!errorsFound)
    {
        updateDataSymbolValues(IC); /* add the value of IC to the symbols given at "data" part */
        secondIterate(file, fileName);
    }
}
