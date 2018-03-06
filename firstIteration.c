#include "firstIteration.h"

void iterate(FILE* file)
{
    int IC = 0;
    int DC = 0;
    int errorsFound;
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

    while(fgets(lineBuffer,LINE_LENGTH,file) != NULL)
    {
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
            insertData(command,restOfLine);
        }
        else
        {
            if(isExtern(command) || isEntry(command)) /*Extern/Entry*/
            {
                if(isExtern(command))
                    insertExtern(restOfLine);
                else
                    ; /*TOOD: write it in entries file*/
            }
            else /*Instuction*/
            {
                if(foundSymbol)
                {
                    setSymbol(symbol,IC,"",relocatable);
                }
                if(isInstuction(command))
                    insertInstruction(command,restOfLine, 0);
            }
        }
        numberOfLines++;
    }
    if(numberOfLines == 0)
        printf("Empty file, moving on");
    if(!errorsFound)
    {
        /*TODO: add IC to data symbols*/
        secondIterate(file);
    }
}
