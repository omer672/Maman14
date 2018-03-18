#include "firstIteration.h"

/*The function handles all global variables used by program*/
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
    entryFound = 0;
    externFound = 0;
    freeSymbolTable();
}

/*The function first iterate on file, gets File type and file name and runs through the file*/
void iterate(FILE* file, char* fileName)
{
    int errorsFound = 0;
    StatusCode code;
    SymbolType sType;
    int foundSymbol = 0;            /*Auxiliary flag - checks if symbol found*/
    int numberOfLines = 0;          /*Auxiliary integer - counts lines*/
    char* symbolPos;               /*Auxiliary pointer - to position of symbol*/
    char* token;
    char command[LINE_LENGTH];
    char restOfLine[LINE_LENGTH];
    char symbol[LINE_LENGTH];
    char* delimit = " \t\n";          /*delimiter for spaces*/
    char lineBuffer[LINE_LENGTH];
    char linebufferCopy[LINE_LENGTH]; /*Copy of the line buffer because strtok destroys the string*/
    int symbolPosition;
    IC = 0;
    DC = 0;
    while(fgets(lineBuffer,LINE_LENGTH,file) != NULL)
    {
        foundSymbol = 0;
        numberOfLines++;
        symbol[0] = '\0';
        if(!(isWhitespace(lineBuffer) || (unsigned char)(*lineBuffer) == ';')) /* Checking for empty line or comment line */
        {
            strcpy(linebufferCopy,lineBuffer);
            token = strtok(lineBuffer, delimit);
            strcpy(command, token);
            if ((symbolPos = strchr(command, ':')) != NULL)	/*Checks if there is a symbol */
            {
                symbolPosition = (int)(symbolPos-command);
                strncpy(symbol, command,symbolPosition);
                symbol[symbolPosition] = '\0'; /* strncpy doesn't insert \0 at the end */
                foundSymbol = 1;
                token = strtok(NULL, delimit);
                if(token == NULL)
                {
                    errorsFound = 1;
                    printError(unrecognized_command,numberOfLines,fileName);
                    continue;
                }
                strcpy(command, token);	/*Should contain instruction/data command */
            }
            token =  strtok(NULL, "");
            if(token != NULL)
                strcpy(restOfLine,token);	/*Gets the rest of the line */
            else
                restOfLine[0] = '\0';
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
        }
    }
    if(!errorsFound)
    {
        updateDataSymbolValues(IC); /* add the value of IC to the symbols given at "data" part */
        secondIterate(file, fileName);
    }
}
