#include "firstIteration.h"

void iterate(FILE* file, char* fileName)
{
    int IC = 0;
    int DC = 0;
    int errorsFound = 0;
    int i;     /*Auxiliary integers*/
    StatusCode code;
    int foundSymbol = 0;            /*Auxiliary flag - checks if symbol found*/
    int numberOfLines = 0;          /*Auxiliary integer - counts lines*/
    char* symbolPos;               /*Auxiliary pointer - to position of symbol*/
    char* command;
    char* restOfLine = NULL;
    char* symbol;
    char* delimit = " \t";          /*Auxiliary flag for tabs*/
    char lineBuffer[LINE_LENGTH];
    char linebufferCopy[LINE_LENGTH]; /*Copy of the line buffer because strtok destroys the string*/

    while(fgets(lineBuffer,LINE_LENGTH,file) != NULL)
    {
        if(isWhitespace(lineBuffer) || (unsigned char)(*lineBuffer) == ';') /* Checking for empty line or comment line */
        {
            numberOfLines++;
            break;
        }

        strcpy(linebufferCopy,lineBuffer);
        command = strtok(lineBuffer,delimit);
        if(symbolPos = strchr(command,':'))   /*Checks if there is a symbol*/
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
                setSymbol(symbol,DC,"data",relocatable);
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
                    if((code = setSymbol(symbol,IC,"",relocatable)) < 0)
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
        /*TODO: add IC to data symbols*/
        secondIterate(file, fileName);
    }
}
