#include "secondIteration.h"

void secondIterate(FILE* file, char* fileName)
{
    int i;     /*Auxiliary integers*/
    int foundSymbol = 0;            /*Auxiliary flag - checks if symbol found*/
    int numberOfLines = 0;          /*Auxiliary integer - counts lines*/
    char* symbolPos;               /*Auxiliary pointer - to position of symbol*/
    char* command;
    char* restOfLine = NULL;
    char* symbol;
    char* delimit = " \t";          /*Auxiliary flag for tabs*/
    char lineBuffer[LINE_LENGTH];
    char linebufferCopy[LINE_LENGTH]; /*Copy of the line buffer because strtok destroys the string*/
    char value[MAX_DIGITS];
    StatusCode code;

    IC = 0;
    while(fgets(lineBuffer,LINE_LENGTH,file) != NULL)
    {
        strcpy(linebufferCopy,lineBuffer);
        command = strtok(lineBuffer,delimit);
        if((symbolPos = strchr(command,':')) != NULL)   /*Checks if there is a symbol*/
        {
            command = strtok(NULL,delimit); /*Should contain instruction/data command*/
            restOfLine = strtok(NULL,""); /*Gets the rest of the line*/
        }
        if(!(isDataType(command) || isExtern(command))) /*Data type or extern*/
        {
            if(isEntry(command)) /*Entry*/
            {
                if((code = markEntry(restOfLine)) < 0)
                {
                    printError(code,numberOfLines,fileName);
                    errorsFound = 1;
                }
            }
            else /*Instruction*/
            {
                if((code = insertInstruction(command,restOfLine, 1)) < 0)
                {
                    printError(code,numberOfLines,fileName);
                    errorsFound = 1;
                }
            }
        }
        numberOfLines++;
    }
    if(!errorsFound)
    {
        createOutputFiles(fileName);
    }

}
